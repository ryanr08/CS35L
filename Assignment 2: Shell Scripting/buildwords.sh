#!/bin/bash

cat $1 |
tr '[:upper:]' '[:lower:]' |
sed -n 28,1285p |
sed 's/<[^>]*>//g' |
sed  '/[^ pkmnwlhaeiou\` ]/d' |
tr '`' "\'" |
sed 's/[ ]*//g' |
sort -u
