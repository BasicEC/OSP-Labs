#!/bin/bash
# Вариант 5

if [[ $# -eq 0 ]] 
then echo "err: no args" >&2
exit 1
fi
for file in "$1"/*
do
	check=$(gfind "$file" -maxdepth 1 -type d) # use find if you don't use solaris
	if [[ $? -eq 0 ]] 
	then
	       if [[ "$file" = "$check" && -n $(gfind "$file" -maxdepth 1 -type f) ]]
	       then 
		echo "$file"
	       fi
	fi
done
