#!/usr/bin/env bash
cosi=`dirname $0`

echo 17953 > $cosi/done/lev.cProfile_output

#{ time python /code/proj8/time/para.py ; } 2> $cosi/done/para.time_output
#{ time python /code/proj8/time/sekv.py ; } 2> $cosi/done/sekv.time_output

#{ time python /code/proj8/out/done/xcaber00_nonpalindrom_words_existing_reversed.py /code/proj8/words/words.txt ; } 2> $cosi/done/words.time_output

echo GIL > $cosi/done/why.txt

zip -j -xcjf $cosi/xcaber00.zip $cosi/done/*
