#!/bin/bash
# var 4

if [[ $# -eq 0 ]] 
then echo "err: no args" >&2
exit 1
fi

if [[ !( -d $1 ) ]] 
then echo "err: $1 isn't dir" >&2
exit 1
fi

dir_info=$(ls -ld "$1" | awk '{print $1":"$3}')
perm=${dir_info%:*}
owner=${dir_info#*:}
uid_gid=$(getent passwd | grep "$owner" | cut -d: -f 3,4 )

regex="[^:]+:[^:]+:[^:]+:${uid_gid#*:}:*"

if [[ -n $(echo $perm | egrep "d....w....") ]]  
then
getent passwd | egrep -v "^$owner" | egrep "$regex" | cut -d: -f 1  
fi

if [[ -n $(echo $perm | egrep "d.w.......") ]]
then echo $owner 
fi

if [[ -n $(echo $perm | egrep "d.......w.") ]] 
then getent passwd | egrep -v "$regex" | cut -d: -f 1 
fi
