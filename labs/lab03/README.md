# its330
Course materials and demos for labs

## Lab03: Create threads

### 1. Description
If a task can be divided into several parallel subtasks, then each subtask can be done with a thread, and their results can be aggregated by the process they reside. Computing efficiency can be improved in this way.

In this lab,  create threads on Windows using Windows API and C# to compute the average of large amount of data.

### 2. Tasks (40%) 
1. Use the Windows API template is [win_sum.c](./code/win/win_sum.c) to find the average number of 1,2,3,...,10000 with 10 threads, then use a calculator to verify your result. The average value should be (1+10000)/2.
   1. (10%) Design/code/compile/run the program to get the average
   2. (10%) Verify the result using a calculator
2. Use the C# template is [cs_sum.c](./code/cs/cs_sum.cs) to find the average number of 1,2,3,...,50000 with 10 threads, then use a calculator to verify your result. The average value should be (1+50000)/2.
   1. (10%) Design/code/compile/run the program to get the average
   2. (10%) Verify the result using a calculator


### 3. Review questions (60%) 
Show your calculation steps for each question, without steps will be graded 0.

1. (20%) Using Amdahl’s Law, calculate the speedup gain of an application that has a 60 percent parallel component for
   1. (10%) two processing cores.
   2. (10%) four processing cores.
  

2. (40%)Suppose that the following processes arrive for execution at the times indicated. Each process will run for the amount of time (burst time) listed. In answering the questions, use nonpreemptive scheduling, and base all decisions on the information you have at the time the decision must be made.

   | Process | Arrival Time | Burst Time |
   | ------- | ------------ | ---------- |
   | P1 | 0.0 | 8 |
   | P2 | 0.4 | 4 |
   | P3 | 1.0 | 1 |

   1. (10%) What is the average turnaround time (from arrival to complete run) for these processes with the FCFS scheduling algorithm?
   2. (10%) What is the average turnaround time for these processes with the SJF scheduling algorithm?
   3. (20%) The SJF algorithm is supposed to improve performance, but notice that we chose to run process P1 at time 0 because we did not know that two shorter processes would arrive soon. Compute what the average turnaround time will be if the CPU is left idle for the first 1 unit and then SJF scheduling is used. Remember that processes P1 and P2 are waiting during this idle time, so their waiting time may increase. This algorithm could be called future-knowledge scheduling.

**Demo video**

* [Lab03 Create Threads](https://youtu.be/n4Kj2LyJVD4)

## References
* Linux
  * [pthreads - POSIX threads](http://man7.org/linux/man-pages/man7/pthreads.7.html)
  * [POSIX thread (pthread) libraries](https://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.html)
  * [POSIX Threads Programming](https://computing.llnl.gov/tutorials/pthreads/)
  * [Multithreaded Programming (POSIX pthreads Tutorial)](https://randu.org/tutorials/threads/)
  * [Linux signals](https://www.win.tue.nl/~aeb/linux/lk/lk-5.html)
  * [TLS performance overhead and cost on GNU/Linux](http://david-grs.github.io/tls_performance_overhead_cost_linux/)
* Windows
  * [About Processes and Threads](https://docs.microsoft.com/en-us/windows/win32/procthread/about-processes-and-threads)
  * [Creating Threads](https://docs.microsoft.com/en-us/windows/win32/procthread/creating-threads)
  * [processthreadsapi.h header](https://docs.microsoft.com/en-us/windows/win32/api/processthreadsapi/)
  * [Thread Pools](https://docs.microsoft.com/en-us/windows/win32/procthread/thread-pools)
  * [Using the Thread Pool Functions](https://docs.microsoft.com/en-us/windows/win32/procthread/using-the-thread-pool-functions)
  * [Thread Local Storage](https://docs.microsoft.com/en-us/windows/win32/procthread/thread-local-storage)
* C#
  * [Using threads and threading](https://docs.microsoft.com/en-us/dotnet/standard/threading/using-threads-and-threading)
  * [Thread Class](https://docs.microsoft.com/en-us/dotnet/api/system.threading.thread?view=netframework-4.8)
    * [Getting the unique identifier for the current managed thread](https://www.geeksforgeeks.org/c-sharp-getting-the-unique-identifier-for-the-current-managed-thread/)
    * [How to tell if a thread is the main thread in C#](https://stackoverflow.com/questions/2374451/how-to-tell-if-a-thread-is-the-main-thread-in-c-sharp)
  * [Threading in C#](http://www.albahari.com/threading/)
  * [The managed thread pool](https://docs.microsoft.com/en-us/dotnet/standard/threading/the-managed-thread-pool)
  * [Thread Local Storage: Thread-Relative Static Fields and Data Slots](https://docs.microsoft.com/en-us/dotnet/standard/threading/thread-local-storage-thread-relative-static-fields-and-data-slots)
* Java
  * [Java threads](https://docs.oracle.com/javase/tutorial/essential/concurrency/threads.html)
  * [How to create thread](https://www.javatpoint.com/creating-thread)
  * [Creating and Starting Java Threads](http://tutorials.jenkov.com/java-concurrency/creating-and-starting-threads.html)
  * [Thread Pools](https://docs.oracle.com/javase/tutorial/essential/concurrency/pools.html)
  * [Java ThreadLocal](http://tutorials.jenkov.com/java-concurrency/threadlocal.html)

* OpenMP
  * [OpenMP](https://www.openmp.org/)

* [Partition](https://en.wikipedia.org/wiki/Partition_(number_theory))
  * [Floor and ceiling functions](https://en.wikipedia.org/wiki/Floor_and_ceiling_functions)
  * [Amdahl's law](https://en.wikipedia.org/wiki/Amdahl%27s\_law)

**Where are the codes and tools?**
* [Windows Sysinternals](https://docs.microsoft.com/en-us/sysinternals/)
* [BCC - Tools for BPF-based Linux IO analysis, networking, monitoring, and more](https://github.com/iovisor/bcc)
* [OSC10e](https://github.com/greggagne/osc10e)
* [The program pstree and htop showing threads with unique PIDS. How is this possible?](https://unix.stackexchange.com/questions/166207/the-program-pstree-and-htop-showing-threads-with-unique-pids-how-is-this-possib)
* [How can I view the active threads of a running program?](https://superuser.com/questions/462969/how-can-i-view-the-active-threads-of-a-running-program)
* [Understanding Process Explorer](https://www.howtogeek.com/school/sysinternals-pro/lesson2/)
* [Controlling Processes and Threads in WinDbg](https://docs.microsoft.com/en-us/windows-hardware/drivers/debugger/processes-and-threads-window)

**Youtube Videos**
  * [Create threads in C# on Windows Server](https://youtu.be/mql8VjnMOME)
  * [Create threads in Linux API on Ubuntu](https://youtu.be/eG0m2Mb5OY8)
  * [Create threads in Windows API on Windows Server](https://youtu.be/PIXg_JME5_A)




