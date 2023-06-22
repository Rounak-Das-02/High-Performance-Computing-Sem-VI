import java.util.*;

class PetersonLock{
    private final boolean flag[] = {false, false}; // Other threads get to know 
    private volatile int turn = 0; // Volatile ensures that other threads can see the change in the variable.

    public void lock(int i){
        int j = 1 - i;
        flag[i] = true;
        turn = j;
        while(flag[j] && turn == j);
    }

    public void unlock(int i){
        flag[i] = false;
    }

}