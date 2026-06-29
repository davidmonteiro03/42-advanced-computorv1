#!/bin/bash

test () {
	if ! [ $# -eq 2 ]; then return; fi
	input="$1"
	correct="$2"
	make
	./computor "$input" > "executed.txt"
	echo -n "$correct" > "correct.txt"
	if ! diff "executed.txt" "correct.txt"; then exit 1; fi
}

test "" "Reduced form: 0 = 0
Any real number is a solution.
"
