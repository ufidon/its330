// https://docs.microsoft.com/en-us/dotnet/api/system.threading.thread.currentthread?view=netframework-4.8
// https://docs.microsoft.com/en-us/dotnet/api/system.threading.thread.sleep?view=netframework-4.8

using System;
using System.Collections.Generic;
using System.Threading;
using System.Threading.Tasks;

public class Example
{
   private static Object lockObj = new Object();
   private static Object rndLock = new Object();

   public static void Main()
   {
      Random rnd = new Random();
      var tasks = new List<Task<Double>>();
      ShowThreadInformation("Application");

      Task<Double> t = Task.Run( () => { ShowThreadInformation("Main Task(Task #" + Task.CurrentId.ToString() + ")");
                                         for (int ctr = 1; ctr <= 20; ctr++)
                                           tasks.Add(Task.Factory.StartNew(
                                              () => { ShowThreadInformation("Task #" + Task.CurrentId.ToString());
                                                      long s = 0;
                                                      for (int n = 0; n <= 999999; n++) {
                                                         lock (rndLock) {
                                                            s += rnd.Next(1, 1000001);
                                                         }
                                                      }

                                                      Thread.Sleep(100000);
                                                      return s/1000000.0;
                                                    } ));

                                        Task.WaitAll(tasks.ToArray());
                                        Double grandTotal = 0;
                                        Console.WriteLine("Means of each task: ");
                                        foreach (var child in tasks) {
                                           Console.WriteLine("   {0}", child.Result);
                                           grandTotal += child.Result;
                                        }
                                        Console.WriteLine();
                                        return grandTotal / 20;
                                   } );
      Console.WriteLine("Mean of Means: {0}", t.Result);
   }

  private static void ShowThreadInformation(String taskName)
  {
      String msg = null;
      Thread thread = Thread.CurrentThread;
      lock(lockObj) {
         msg = String.Format("{0} thread information\n", taskName) +
               String.Format("   Background: {0}\n", thread.IsBackground) +
               String.Format("   Thread Pool: {0}\n", thread.IsThreadPoolThread) +
               String.Format("   Thread ID: {0}\n", thread.ManagedThreadId);
      }
      Console.WriteLine(msg);
   }
}
