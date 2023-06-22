import java.util.concurrent.atomic.AtomicInteger;

class Main{

    static int num_of_iteration = 100000;
    static int count = 0; // Testing lock without using AtomicInteger


    // static test_and_set_lock lock = new test_and_set_lock();
    static CLH_lock lock = new CLH_lock();
    // static TTAS_backoff_lock lock = new TTAS_backoff_lock();

    public static void main(String args[]){
        
        Thread t1 = new Thread(new Incrementer()); // This increments count

        Thread t2 = new Thread(new Decrementer()); // This decrements count


        long start = System.currentTimeMillis();
        t1.start();
        t2.start();
        
        try{
            t1.join();
            t2.join();
        }
        catch(Exception e){
        }

        // At the end of the execution of thread. 
        if (count == 0){
            System.out.println("PASS");
            System.out.println("Throughput (OPS) = " +  (num_of_iteration*2)/(System.currentTimeMillis() - start)*Math.pow(10,-3)) ;
        }
        else
            System.out.println("FAIL");

    }

    private static class Incrementer implements Runnable{
        public void run(){
            for(int i = 0 ; i < num_of_iteration; i++){
                lock.lock();
                // System.out.println("Thread 1");
                count++;
                lock.unlock();
            }
        }
}

    private static class Decrementer implements Runnable{
        public void run(){
            for(int i = 0 ; i < num_of_iteration; i++){
                lock.lock();
                // System.out.println("Thread 2");
                count--;
                lock.unlock();
            }
        }
}
}