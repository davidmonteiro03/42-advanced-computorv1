#!/bin/bash

print_error () {
	if ! [ $# -eq 1 ]; then return; fi
	echo -e "\e[5m❌\e[0m \e[1m\e[38;2;255;0;20m$1\e[0m" 1>&2
}

print_warning () {
	if ! [ $# -eq 1 ]; then return; fi
	echo -e "⚠️  \e[1m\e[38;2;255;255;0m$1\e[0m" 1>&2
}

print_loading () {
	if ! [ $# -eq 1 ]; then return; fi
	echo -e "⏳ \e[1m\e[38;2;0;120;255m$1\e[0m" 1>&2
}

print_success () {
	if ! [ $# -eq 1 ]; then return; fi
	echo -e "✅ \e[1m\e[38;2;0;195;0m$1\e[0m"
}

test () {
	if ! [ $# -eq 2 ]; then return; fi
	print_loading "Testing '$input'..."
	input="$1"
	correct="$2"
	make || exit 1
	./computor "$input" 2>&1 > "executed.txt"
	echo -n "$correct" 2>&1 > "correct.txt"
	if ! diff "executed.txt" "correct.txt"
	then
		print_error "Test for '$input' failed."
		exit 1
	else
		print_success "Test for '$input' succeed."
	fi
}

test "" "Reduced form: 0 = 0
Any real number is a solution.
"
