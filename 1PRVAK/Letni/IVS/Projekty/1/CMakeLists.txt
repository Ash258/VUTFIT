##======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============##
##
## Purpose:     IVS Project 1 - Solution CMakeFile
##
## $NoKeywords: $ivs_project_1 $CMakeLists.txt
## $Authors:    Filip Vaverka <ivaverka@fit.vutbr.cz>
##              David Grochol <igrochol@fit.vutbr.cz>
## $Date:       $2017-01-04
##============================================================================##

CMAKE_MINIMUM_REQUIRED(VERSION 2.8.4)
PROJECT(ivs_proj_1)
SET(CMAKE_BUILD_TYPE Debug)

IF (CMAKE_COMPILER_IS_GNUCXX)
	INCLUDE(CodeCoverage.cmake)

	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage -std=c++11")
	SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage")
ENDIF ()

INCLUDE(GoogleTest.cmake)

# Test targets
ENABLE_TESTING()

FIND_LIBRARY(BLACK_BOX_LIBS black_box_lib REQUIRED PATHS libs NO_DEFAULT_PATH)
INCLUDE_DIRECTORIES("libs")

ADD_EXECUTABLE(black_box_test black_box_tests.cpp)
TARGET_LINK_LIBRARIES(black_box_test ${BLACK_BOX_LIBS} gtest_main)
GTEST_ADD_TESTS(black_box_test "" black_box_tests.cpp)

ADD_EXECUTABLE(white_box_test white_box_tests.cpp white_box_code.cpp)
TARGET_LINK_LIBRARIES(white_box_test gtest_main)
GTEST_ADD_TESTS(white_box_test "" white_box_tests.cpp)
IF (CMAKE_COMPILER_IS_GNUCXX)
	SETUP_TARGET_FOR_COVERAGE(white_box_test_coverage white_box_test white_box_test_coverage)
ENDIF ()

ADD_EXECUTABLE(tdd_test tdd_code.cpp tdd_tests.cpp)
TARGET_LINK_LIBRARIES(tdd_test gtest_main)
GTEST_ADD_TESTS(tdd_test "" tdd_tests.cpp)
IF (CMAKE_COMPILER_IS_GNUCXX)
	SETUP_TARGET_FOR_COVERAGE(tdd_test_coverage tdd_test tdd_test_coverage)
ENDIF ()

IF (CMAKE_VERSION VERSION_GREATER 3.2.0)
	ADD_CUSTOM_TARGET(pack COMMAND
	                  ${CMAKE_COMMAND} -E tar "cfv" "xcaber00.zip" --format=zip
	                  "${CMAKE_CURRENT_SOURCE_DIR}/black_box_tests.cpp"
	                  "${CMAKE_CURRENT_SOURCE_DIR}/white_box_tests.cpp"
	                  "${CMAKE_CURRENT_SOURCE_DIR}/tdd_code.h"
	                  "${CMAKE_CURRENT_SOURCE_DIR}/tdd_code.cpp")
ENDIF ()

#add_test(NAME ivs_proj_1_black_box_test COMMAND ivs_proj_1_black_box --gtest_filter=example_test1.*)
