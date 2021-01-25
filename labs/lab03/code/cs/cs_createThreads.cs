// https://docs.microsoft.com/en-us/dotnet/api/system.threading.thread?view=netframework-4.8
// https://docs.microsoft.com/en-us/dotnet/standard/threading/creating-threads-and-passing-data-at-start-time

using System;
using System.Threading;

// Simple threading scenario:  Start a static method running
// on a second thread.
public class ThreadExample {
    // The ThreadProc method is called when the thread starts.
    // It loops ten times, writing to the console and yielding 
    // the rest of its time slice each time, and then ends.
    public static void ThreadProc() {
        for (int i = 0; i < 10; i++) {
           
            Console.WriteLine("ThreadProc: {0}", i);
            // Yield the rest of the time slice.
            Thread.Sleep(0);
        }
    }

    public static void Main() {
        Console.WriteLine("Main thread: Start a second thread.");
        // The constructor for the Thread class requires a ThreadStart 
        // delegate that represents the method to be executed on the 
        // thread.  C# simplifies the creation of this delegate.
        Thread t1 = new Thread(new ThreadStart(ThreadProc));

        Console.WriteLine("Main thread: Start a third thread.");
        Thread t2 = new Thread(new ThreadStart(ThreadProc));

        // Start ThreadProc.  Note that on a uniprocessor, the new 
        // thread does not get any processor time until the main thread 
        // is preempted or yields.  Uncomment the Thread.Sleep that 
        // follows t.Start() to see the difference.
        t1.Start();
        t2.Start();
        //Thread.Sleep(0);

        for (int i = 0; i < 4; i++) {
            Console.WriteLine("Main thread: Do some work.");
            Thread.Sleep(0);
        }

        Console.WriteLine("Main thread: Call Join(), to wait until ThreadProc ends.");
        t1.Join();
        t2.Join();
        Console.WriteLine("Main thread: ThreadProc.Join has returned.  Press Enter to end program.");
        Console.ReadLine();
    }
}