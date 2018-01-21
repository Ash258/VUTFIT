#!/usr/bin/env bash

function fixIncludes(){
    cd $1
    local FILES=`find . -name '*' -type f`
    #https://regex101.com/r/uSADjl/3
    pattern="\#include \"\(.*\/\)\(.*\)\""
    toReplace="\#include \"\2\""

    for file in ${FILES}; do
        sed -i "s/$pattern/$toReplace/g" ${file}
    done
}

fixIncludes ../tmp/
