#!/usr/bin/env bash

NORM=1
IGFILE="/"
CPWD="."

while getopts "ni:" opt; do
  case $opt in
	n)
		if test -t ; then
			NORM=$(( `tput cols` - 13 ))
		else
			NORM=79
		fi
	  ;;
	i)
	  if [ "$(echo "!$OPTARG" | head -c 2)" = "!-" ]; then
		echo "Invalid parameter of -i" >&2
		exit 1
	  fi
	  IGFILE=$OPTARG
	  ;;
	\?)
	  echo "Invalid option: -$OPTARG" >&2
	  exit 1
	  ;;
	:)
	  echo "Option -$OPTARG requires an argument." >&2
	  exit 1
	  ;;
  esac
done

((OPTIND--))
shift $OPTIND
if [ "$*" != "" ]; then
	CPWD=$(echo "$*" | cut -d " " -f1)
fi

if [ ! -d "$CPWD" ]; then
	echo "Directory '"${CPWD}"' does not exist." >&2
	exit 1
fi
echo "Root directory:" ${CPWD}
echo "Directories:" `find  ${CPWD} -type d -not -name "$IGFILE" | wc -l`
echo "All files:" `find  ${CPWD} -type f -not -name "$IGFILE" | wc -l`

VAR1=`find ${CPWD} -type f -size -100c -not -name "$IGFILE" | wc -l`
VAR2=`find ${CPWD} -type f -size +99c -a -size -1024c -not -name "$IGFILE" | wc -l`
VAR3=`find ${CPWD} -type f -size +1023c -a -size -10240c -not -name "$IGFILE" | wc -l`
VAR4=`find ${CPWD} -type f -size +10239c -a -size -102400c -not -name "$IGFILE" | wc -l`
VAR5=`find ${CPWD} -type f -size +102399c -a -size -1048576c -not -name "$IGFILE" | wc -l`
VAR6=`find ${CPWD} -type f -size +1048575c -a -size -10485760c -not -name "$IGFILE" | wc -l`
VAR7=`find ${CPWD} -type f -size +10485759c -a -size -104857600c -not -name "$IGFILE" | wc -l`
VAR8=`find ${CPWD} -type f -size +104857599c -a -size -1073741824c -not -name "$IGFILE" | wc -l`
VAR9=`find ${CPWD} -type f -size +1073741823c -not -name "$IGFILE" | wc -l`
MAX=`(echo "$VAR1"; echo "$VAR2"; echo "$VAR3"; echo "$VAR4"; echo "$VAR5"; echo "$VAR6"; echo "$VAR7"; echo "$VAR8"; echo "$VAR9") | sort | tail -n 1`

if [ ${NORM} != 1 ]; then
	if [ ${NORM} -lt ${MAX} ]; then
		VAR1=`awk "BEGIN { print ($NORM / $MAX) * $VAR1 }" | tr ',' '.'` ; VAR1=`awk 'BEGIN { printf("%.0f\n", '${VAR1}'); }'`
		VAR2=`awk "BEGIN { print ($NORM / $MAX) * $VAR2 }" | tr ',' '.'` ; VAR2=`awk 'BEGIN { printf("%.0f\n", '${VAR2}'); }'`
		VAR3=`awk "BEGIN { print ($NORM / $MAX) * $VAR3 }" | tr ',' '.'` ; VAR3=`awk 'BEGIN { printf("%.0f\n", '${VAR3}'); }'`
		VAR4=`awk "BEGIN { print ($NORM / $MAX) * $VAR4 }" | tr ',' '.'` ; VAR4=`awk 'BEGIN { printf("%.0f\n", '${VAR4}'); }'`
		VAR5=`awk "BEGIN { print ($NORM / $MAX) * $VAR5 }" | tr ',' '.'` ; VAR5=`awk 'BEGIN { printf("%.0f\n", '${VAR5}'); }'`
		VAR6=`awk "BEGIN { print ($NORM / $MAX) * $VAR6 }" | tr ',' '.'` ; VAR6=`awk 'BEGIN { printf("%.0f\n", '${VAR6}'); }'`
		VAR7=`awk "BEGIN { print ($NORM / $MAX) * $VAR7 }" | tr ',' '.'` ; VAR7=`awk 'BEGIN { printf("%.0f\n", '${VAR7}'); }'`
		VAR8=`awk "BEGIN { print ($NORM / $MAX) * $VAR8 }" | tr ',' '.'` ; VAR8=`awk 'BEGIN { printf("%.0f\n", '${VAR8}'); }'`
		VAR9=`awk "BEGIN { print ($NORM / $MAX) * $VAR9 }" | tr ',' '.'` ; VAR9=`awk 'BEGIN { printf("%.0f\n", '${VAR9}'); }'`
	fi
fi

echo "File size histogram:"
echo "  <100 B  :" `if [ ${VAR1} != 0 ]; then yes "#" | head -n ${VAR1} | tr -d '\n'; fi`
echo "  <1 KiB  :" `if [ ${VAR2} != 0 ]; then yes "#" | head -n ${VAR2} | tr -d '\n'; fi`
echo "  <10 KiB :" `if [ ${VAR3} != 0 ]; then yes "#" | head -n ${VAR3} | tr -d '\n'; fi`
echo "  <100 KiB:" `if [ ${VAR4} != 0 ]; then yes "#" | head -n ${VAR4} | tr -d '\n'; fi`
echo "  <1 MiB  :" `if [ ${VAR5} != 0 ]; then yes "#" | head -n ${VAR5} | tr -d '\n'; fi`
echo "  <10 MiB :" `if [ ${VAR6} != 0 ]; then yes "#" | head -n ${VAR6} | tr -d '\n'; fi`
echo "  <100 MiB:" `if [ ${VAR7} != 0 ]; then yes "#" | head -n ${VAR7} | tr -d '\n'; fi`
echo "  <1 GiB  :" `if [ ${VAR8} != 0 ]; then yes "#" | head -n ${VAR8} | tr -d '\n'; fi`
echo "  >=1 GiB :" `if [ ${VAR9} != 0 ]; then yes "#" | head -n ${VAR9} | tr -d '\n'; fi`

echo "File type histogram:"
if [ ${NORM} != 1 ]; then
	NORM=$(( $NORM - 35 ))
fi
TMP=`find ${CPWD} -type f -not -name "$IGFILE"`
TMP=$(echo "`( "file" $TMP "-b")`" | sort | uniq -c | sort -r | head -n 10)
MAX=$(echo $TMP | cut -d " " -f1)
echo "$TMP" | while read -e LINE
do
	NUMBER=$(echo "${LINE}" | cut -d " " -f1)
	LINE=${LINE#"$NUMBER "}

	if [ ${NORM} != 1 ]; then
		if [ ${NORM} -lt ${MAX} ]; then
			NUMBER=`awk "BEGIN { print ($NORM / $MAX) * $NUMBER }" | tr ',' '.'` ; NUMBER=`awk 'BEGIN { printf("%.0f\n", '${NUMBER}'); }'`
		fi
	fi

	printf "  %.40s%.3s: " "$LINE                                        " "$(if [ 39 -lt ${#LINE} ] ; then echo "..." ;  else echo "   "; fi)"; echo `if [ 1 -le ${NUMBER} ]; then yes "#" | head -n ${NUMBER} | tr -d '\n'; fi`

done
