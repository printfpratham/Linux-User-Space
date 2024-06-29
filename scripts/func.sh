#!/bin/bash


JUST=1

funky(){
	echo "Inside funky function"
	echo "Exiting funky function"
}

fun(){
	i=0
	REPEAT=5
	echo
	echo "Fun begin"
	echo

	sleep $JUST
	while [ $i -lt $REPEAT ]
	do
		echo "-----FUNCTION-----"
		echo "-----ARE-----"
		echo "-----FUN-----"
		echo
		((i++))
		sleep $JUST
	done
}

funky
fun

exit $?
