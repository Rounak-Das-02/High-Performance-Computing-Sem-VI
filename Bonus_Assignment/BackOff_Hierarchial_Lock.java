import java.util.concurrent.atomic.AtomicInteger;

class BackOff_Hierarchial_Lock {

    private static final int LOCAL_MIN_DELAY = 4;
    private static final int LOCAL_MAX_DELAY = 6;
    private static final int REMOTE_MIN_DELAY = 2;
    private static final int REMOTE_MAX_DELAY = 6;

    private static final int FREE = -1;
    AtomicInteger state;



    public BackOff_Hierarchial_Lock(){
        state = new AtomicInteger(FREE);
    }

    public void lock(){

        int myCluster = ThreadID.getCluster();
    }

    public void unlock(){
        int slot = slotIndex.get();
        flag[slot] = false;
        flag[(slot+1)%size] = true;        
    }
}

