#!/bin/bash

gcc BMM_transpose.c -o BMM_transpose -fopenmp

number_of_threads=(1 2 4 6 8 10 12 14 16)
# number_of_threads=(1 2 4 6 8)
n=(2 3 4 5 6 7 8 9 10 11 12 13 14 15 16)
# n=( 2 3 4)
order=( 512 1024 2048)

block_size=( 4 8 16 32 64)


for b in "${block_size[@]}"
do
for i in "${n[@]}"
do 
    for j in "${number_of_threads[@]}"
    do 
        echo -ne "$j""\t" >> "fixed_size_A""$i""_block_"$b".txt"
        for k in "${order[@]}"
        do
            ./BMM_transpose $k $i $j $b "fixed_size_A""$i""_block_"$b".txt"
            
        done
        echo -ne "\n" >> "fixed_size_A""$i""_block_"$b".txt"
    done
done
done


for b in "${block_size[@]}"
do
for i in "${n[@]}"
do 
    for j in "${order[@]}"
    do 
        echo -ne "$j""\t" >> "fixed_size_A""$i""_block_"$b".txt"
        for k in "${number_of_threads[@]}"
        do
            ./BMM_transpose $k $i $j $b "fixed_size_A""$i""_block_"$b".txt"
            
        done
        echo -ne "\n" >> "fixed_size_A""$i""_block_"$b".txt"
    done
done
done



# echo Hello'\n'world >> test.txt
