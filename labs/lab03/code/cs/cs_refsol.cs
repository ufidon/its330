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
    private int id;
    public int sum = 0;

    // The constructor obtains the state information.
    public ThreadWithState(int s, int e, int i)
    {
        start = s;
        end = e;
        id = i;
    }

    // The thread procedure performs the task, such as formatting
    // and printing a document.
    public void ThreadProc()
    {
        for( int i=start; i<=end; ++i)
        {
            sum += i;
        }
        Console.WriteLine("Thread "+ id.ToString() + ": calculates sum from "+start.ToString()+" to "+ end.ToString() + " , gets " + sum.ToString());
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
        double average;

        ThreadWithState[] tws = new ThreadWithState[10];
        Thread[] t = new Thread[10];

        for(int i=0; i<10; ++i)
        {
            tws[i] = new ThreadWithState(
                i*5000+1, (i+1)*5000, i);

            // Create a thread to execute the task, and then
            // start the thread.
            t[i] = new Thread(new ThreadStart(tws[i].ThreadProc));
            t[i].Start();
            t[i].Join();
        }
        
        for(int i=0; i<10; ++i)
        {
            t[i].Join();
        }
        Console.WriteLine("All child threads termininated.");

        for(int i=0; i<10; ++i)
        {
            totalSum += tws[i].sum;
        }

        average = totalSum / 50000.0;        
        Console.WriteLine("1+2+3+...+50000 = " + totalSum.ToString());   
        Console.WriteLine("The average of 1, 2, 3, ..., 50000 is: " + average.ToString());       
    }
}
