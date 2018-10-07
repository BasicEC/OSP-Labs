#!/bin/bash
declare -a group

if [[ $# = 0 ]] 
	then echo "no args" >&2
fi

groups=`cat /etc/group | grep "^$1" `

for group in $groups
do
	echo $group
	group=`echo $group | awk -F: '{print $3}'`
	ps -l -f -g "$group"
	echo
done
