/*
Refs:
https://docs.microsoft.com/en-us/dotnet/standard/threading/creating-threads-and-passing-data-at-start-time
https://docs.microsoft.com/en-us/dotnet/csharp/programming-guide/arrays/
*/

using System;
using System.Threading;

// The ThreadWithState class contains the information needed for
// a task, and the method that executes the task.
//
public class ThreadWithState
{
    // State information used in the task.
    private int start;
    private int end;
    public int sum = 0;

    // The constructor obtains the state information.
    public ThreadWithState(int s, int e)
    {
        start = s;
        end = e;
    }

    // The thread procedure performs the task, such as formatting
    // and printing a document.
    public void ThreadProc()
    {
        for( int i=start; i<=end; ++i)
        {
            sum += i;
        }
        Console.WriteLine(sum.ToString(), start.ToString(), end.ToString());
    }
}

// Entry point for the example.
//
public class Example
{
    public static void Main()
    {
        // Supply the state information required by the task.
        int totalSum = 0;
        ThreadWithState[] tws = new ThreadWithState[10];
        Thread[] t = new Thread[10];

        for(int i=0; i<10; ++i)
        {
            tws[i] = new ThreadWithState(
                i*1000+1, (i+1)*1000);

            // Create a thread to execute the task, and then
            // start the thread.
            t[i] = new Thread(new ThreadStart(tws[i].ThreadProc));
            t[i].Start();
            t[i].Join();
        }
        Console.WriteLine("Main thread does some work, then waits.");
        for(int i=0; i<10; ++i)
        {
            t[i].Join();
        }
        
        for(int i=0; i<10; ++i)
        {
            totalSum += tws[i].sum;
        }        
        Console.WriteLine(
            totalSum.ToString()
            );         
    }
}
// The example displays the following output:
//       Main thread does some work, then waits.
//       This report displays the number 42.
//       Independent task has completed; main thread ends.