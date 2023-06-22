## Assignment 3:

---

### Problem 1 - Threshold:

We have created two programs for the same program. One is threshold.c which uses OpenMP to generate the binary image, whereas the second one is threshold_opti.c which uses hashing to generate binary image.
The threshold_opti.c program is much faster (a lot actually) than the OpenMP program in this case.

We ran the programs in IT2 HPC lab and in super computer lab. Some of the speed ups that we noted are listed below:

SpeedUp for 1024 x 1024 when 16 threads were used = 5219.786 / 446.27 = 11.70
SpeedUp for 1024 x 1024 when 14 threads were used = 5219.786 / 497.12 = 10.51
SpeedUp for 1024 x 1024 when 12 threads were used = 5219.786 / 583.16 = 8.95

SpeedUp for 2048 x 2048 when 16 threads were used = 6013.124 / 489.76 = 12.277695198
SpeedUp for 2048 x 2048 when 14 threads were used = 6013.124 / 511.65 = 11.752416691
SpeedUp for 2048 x 2048 when 12 threads were used = 6013.124 / 678.23 = 8.865906846

gen.py is added to generate random square matrices of size n. n is a variable inside gen.py
After that, we can use the new generated text file as an input to our thresholding program.

```
gcc threshold.c -o threshold -fopenmp
./threshold <size of array> <input file> <output file>
```

---

### Problem 2 - Matrix Chain Multiplication:

The number of matrices is hardcoded here as 10. You can change it. Also, we initialize the matrixes with random values.

Speed Up with 1024 x 1024 matrix size = 0.642106 / 0.215082 = 2.985400917
Speed Up with 2048 x 2048 matrix size = 4.184850 / 1.321365 = 3.167065875

---

### Problem 3 - Conway's Game of Life

We have created a python script `gen_seed.py` which creates n x n 2D matrix of values 0.
`conway2.c` generates the new state of the board.

Initial configuration has only few simple oscillators.
Source : [Click here](http://jakevdp.github.io/blog/2013/08/07/conways-game-of-life/`)

With 1024 Steps:
SpeedUp for 1024 x 1024 when 8 threads were used = 40.643529 / 14.211967 = 2.859810257
SpeedUp for 1024 x 1024 when 16 threads were used = 40.643529 / 6.015873 = 6.756048374

To run the file :

```
gcc conway2.c -o conway2 -fopenmp
./conway2 <input file> <rows> <columns> <#steps> <output file>
```

Note : collapse(2) is used so that each thread gets a pair of (i,j) instead of only i i.e row

---

Team 53:

1. Abhinav Chaudhry - SE20UCSE006
2. Rounak Das - SE20UCSE149
3. Manoj Singh Tomer - SE20UCSE094
4. Rohith Dandi - SE20UCSE148
5. Leela Aravinda - SE20UCSE077
