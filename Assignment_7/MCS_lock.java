import java.util.concurrent.atomic.AtomicReference;

public class MCS_lock {
    AtomicReference<QNode> tail;

    ThreadLocal<QNode> myNode;

    public MCS_lock(){
        tail = new AtomicReference<QNode>(null);
        myNode = new ThreadLocal<QNode>(){
            protected QNode initialValue(){
                return new QNode();
            }
        };
    }


    public void lock(){
        QNode qnode = myNode.get();
        QNode pred = tail.getAndSet(qnode);
        
        if(pred != null){
            qnode.locked = true;
            pred.next = qnode;
            while(pred.locked);
        }
    }

    public void unlock(){
        QNode qnode = myNode.get();

        if(qnode.next == null){
            if(tail.compareAndSet(qnode, null))
                return;
            
            while(qnode.next == null);
        }
        qnode.next.locked = false;
        qnode.next = null;
    }

    static class QNode{
        volatile boolean locked = false;
        volatile QNode next = null;
    }
}