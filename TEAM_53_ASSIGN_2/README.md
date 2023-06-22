Assignment 2:

We tried the codes in HPC IT Lab first. Since we had to wait for a long time over there, we decided to use Super Computer for the same. The codes were run in separate tmux terminals, mostly at night or at times when the usage of super computer was low and threads were idle.

For the first question of merge sort, using 1 thread it took 7.31093947 s,
using 2 threads it took 3.9270362700000003, thus the speed up observed = 1.8616939002704957
using 4 threads it took 2.40623757, thus the speed up observed = 3.0383282021483855
using 6 threads it took 1.81749474 , thus the speed up observed = 4.022536796997827.
using 8 threads it took 1.6085989, thus the speed up observed = 4.544911394630445
using 10 threads it took 1.649941 , thus the speed up observed = 4.431030848981872.
using 12 threads it took 1.67051071 , thus the speed up observed = 4.376469678545192.
using 14 threads it took 1.66402902 thus the speed up observed = 4.393516808979689
using 16 threads it took 1.54170733 , thus the speed up observed = 4.742105928756271.

Just like the first problem, we can observe a similiar trend of decrease in run time as we increase the no. of threads. If you look into the code, we ran an outer loop to alter the number of Ns in N-Queen problem.
You need to input the number of threads.

Team 53:

1. Abhinav Chaudhry - SE20UCSE006
2. Rounak Das - SE20UCSE149
3. Manoj Singh Tomer - SE20UCSE094
4. Rohith Dandi - SE20UCSE148
5. Leela Aravinda - SE20UCSE077
