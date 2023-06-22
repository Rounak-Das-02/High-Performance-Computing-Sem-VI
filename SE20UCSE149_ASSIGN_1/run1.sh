#!/bin/bash

gcc OMM.c -o OMM -fopenmp

number_of_threads=(1 2 4 6 8 10 12 14 16)
# number_of_threads=(1 2 4 6 8)
n=(2 3 4 5 6 7 8 9 10 11 12 13 14 15 16)
# n=( 2 3 4)
order=( 512 1024 2048)


for i in "${n[@]}"
do 
    for j in "${number_of_threads[@]}"
    do 
        echo -ne "$j""\t" >> "fixed_size_A""$i"
        for k in "${order[@]}"
        do
            ./OMM $k $i $j "fixed_size_A""$i"
            
        done
        echo -ne "\n" >> "fixed_size_A""$i"
    done
done



for i in "${n[@]}"
do 
    for j in "${order[@]}"
    do 
        echo -ne "$j""\t" >> "fixed_thread_A""$i"
        
        for k in "${number_of_threads[@]}"
        do
            ./OMM $k $i $j "fixed_thread_A""$i"
            
        done
        echo -ne "\n" >> "fixed_thread_A""$i"
    done
done



# echo Hello'\n'world >> test.txt
