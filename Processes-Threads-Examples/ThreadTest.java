import java.util.ArrayList;

public class ThreadTest {

  private ArrayList<Integer> sums;
  private static int n;
  private Thread[] threads; /* the thread identifier */
  private Runnable runner;

  public static void main(String[] args){

    if (args.length != 1) {
      System.err.println("usage: a.out <integer value>\n");
      System.exit(-1);
    }

    if (Integer.valueOf(args[0]) < 0) {
      System.err.printf("Argument %d must be non-negative\n",
        Integer.valueOf(args[0]));
        System.exit(-1);
    }

    n =  Integer.valueOf(args[0]);

    new ThreadTest();
  }

  public ThreadTest(){

    sums = new ArrayList<>();

    runner = new Runnable(){
      public void run(){
        int sum = 0;

        for (int j = 1; j <= n; j++)
          sum += j;

        addSum(sum);
      }
    };

    threads = new Thread[3];
    /* create the threads */
    for(int i=0; i<3; i++){
      threads[i] = new Thread(runner);
    }
    /* start the threads */
    for(int i=0; i<3; i++){
      threads[i].start();
    }

    /* now wait for the threads to exit */
    try{
      for(int i=0; i<3; i++){
         threads[i].join();
      }
    } catch (InterruptedException e){
      System.err.println("InterruptedException");
    }

    for(int i=0; i<3; i++){
        System.out.printf("sum = %d\n",sums.get(i));
    }

  }

  private synchronized void addSum(Integer sum){
    sums.add(sum);
  }
}
