#! /bin/bash


echo "Enter file name"
read -r file

file_exist(){

	echo "file exists: $file"
	echo "File contents"
	cat "$file"
	echo "File info" 
	stat "$file"

}

file_notexist(){
	echo "file does not exists You want to create one?(Y/N)"
	read -r var1
	case "$var1" in
		yes|Y|YES|Yes|y) touch "$file";;
		n|NO|N|No) exit 0;;
	esac

	echo "File Successfully Created"
	echo "Do you want to open it now?(Y/N)"
	read -r var1
	case "$var1" in
		yes|Y|YES|Yes|y) vim "$file";;
		n|NO|N|No) exit 0;;
		*)echo "Didn't choose any option exiting..." & exit 0;;
		
	esac


}
if [ -e "$file" ]; then
	file_exist
else
	file_notexist
fi
