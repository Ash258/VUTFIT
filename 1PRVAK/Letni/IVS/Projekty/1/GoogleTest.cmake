##======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============##
##
## Purpose:     IVS Project 1 - CMakeFile (except from FindGTest.cmake)
##
## $NoKeywords: $ivs_project_1 $CMakeLists.txt
## $Authors:    Filip Vaverka <ivaverka@fit.vutbr.cz>
##              David Grochol <igrochol@fit.vutbr.cz>
## $Date:       $2017-01-04
##============================================================================##

FUNCTION(GTEST_ADD_TESTS executable extra_args)
	IF (NOT ARGN)
		MESSAGE(FATAL_ERROR "Missing ARGN: Read the documentation for GTEST_ADD_TESTS")
	ENDIF ()
	IF (ARGN STREQUAL "AUTO")
		# obtain sources used for building that executable
		GET_PROPERTY(ARGN TARGET ${executable} PROPERTY SOURCES)
	ENDIF ()
	SET(gtest_case_name_regex ".*\\( *([A-Za-z_0-9]+) *, *([A-Za-z_0-9]+) *\\).*")
	SET(gtest_test_type_regex "(TYPED_TEST|TEST_?[FP]?)")
	FOREACH (source ${ARGN})
		SET_PROPERTY(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ${source})
		FILE(READ "${source}" contents)
		STRING(REGEX MATCHALL "${gtest_test_type_regex} *\\(([A-Za-z_0-9 ,]+)\\)" found_tests ${contents})
		FOREACH (hit ${found_tests})
			STRING(REGEX MATCH "${gtest_test_type_regex}" test_type ${hit})

			# Parameterized tests have a different signature for the filter
			IF ("x${test_type}" STREQUAL "xTEST_P")
				STRING(REGEX REPLACE ${gtest_case_name_regex} "*/\\1.\\2/*" test_name ${hit})
			ELSEIF ("x${test_type}" STREQUAL "xTEST_F" OR "x${test_type}" STREQUAL "xTEST")
				STRING(REGEX REPLACE ${gtest_case_name_regex} "\\1.\\2" test_name ${hit})
			ELSEIF ("x${test_type}" STREQUAL "xTYPED_TEST")
				STRING(REGEX REPLACE ${gtest_case_name_regex} "\\1/*.\\2" test_name ${hit})
			ELSE ()
				MESSAGE(WARNING "Could not parse GTest ${hit} for adding to CTest.")
				CONTINUE()
			ENDIF ()
			ADD_TEST(NAME ${test_name} COMMAND ${executable} --gtest_filter=${test_name} ${extra_args})
		ENDFOREACH ()
	ENDFOREACH ()
ENDFUNCTION()

IF (NOT EXISTS ${CMAKE_BINARY_DIR}/googletest-master)
	CONFIGURE_FILE(CMakeLists.txt.in googletest/CMakeLists.txt)
	EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
	                RESULT_VARIABLE result
	                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest)
	IF (result)
		MESSAGE(FATAL_ERROR "CMake step for googletest failed: ${result}")
	ENDIF ()

	EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} --build .
	                RESULT_VARIABLE result
	                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest)
	IF (result)
		MESSAGE(FATAL_ERROR "Build step for googletest failed: ${result}")
	ENDIF ()
ENDIF ()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
SET(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

ADD_SUBDIRECTORY(${CMAKE_BINARY_DIR}/googletest-master
                 ${CMAKE_BINARY_DIR}/googletest-build)

IF (CMAKE_VERSION VERSION_LESS 2.8.11)
	INCLUDE_DIRECTORIES("${gtest_SOURCE_DIR}/include")
ENDIF ()
