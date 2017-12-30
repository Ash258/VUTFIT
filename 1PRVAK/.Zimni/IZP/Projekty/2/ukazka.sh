#!/bin/sh

iteraci=${1:-4000}
inputs=${2:-"inf -inf nan -nan 0 1 -1 0.01 1.00001 -1.00001 2.7 -2.7 0.12 -0.82 1.23 -1.58 10.5 -17.12 -220.9 118.4"}

check () {
	"$@" | awk '{print $NF}' | xargs echo | {
		read reference method1 method2
		([ "$reference" != "$method1" ] || [ "$reference" != "$method2" ]) && {
			echo "$reference $method1 $method2" | grep -q 'nan.*nan.*nan' ||
				echo "$@;$reference;$method1;$method2"
		}
	} | grep -v 'pow -.*nan;-*nan$'
}

for input1 in $inputs; do
	check ./proj2 --log $input1 $iteraci

	for input2 in $inputs; do
		check ./proj2 --pow $input1 $input2 $iteraci
	done
done | column -s\; -t

echo

./proj2 --log 1.131401114526 4

echo

./proj2 --pow 1.23 4.2 4
