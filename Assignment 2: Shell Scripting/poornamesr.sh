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
    sed "/^[A-Za-z\._-]*$/d" files >> invalidNames
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

    rm directories2
    rm files
    rm invalidNames
    rm invalidNames2
    rm files2
    rm uniqfiles

    if [ $2 = '-r' ]
    then
	
	find $1 -maxdepth 1 -type d | sort  > directories
	IFS=$'\n'
	for i in $(cat directories)
	do
	    if [ $i != $1 ]
	    then
		findFiles $i -r
	    fi
	done
    fi
}

if [ $# -eq 0 ]
then    
    findFiles '.' -nr
elif [ $# -gt 2 ]
then
    1>&2 echo "Only up to two argument are allowed."
    exit 1
elif [ $# -gt 1 ]
then
    if [ $1 != '-r' ]
    then
	1>&2 echo "-r must come before specified directory."
	exit 1
    else
	findFiles $2 -r
    fi
elif [ $1 = '-r' ]
then
    findFiles '.' -r
else
    findFiles $1 -nr
fi

