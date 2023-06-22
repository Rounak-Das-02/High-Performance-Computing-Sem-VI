class Matrix{
                int rows;
                int cols;
                int[][] ele;
                Matrix(int m, int n){
                        rows=m; cols=n;
                        ele=new int[rows][cols];
                }
                void printMatrix(){
                        for(int i=0;i<rows;i++){
                                for(int j=0;j<cols;j++)
                                        System.out.print(ele[i][j]+"  ");
                                System.out.print("\n");
                        }
                }
		void readMatrix(){
			for(int i=0;i<rows;i++){
				for(int j=0;j<cols;j++){ ele[i][j]=1; }
			}
		}
}
class MatrixMulti{
SenseBarrier sb1;	

void multiply(int tid){
		for(int i=tid;i<A.rows;i=i+THREADS)
		for(int j=0;j<B.cols;j++){
		C.ele[i][j]=0;	
		for(int k=0;k<A.cols;k++)
			C.ele[i][j]+=A.ele[i][k]*B.ele[k][j];
		}
}


void multiply(){               
                for(int i=0;i<A.rows;i++)
                for(int j=0;j<B.cols;j++)
                for(int k=0;k<A.cols;k++)
                        C.ele[i][j]+=A.ele[i][k]*B.ele[k][j];
}


void copy(int tid){
	for(int i=tid;i<B.rows;i=i+THREADS)
	for(int j=0;j<B.cols;j++){ B.ele[i][j]=C.ele[i][j]; }
}



void readMatrices(){ A.readMatrix(); B.readMatrix(); }
void printMat(){ C.printMatrix(); }	
Matrix A,B,C;
int THREADS, pow;
Thread th[];
MatrixMulti(int num_th, int N, int P){
	sb1=new SenseBarrier(num_th);

	THREADS=num_th;
	pow=P;
	A=new Matrix(N,N);
	B=new Matrix(N,N);
	C=new Matrix(N,N);
	th=new Thread[THREADS];

}


public void testParallel()throws Exception{
	for(int i=0;i<THREADS;i++){ th[i]=new CreateThread(); }
	for(int i=0;i<THREADS;i++){ th[i].start(); }
	for(int i=0;i<THREADS;i++){ th[i].join(); }	
}



class CreateThread extends Thread{
	public void run(){
 		int tid=ThreadID.get();
		for(int i=1;i<=pow;i++){
		multiply(tid);
		sb1.await();
		copy(tid);
		sb1.await();
		}
	}
}
}


class ThreadID {
  // The next thread ID to be assigned
  private static volatile int nextID = 0;
  // My thread-local ID.
  private static ThreadLocalID threadID = new ThreadLocalID();
  public static int get(){
    return threadID.get();
  }
  public static void reset(){
    nextID = 0;
  }
  private static class ThreadLocalID extends ThreadLocal<Integer> {
    protected synchronized Integer initialValue() {
      return nextID++;
    }
  }
}



public class MyMatrixOP {
    MatrixMulti instance;
    MyMatrixOP(int num_th, int N, int P){
        instance=new MatrixMulti(num_th,N,P);
    }
    public static void main(String args[]) {
	int num_th=Integer.parseInt(args[0]);
	int N=Integer.parseInt(args[1]);
	int P=Integer.parseInt(args[2]);
	MyMatrixOP ob=new MyMatrixOP(num_th,N,P);
	ob.instance.readMatrices();
	int processors = Runtime.getRuntime().availableProcessors();
		System.out.println("CPU cores: " + processors);
	long start=System.currentTimeMillis();
	try{ ob.instance.testParallel();} 
	catch(Exception e){ System.out.println(e); }
	long end=System.currentTimeMillis();
		System.out.println(end-start);
		ob.instance.printMat();
}
}
