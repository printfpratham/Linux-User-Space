#! /bin/bash


echo "Enter file name"
read -r file

if [ -e "$file" ]
then
	echo "file exists: $file"
	echo "File contents"
	cat "$file"
	echo "File info" 
	stat "$file"
else
	echo "file does not exists making new file..."
	touch "$file"
	echo -e '\a'
	echo "File Successfully made"
	vim "$file"

fi
