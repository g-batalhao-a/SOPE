#!/bin/bash
counter=2
tp="TP_"
with="${tp}0"
while [ $counter -le 15 ]
do
    if [ $counter -le 9 ]
    then
        mkdir ${with}$counter
    else
        mkdir ${tp}$counter
    fi
    ((counter++))
done