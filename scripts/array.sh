#!/bin/bash



arr=("file1" "file2" "file3")
echo "Elements are"

i=0
SL=1
while [ $i -lt 3 ]
do
	echo "${arr[i]}"
	((i++))
	sleep $SL
done

exit 0
