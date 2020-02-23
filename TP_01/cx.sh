#!/bin/bash
ext=".c"
exe=".o"
echo "Input file to be executed"
read file
new="${file}${ext}"
exe="${file}${exe}"
if [ -e file ]
then
    rm file
fi
if [ -e exe ]
then
    rm exe
fi
gcc -Wall -o $file $new
if [ $? -ne 0 ]
then
    echo "COMPILATION ERROR"
else
    ./$file
fi