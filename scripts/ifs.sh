#!/bin/bash

string="Hello How are you"

IFS=' '
read -a array <<< "$string"

for word in "${array[@]}"; do
echo "$word"
done

