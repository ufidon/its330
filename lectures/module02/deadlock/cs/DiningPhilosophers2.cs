/** Ref:
* 1. https://docs.microsoft.com/en-us/dotnet/csharp/programming-guide/classes-and-structs/how-to-define-constants
* 2. https://docs.microsoft.com/en-us/dotnet/api/system.threading.monitor?view=netframework-4.8
* 3. https://www.dotnetforall.com/correct-way-provide-input-parameter-task/
* 4. https://docs.microsoft.com/en-us/dotnet/api/system.threading.tasks.task.waitall?view=netframework-4.8
* 5. https://docs.microsoft.com/en-us/dotnet/api/system.console.readkey?view=netframework-4.8
* How to compile and run?
* On Ubuntu: 
* Compile: mcs diningphilosophers2.cs
* Run: ./diningphilosophers2.exe
* On Windows:
* Compile: csc diningphilosophers2.cs
* Run: .\diningphilosophers2.exe
*/
using System;
using System.Collections.Generic;
using System.Threading;
using System.Threading.Tasks;


static class Configs
{
    public const int N = 5;
    public const int ROUNDS = 10;

    public static readonly int[] EAT = {1000,4000,100,3000,500};
    public static readonly int[] THINK = {2000,100,500,200,3000};
    public static readonly int[] SLOTH = {5000,5000,5000,5000,5000};
}



public class DiningPhilosophers
{

     
     public static Random rnd = new Random();
     public static object[] chopsticks = new object[Configs.N];

    

   public static void Main()
   {

    Func<object, int> philosopher = (object obj) =>
    {
        
        int r = Configs.ROUNDS;
        int pID = (int)obj;

        while (r>=0)
        {
            Console.WriteLine("Philosopher {0} is THINKING...\n", pID);
            Thread.Sleep(Configs.THINK[pID]);

            Console.WriteLine("Philosopher {0} is trying picking up his LEFT chopstick\n", pID);
            Monitor.Enter(chopsticks[pID]);
            Console.WriteLine("Philosopher {0} picked up his LEFT chopstick\n", pID);

            /** TODO:
            * 1. compile, run, observe, describe your observation
            * 2. comment out line 66, compile, run, observe, describe your observation
            * 3. explain the difference
            */

            Thread.Sleep(Configs.SLOTH[pID]);
            Console.WriteLine("Philosopher {0} is SLOTHING...\n", pID);

            Console.WriteLine("Philosopher {0} is trying picking up his RIGHT chopstick\n", pID);
            Monitor.Enter(chopsticks[(pID+1)%Configs.N]);
            Console.WriteLine("Philosopher {0} picked up his RIGHT chopstick\n", pID);

            Console.WriteLine("Philosopher {0} has two chopsticks\n", pID);
            Console.WriteLine("Philosopher {0} is dining now...\n", pID);
            Thread.Sleep(Configs.EAT[pID]);

            Console.WriteLine("Philosopher {0} put down his RIGHT chopstick\n", pID);
            Monitor.Exit(chopsticks[(pID+1)%Configs.N]);
            Console.WriteLine("Philosopher {0} put down his LEFT chopstick\n", pID);
            Monitor.Exit(chopsticks[pID]);


            --r;
        }

        Console.WriteLine("Philosopher {0} LEFT\n", pID);
        return pID;
    };


        var philosophers = new List<Task<int>>();

       Console.WriteLine("The philosophers party BEGINS...\n");
        Console.WriteLine("================================\n");

      for (int pID = 0; pID < Configs.N; pID++)
      {
          int id = pID;
        Console.WriteLine("Philosopher {0} is COMING...\n", pID);
        chopsticks[id] = new object();
          philosophers.Add(Task<int>.Factory.StartNew(philosopher, id));
      }
         


    
      try {
         Task.WaitAll(philosophers.ToArray());
         Console.WriteLine("================================\n");
         Console.WriteLine("The philosophers party is OVER...\n");
      }
      catch (AggregateException e) {
         foreach (var ie in e.InnerExceptions)
            Console.WriteLine("{0}:--: {1}", ie.GetType().Name, ie.Message);
      }

   }
}
