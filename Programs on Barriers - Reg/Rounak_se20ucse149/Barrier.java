/* Barrier.java */

public interface Barrier {
  /**
   * Block until all threads have reached barrier.
   */
  public void await();
}
