#!/bin/bash

javac *.java

size=1
for((j=200000;j<=20000000;j=j*10)); do
	for((k=1;k<=16;)); do
        echo "Thread: $k, Workload 1"
		echo -n $k >> DataForSize-$size.dat
		java List_Test $k $j 100000 10 100 100 >> DataForSize-$size.dat

        echo "Thread: $k, Workload 2"

		java List_Test $k $j 100000 10 70 90 >> DataForSize-$size.dat

        echo "Thread: $k, Workload 3"

		java List_Test $k $j 100000 10 50 75 >> DataForSize-$size.dat

        echo "Thread: $k, Workload 4"

		java List_Test $k $j 100000 10 30 65 >> DataForSize-$size.dat

        echo "Thread: $k, Workload 5"

		java List_Test $k $j 100000 10 0 50 >> DataForSize-$size.dat
		
		if [ $k -eq 1 ]; #Thread 2 comes after Thread 1
		then
			k=$(($k+1))
		else
			k=$(($k+2))
		fi
	echo >> DataForSize-$size.dat
	done
	size=$(($size+1))
done
