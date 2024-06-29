#!/bin/bash

echo "Enter value of A"
read a

add(){

local b=20
echo "a+b is $((a+b))"
}

sub(){
	local b
	echo "Enter b"
	read b
	if [ $b -lt $a ]
	then
		echo "a-b is $((a-b))"
	else
		echo "a should be greater than b"
	fi
}

comp(){
	local b=23
if [ $a -eq $b ]
then
	echo "A is equal to B"
fi

if [ $a -ne $b ] 
then
	echo "A is not equal to B"
fi
}

comp
sub
add
