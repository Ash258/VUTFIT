#!/usr/bin/env bash

FILE=`find .. -name "Functions.sh" -type f`
DEFAULT="generatedCodeFile=\`ic17int"
FIX="generatedCodeFile=\`..\/..\/ic17int"

if [[ $1 == 1 ]]; then
    sed -i "s/$DEFAULT/$FIX/g" ${FILE}
elif [[ $1 == 0 ]]; then
    sed -i "s/$FIX/$DEFAULT/g" ${FILE}
fi
