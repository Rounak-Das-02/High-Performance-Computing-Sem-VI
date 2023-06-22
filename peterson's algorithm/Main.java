import java.util.*;
import java.util.concurrent.atomic.AtomicInteger;

class Main{
    private static AtomicInteger counter = new AtomicInteger(0);
    private static PetersonLock lock = new PetersonLock();

    public static void main(String args[]){
        Thread t1 = new Thread(new Incrementer());
        // Thread t2 = new Thread(new Incrementer());
        Thread t2 = new Thread(new Decrementer());

        // Starting the threads

        t1.start();
        t2.start();


        try{
            t1.join();
            t2.join();
        }
        catch(Exception e){
            e.printStackTrace();
        }

        System.out.println("Final Counter Value : " + counter);

        // If Peterson's lock is executed correctly, 
        if(counter.get() == 0){
            System.out.println("PASS");
        }
        else{
            System.out.println("FAIL");
        }
    }


private static class Incrementer implements Runnable{
    public void run(){
        for(int i = 0 ; i < 10000; i++){
            lock.lock(0);
            counter.incrementAndGet();
            lock.unlock(0);
        }
    }
}

private static class Decrementer implements Runnable{
    public void run(){
        for(int i = 0 ; i < 10000; i++){
            lock.lock(1);
            counter.decrementAndGet();
            lock.unlock(1);
        }
    }
}

}

