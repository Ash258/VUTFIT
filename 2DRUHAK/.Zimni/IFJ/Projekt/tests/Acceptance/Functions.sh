#!/usr/bin/env bash
# Helper functions for dealing with program output and syntax sugar.

RED='\033[1;31m'
GREEN='\033[1;32m'
BLUE='\033[1;34m'
NC='\033[0m' # No Color

LOG="Acceptance.log"
GENERATED_FILE="../../GeneratedFile.code"
TESTS_C=0
PASSED_T=0
FAILED_T=0

appendLog(){
    echo -e "$1" >> ${LOG}
}

#TODO: Handle inputs in some .input file
executeTest(){
    appendLog "========Starting $2=========="

    (./$1 < $2 > ${GENERATED_FILE} 2>> ${LOG}) # Save stdout into file

    local actualExitCode=$? # Save exit code of executed program
    local outFile="${2%.IFJ}.stdout" exitFile="${2%.IFJ}.exit"
    local generatedCodeFile="" expectedSTDOUT=""
    local expectedExitCode=0 resultOfIc17=0 resultOfDiff=0

    # If you need to check what program generate add something as third parameter to executeTest function.
    if [[ ! -z $3 ]]; then
        appendLog "\t`cat ${GENERATED_FILE}`"
    fi

    # Get expected outputs or empty
    if [ -f ${outFile} ]; then expectedSTDOUT=`cat "${outFile}"`; fi

    # If there is no exitfile return code is 0
    if [ -f ${exitFile} ]; then expectedExitCode=`cat "${exitFile}"`; fi

    if [[ (${actualExitCode} == 0) ]]; then
        generatedCodeFile=`ic17int ${GENERATED_FILE} 2>> ${LOG}`
        resultOfIc17=$?
        diff -q <(echo "${generatedCodeFile}") <(echo "${expectedSTDOUT}") > /dev/null
        resultOfDiff=$?
    fi

    if [[ (${actualExitCode} -eq ${expectedExitCode}) && (${resultOfDiff} -eq 0) && (${resultOfIc17} -eq 0) ]]; then
        printStatus 1 $2
    else
        printStatus 0 $2
    fi

    appendLog "${generatedCodeFile}"
    appendLog "STATUS CODES:\n\t Compiler: ${actualExitCode}\n\t Expected compiler: ${expectedExitCode} \n\t ic17int: ${resultOfIc17}"
    appendLog "=========End of $2===========\n"
}

printStatus(){
    ((TESTS_C++))
    if [[ $1 -eq 1 ]]; then
        echo -e "${GREEN}========== $2 ==========${NC}"
        appendLog "\tPASSED"
        ((PASSED_T++))
    elif [[ $1 -eq 0 ]]; then
        echo -e "${RED}========== $2 ==========${NC}"
        appendLog "\tFAILED"
        ((FAILED_T++))
    fi
}

printFinalSummary(){
    line="[${BLUE}====${NC}] Synthesis: Tested: ${BLUE}${TESTS_C}${NC} | Passing: ${GREEN}${PASSED_T}${NC} |"
    line="${line} Failing: ${RED}${FAILED_T}${NC} | ($((${PASSED_T} * 100 / ${TESTS_C}))%)"

    echo -e ${line}
}

printAndExit(){
    printFinalSummary

    if [[ (${FAILED_T} -gt 0) || (${PASSED_T}+${FAILED_T} -ne ${TESTS_C}) ]]; then
        exit 15
    fi

    exit 0
}
