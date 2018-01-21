#!/usr/bin/env bash

# Použití:   is_it_ok.sh xlogin01.zip testdir
#
#   - POZOR: obsah adresáře zadaného druhým parametrem bude VYMAZÁN!
#   - Rozbalí archív studenta xlogin01.zip do adresáře testdir a a ověří formální požadavky pro odevzdání projektu IFJ
#   - Následně vyzkouší kompilaci
#   - Detaily průběhu jsou logovány do souboru is_it_ok.log v adresáři testdir

# Autor: Zbyněk Křivka
# Verze: 1.2 (2012-11-23)
RED='\033[0;31m'
GREEN='\033[1;32m'
NC='\033[0m'
LOG="is_it_ok.log"

# Implicit task identifier from config.sh
if [[ $# -ne 2 ]]; then
    echo -e "${RED}ERROR : Missing arguments or too much arguments!${NC}"
    echo -e "Usage: $0  ARCHIVE  TESTDIR"
    echo -e "       This script checks formal requirements for archive with solution of IFJ project."
    echo -e "         ARCHIVE - the filename of archive to check"
    echo -e "         TESTDIR - temporary directory that can be deleted/removed during testing!"
    exit 2
fi

# Extrakce archivu
function unpack_archive () {
    local ext=`echo $1 | cut -d . -f 2,3`
    echo -n "2] Archive extraction: "
    RETCODE=100

    if [[ "$ext" = "zip" ]]; then
        unzip -o $1 >> ${LOG} 2>&1
        RETCODE=$?
    elif [[ "$ext" = "gz" || "$ext" = "tgz" || "$ext" = "tar.gz" ]]; then
        tar xfz $1 >> ${LOG} 2>&1
        RETCODE=$?
    elif [[ "$ext" = "tbz2" || "$ext" = "tar.bz2" ]]; then
        tar xfj $1 >> ${LOG} 2>&1
        RETCODE=$?
    fi
    if [[ ${RETCODE} -eq 0 ]]; then
        echo -e "${GREEN}OK${NC}"
    elif [[ ${RETCODE} -eq 100 ]]; then
        echo -e "${RED}ERROR (unsupported extension)${NC}"
        exit 1
    else
        echo -e "${RED}ERROR (code $RETCODE)${NC}"
        exit 1
    fi
}

# Převod jmen souboru obsahujících nepovolené znaky
function to_small () {
    local N=`echo $1 | tr "[:upper:]" "[:lower:]"`
    if [ "$N" != "$1" ]; then
        mv "$1" "$N" 2>/dev/null
        echo -e "${RED}ERROR ($1 -> $N)${NC}"
        exit 1
    fi
}

# Flattening aktuálního adresáře + to_small
function flattening () {
    local FILE=""
    local NFILE=""
    local FILES=`find . -name '*' -type f`
    for FILE in ${FILES}; do
         NFILE=./${FILE##*/}

         if [ "$FILE" != "$NFILE" ]; then
             mv "$FILE" ${NFILE} 2>/dev/null
             echo -e "${RED}ERROR ($FILE -> $NFILE)${NC}"
             exit 1
         fi
         F=`basename ${FILE}`
         if [ "$F" != "Makefile" ]; then
             to_small ${NFILE}
         fi
    done
    echo -e "${GREEN}OK${NC}"
}

# Staré odstranění DOSovských řádků (nyní možno použít i utilitu dos2unix)
function remove_CR () {
    local FILES=`ls $* 2>/dev/null`
    for FILE in ${FILES}; do
        mv -f "$FILE" "$FILE.tmp"
        tr -d "\015" < "$FILE.tmp" > "$FILE"
        rm -f "$FILE.tmp"
    done
}

#   0) Příprava testdir a ověření serveru
rm -rf $2 2>/dev/null
mkdir $2 2>/dev/null
cp $1 $2 2>/dev/null

echo -n "Testing on Merlin: "
HN=`hostname`
if [[ ${HN} = "merlin.fit.vutbr.cz" ]]; then
    echo -e "Yes"
else
    echo -e "No"
fi

#   1) Extrahovat do testdir
cd $2
touch ${LOG}
ARCHIVE=`basename $1`
NAME=`echo ${ARCHIVE} | cut -d . -f 1 | egrep "x[a-z]{5}[0-9][0-9a-z]"`
echo -n "1] Archive name ($ARCHIVE): "
if [[ -n ${NAME} ]]; then
    echo -e "${GREEN}OK${NC}"
else
    echo -e "${RED}ERROR (the name does not correspond to a login)${NC}"
    exit 11
fi

unpack_archive ${ARCHIVE}

#   2) Normalizace jmen na mala písmena
echo -n "3] Normalization of filenames: "
flattening

#   3) Dokumentace
echo -n "4] Searching for dokumentace.pdf: "
if [[ -f "dokumentace.pdf" ]]; then
    echo -e "${GREEN}OK${NC}"
else
    echo -e "${RED}ERROR (not found)${NC}"
    exit 12
fi

#   4) Příprava kompilace
remove_CR *.mak *.c *.cpp *.cc *.h *.c++ *.hpp
chmod 644 *

#   5) Kompilace
echo -n "5] Project compilation: "
if [[ -f Makefile ]]; then
    ( make ) >> ${LOG} 2>&1
    RETCODE=$?
    if [[ -z ${RETCODE} ]]; then
        echo -e "${RED}ERROR (returns code $RETCODE)${NC}"
        exit 15
    fi
else
    echo -e "${RED}ERROR (missing Makefile)${NC}"
    exit 15
fi
echo -e "${GREEN}OK${NC}"

#   6) Najdi přeložený binární soubor
echo -n "6] Searching for created binary file: "
EXE=`ls -F | grep "*" | tr -d "*" | grep "" -m 1`   # A najít binárku...
if [[ -f ${EXE} ]]; then
    echo -e "${GREEN}OK ($EXE)${NC}"
else
    echo -e "${RED}ERROR (not found)${NC}"
    exit 16
fi

#   7) Kontrola, ze nebyl vytvořen podadresář
echo -n "7] Searching for new subdirectories: "
DIR_COUNT=`find -type d | grep -v "^\.$" | wc -l`
if [[ ${DIR_COUNT} -eq 0 ]]; then
    echo -e "${GREEN}OK (None)${NC}"
else
    echo -e "${RED}ERROR (found $DIR_COUNT subdirectory/ies)${NC}"
    exit 17
fi

#   8) Kontrola rozděleni
echo -n "8] Presence of file rozdeleni: "
IFS="$IFS:"
if [[ -f rozdeleni ]]; then
    # Zpracování souboru rozdělení
    unset LOGINS
    unset PERCENTS
    unset ARCHNAME
    declare -a LOGINS
    {
        i=0
        declare -a RADEK
        declare -a PERCENTS
        while read -a RADEK; do
            if [[ "${RADEK[0]}" != "" ]]; then
                LOGINS[$i]=${RADEK[0]}
                PERCENTS[$i]=`echo ${RADEK[1]} | tr -cd [:digit:]`
                ((TMP_PROC+=${PERCENTS[$i]:-0}))
                ((i++))
            if [[ "$NAME" = "${RADEK[0]}" ]]; then
                ARCHNAME=${NAME}
            fi
            else
                echo -e "${RED}ERROR (empty line occurred)${NC}"
                exit 18
            fi
        done
    } < rozdeleni

    # Kontrola formátu rozdělení a součtu procent
    if [[ -n $RADEK ]]; then # Simple variable must be used
        echo -e "${RED}ERROR (the last line is not ended properly)${NC}"
        exit 18
    elif [[ ${TMP_PROC} -ne 100 ]]; then
        echo -e "${RED}ERROR (sum != 100%)${NC}"
        exit 18
    elif [[ -z ${ARCHNAME} ]]; then
        echo -e "${RED}ERROR (rozdeleni does not contain the leader's login $NAME)${NC}"
        exit 18
    else
        echo -e "${GREEN}OK${NC}"
    fi

else
    echo -e "${RED}ERROR (file not found)${NC}"
    exit 18
fi

#   9) Kontrola rozšíření
echo -n "9] Presence of file rozsireni (optional): "
if [[ -f rozsireni ]]; then
    echo -e "${GREEN}Yes${NC}"
else
    echo -e "No"
fi
