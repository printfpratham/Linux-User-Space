#!/bin/bash

salutation=hello;
echo $salutation
echo "The program $0 is running"
echo "The second parameter was $2"
echo "The first parameter was $1"
echo "List was $*"
echo "home directory $HOME"
echo "Present directory is $PWD"
exit 0;
