## Lock Implementation (Assignment 7)

TL;DR : Exactly like the previous assignment.


In Main.java, all the locks are tested. A shared variable count is created whose value is incremented and decremented by two threads t1 and t2 respectively. At the end of the 'test', the value of the counter should always be 0. If the program outputs PASS, our lock implemetation works successfully.

Without LOCK implementation, the count value will not be 0 most of the times.


Throughput over here is calculated as number of operations done per second. Number of operation here is `num_of_iterations*2` since we increment the count 'num_of_iterations' times and then decrement it the same number of times.

Executing the program is easy. First compile the `<name_of_lock>_lock.java` file. Then in `Main.java`, uncomment the type of lock you want to execute (Line number : 9, 10, 11). Comment out the rest of the locks. Compile Main.java and then run it.

```
javac Main.java
java Main
```

Alternatively, just run `sh run.sh` in your terminal. Just make the change in Main.java. Execution will be done on it's own.

Name : Rounak Das
Roll Number : SE20UCSE149
