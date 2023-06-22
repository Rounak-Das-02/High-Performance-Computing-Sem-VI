/* SimpleBarrier.java */
import java.util.concurrent.atomic.AtomicInteger;

public class SimpleBarrier implements Barrier {
  AtomicInteger count;
  int size;
  public SimpleBarrier(int n){
    this.count = new AtomicInteger(n);
    this.size = n;
  }
  public void await() {
    int position = count.getAndDecrement();
    if (position == 1) {         // If I'm last ...
      count.set(size);	         // reset for next use
    } else {			 // otherwise spin
      while (count.get() != 0) {}
    }
  }
}
