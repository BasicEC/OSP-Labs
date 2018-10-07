#!/bin/bash
# Вариант 5

if [[ $# -eq 0 ]] 
then echo "err: no args" >&2
exit 1
fi
declare -a list
list="$1"/*
for file in $list
do
	check=$(gfind "$file" -maxdepth 1 -type d )#gfind for solaris. Use find in Linux. 
	if [[ $? -eq 0 ]] 
	then
	       if [[ "$file" = "$check" && -n $(gfind "$file" -maxdepth 1 -type f) ]]
	       then 
		echo "$file"
	       fi
	fi
done
