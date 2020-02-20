#!/bin/bash

findFiles(){
    if [ ! -d $1 ]
    then
	1>&2 echo "The argument passed is not a directory."
	exit 1
    elif [ ! -r $1 ]
    then
	 1>&2 echo "Read access unavailable."
	 exit 0
    fi

    ls -a $1 > files
    sed '/^.\{,14\}$/d' files > invalidNames
    sed "/^[A-Za-z_-\.]*$/d" files >> invalidNames
    ls -a $1 | grep -E "^\-" >> invalidNames
    sed '/^[^\.]/d' files >> invalidNames
    sed -i '/^\.$/d' invalidNames
    sed -i '/^\.\.$/d' invalidNames
    sort files > files2
    uniq -u -i files2 | sort > uniqfiles
    comm -23 - uniqfiles < files2 >> invalidNames
    sort -u < invalidNames > invalidNames2

    find $1 -maxdepth 1 -type d -printf '%f\n' | sort  > directories
    comm -13 - invalidNames2 < directories > invalidNames
    comm -12 - invalidNames2 < directories > directories2
    
    IFS=$'\n'
    for i in $(cat invalidNames)
    do
	if [ "${1: -1}" != "/" ]
	then
	    echo "$1/$i"
	else
	    echo "$1$i"
	fi  
    done

    IFS=$'\n'
    for i in $(cat directories2)
    do
	if [ "${1: -1}" != "/" ]
	then
	    echo "$1/$i/"
	else
	    echo "$1$i/"
	fi  
    done
    
    
}

if [ $# -eq 0 ]
then    
    findFiles '.'
elif [ $# -gt 1 ]
then
    1>&2 echo "Only one argument is allowed."
    exit 1
else
    findFiles $1
fi

