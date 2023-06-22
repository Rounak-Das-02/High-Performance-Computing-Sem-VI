import java.util.concurrent.atomic.AtomicReference;

public class CLH_lock {
    AtomicReference <QNode> tail;

    ThreadLocal <QNode> myPred;
    ThreadLocal <QNode> myNode;

    public CLH_lock(){
        tail = new AtomicReference<QNode>(new QNode());
        myNode = new ThreadLocal<QNode>(){
            protected QNode initialValue(){
                return new QNode();
            }
        };
        myPred = new ThreadLocal<QNode>(){
            protected QNode initialValue(){
                return null;
            }
        };
    }


    public void lock(){
        QNode qnode = myNode.get();
        qnode.locked = true;
        QNode pred = tail.getAndSet(qnode);
        myPred.set(pred);
        while(pred.locked);
    }

    public void unlock(){
        QNode qnode = myNode.get();
        qnode.locked = false;
        myNode.set(myPred.get());
    }

    class QNode{
        volatile boolean locked = false;
    }
}