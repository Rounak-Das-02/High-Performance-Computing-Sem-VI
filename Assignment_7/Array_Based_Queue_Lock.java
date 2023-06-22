import java.util.concurrent.atomic.AtomicInteger;

class Array_Based_Queue_Lock {

    ThreadLocal <Integer> slotIndex = new ThreadLocal<Integer>(){
        protected Integer initialValue(){
            return 0;
        }
    };

    AtomicInteger tail;
    volatile boolean flag[];
    int size;



    public Array_Based_Queue_Lock(int size){
        this.size = size;
        this.tail = new AtomicInteger(0);
        flag = new boolean[size];
        flag[0] = true; // 0th thread has permission to acquire lock
    }

    public void lock(){
        int slot = tail.getAndIncrement() % size;
        slotIndex.set(slot);
        while(!flag[slot]);

    }

    public void unlock(){
        int slot = slotIndex.get();
        flag[slot] = false;
        flag[(slot+1)%size] = true;        
    }
}