import java.util.concurrent.atomic.AtomicBoolean;

class test_and_set_lock{

    public AtomicBoolean state = new AtomicBoolean(false);

    public void lock(){
        while(state.getAndSet(true));
    }
    public void unlock(){
        state.set(false);

    }
    
}