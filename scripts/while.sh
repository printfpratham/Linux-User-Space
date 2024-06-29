#!/bin/bash

echo "enter N"
read N
while [ "$N" -le 10 ]; do
	echo "$N"
	((N++))
done
exit 0


