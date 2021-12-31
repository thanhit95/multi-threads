/*
 * SYNCHRONIZED BLOCKS
 * Version B: Synchronized instance methods
 *
 * Synchronized methods have two effects:
 *
 * First, it is not possible for two invocations of synchronized methods on the same object to interleave.
 * When one thread is executing a synchronized method for an object,
 * all other threads that invoke synchronized methods for the same object block (suspend execution)
 * until the first thread is done with the object.
 *
 * Second, when a synchronized method exits, it automatically establishes a happens-before relationship
 * with any subsequent invocation of a synchronized method for the same object.
 * This guarantees that changes to the state of the object are visible to all threads.
 */

package demo14;

import java.util.stream.IntStream;



public class AppB01 {

    public static void main(String[] args) throws InterruptedException {
        final int NUM_THREADS = 3;


        var lstTh = IntStream.range(0, NUM_THREADS).mapToObj(i -> new WorkerB01()).toList();


        for (var th : lstTh)
            th.start();

        for (var th : lstTh)
            th.join();


        System.out.println("counter = " + WorkerB01.counter);
        /*
         * We are NOT sure that counter = 30000
         */
    }

}



class WorkerB01 extends Thread {
    public static int counter = 0;


    @Override
    public synchronized void run() {
        try { Thread.sleep(500); } catch (InterruptedException e) { }

        for (int i = 0; i < 10000; ++i) {
            ++counter;
        }
    }
}