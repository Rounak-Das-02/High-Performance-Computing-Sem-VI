/*SenseBarrier.java */
import java.util.concurrent.atomic.AtomicInteger;

public class SenseBarrier implements Barrier {
  AtomicInteger count;     // how many threads have arrived
  int size;                // number of threads
  volatile boolean sense;  // object's sense
  ThreadLocal<Boolean> threadSense;
  
  public SenseBarrier(int n) {
    count = new AtomicInteger(n);
    size = n;
    sense = false;
    threadSense = new ThreadLocal<Boolean>();
    // threadSense.set(!sense);
    threadSense = new ThreadLocal<Boolean>() {
      protected Boolean initialValue() { return !sense; };
    };
  }
  /**
   * Wait for threads to catch up.
   */
  public void await() {
    boolean mySense = threadSense.get();
    int position = count.getAndDecrement();
    if (position == 1) { // I'm last
      count.set(this.size);     // reset counter
      sense = mySense;        // reverse sense 
     }else{
      while (sense != mySense) {} // busy-wait
    }
    threadSense.set(!mySense);
  }
}
