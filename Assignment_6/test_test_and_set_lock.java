import java.util.concurrent.atomic.AtomicBoolean;

class test_test_and_set_lock{

    public AtomicBoolean state = new AtomicBoolean(false);

    public void lock(){
        while(true){
            while(state.get());

            if(!state.getAndSet(true)){
                return;
            }
        }
    }
    public void unlock(){
        state.set(false);

    }
    
}