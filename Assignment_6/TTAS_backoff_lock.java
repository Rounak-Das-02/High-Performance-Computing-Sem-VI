import java.util.concurrent.ThreadLocalRandom;
import java.util.concurrent.atomic.AtomicBoolean;

class Backoff{
    final int minDelay, maxDelay;
    int limit;

    Backoff(int min, int max){
        minDelay = min;
        maxDelay = max;
        limit = minDelay;
    }

    public void backOff(){
        try{
            int delay = ThreadLocalRandom.current().nextInt(limit);
            limit = Math.min(maxDelay, 2*limit);
            Thread.sleep(delay);
        }
        catch(Exception e){

        }

    }
}




class TTAS_backoff_lock{

    public AtomicBoolean state = new AtomicBoolean(false);
    private static final int MIN_DELAY = 2;
    private static final int MAX_DELAY = 10;

    public void lock(){
        Backoff backoff = new Backoff(MIN_DELAY, MAX_DELAY);

        while(true){
            while(state.get());

            if(!state.getAndSet(true)){
                return;
            }
            else{
                backoff.backOff();
            }
        }
    }
    public void unlock(){
        state.set(false);

    }
    
}