Assignment 1:

We tried the codes in HPC IT Lab first. Since we had to wait for a long time over there, we decided to use Super Computer for the same. The codes were run in separate tmux terminals, mostly at night or at times when the usage of super computer was low and threads were idle.

OMM and OMM-transpose are pretty easy. We have used a construct called collapse over there, for which each thread gets their own private pair (i,j).
OMM-transpose is the same as OMM, but we multiple here row and row. Since C stores arrays in Row major order, we benefit from temporal cache here. Hence, the run time of OMM-transpose is better than normal OMM.

For running the OMM files, you can execute the following in the terminal:

`./OMM sizeOfMatrix powerOfMatrix numberOfThreads  file_name`

For running the OMM_transpose program, you can execute the following in the terminal :

`./OMM_transpose sizeOfMatrix  powerOfMatrix numberOfThreads file_name`

Same concept applies for BMM and BMM-transpose. Here we just use block sizes to use the functionality of temporal caches. BMM-transpose uses the advantage of Row-major order also.

For running the BMM files, you can execute the following in the terminal:

`./BMM sizeOfMatrix  powerOfMatrix numberOfThreads block_size file_name`

For running the BMM_transpose program, you can execute the following in the terminal :

`./BMM_transpose  sizeOfMatrix powerOfMatrix numberOfThreads block_size file_name`

The outputs are provided in the respective folders!

We have created bash script for generating files also.
run1, run2, run3, and run4 are the bash files for respective question numbers.

Team 53:

1. Abhinav Chaudhry - SE20UCSE006
2. Rounak Das - SE20UCSE149
3. Manoj Singh Tomer - SE20UCSE094
4. Rohith Dandi - SE20UCSE148
5. Leela Aravinda - SE20UCSE077
