## Peterson's Lock Algorithm

I have implemented Peterson's lock using `PetersonLock.java`. It has two functions, lock() and unlock().

In Main.java, Peterson's lock is tested. A shared variable counter is created whose value is incremented and decremented by two threads t1 and t2 respectively. At the end of the 'test', the value of the counter should always be 0. If the program outputs PASS, our lock implemetation works successfully.

The code is executed multiple times with multiple values in the loop. We got PASS everytime.

To execute the piece of code, run the script file in the same directory.


`sh run.sh`

Name : Rounak Das
Roll Number : SE20UCSE149
