#!/bin/sh
# @author: Nějaký randomák

for t in c016 c401 c402; do
	echo "################################################################################"
	echo "Running tests for "$t":"
	cd $t

	test1=$t-test
	test2=$t-advanced-test
	rm $test1 $test2 2>/dev/null >/dev/null
	make $test1
	make $test2
	chmod +x $test1
	chmod +x $test2
################### standard test #############################################
	echo -n "   standard test:"
	./$test1 > $test1-result.txt
	diff $test1.output $test1-result.txt >diff-standard.txt
	if [ -s diff-standard.txt ]; then
		echo "      failed"
		echo "Do you want to check differences (Y/N)?"
		read x
		if [ "$x" = "Y" -o "$x" = "y" ]; then
			cat diff-standard.txt
		fi
	else
		echo "      success"
		valgrind --log-file=valgrind.txt ./$test1 >/dev/null
		echo "     ---------------------------------------------------------------VALGRIND OUT"
		cat valgrind.txt | sed 's/^.*[=]/     |/g' | grep bytes
		echo "     ---------------------------------------------------------------VALGRIND OUT"
	fi
################### advanced test #############################################
	echo -n "   advanced test:"
	./$test2 > $test2-result.txt
	diff $test2.output $test2-result.txt >diff-advanced.txt
	if [ -s diff-advanced.txt ]; then
		echo "      failed"
		echo "Do you want to check differences (Y/N)?"
		read x
		if [ "$x" = "Y" -o "$x" = "y" ]; then
			cat diff-advanced.txt
		fi
	else
		echo "      success"
		valgrind --log-file=valgrind.txt ./$test2 >/dev/null
		echo "     ---------------------------------------------------------------VALGRIND OUT"
		cat valgrind.txt | sed 's/^.*[=]/     |/g' | grep bytes
		echo "     ---------------------------------------------------------------VALGRIND OUT"
	fi
	cd ..
	echo ""
done

echo "Do you want to remove temporary files (Y/N)?"
read x
if [ "$x" = "Y" -o "$x" = "y" ]; then
	cd c016
	rm -f c016*.txt c016*test valgrind.txt diff*.txt
	cd ..

	cd c401
	rm -f c401*.txt c401*test valgrind.txt diff*.txt
	cd ..

	cd c402
	rm -f c402*.txt c402*test valgrind.txt diff*.txt
fi
############################## END ############################################
