# its330
Course materials and demos for labs

## Lab04: thread's scheduling

### 1. Description
In this lab,  get/set thread's priority on Windows using Windows API and create a custom task scheduler using C#.


### 2. Tasks(20%) 
1. (10%) Create one thread on Windows using Windows API, show its default thread priority, change its priority to a different one then show it again. 
2. (10%) Create a custom task scheduler using C#, and show the threads.

### 3. Review questions(80%)
1. Consider the following set of processes, with the length of the CPU burst given in milliseconds:
   
   | Process | Burst Time | Priority |
   | ------- | ---------- | -------- |
   | P1 | 2 | 2 |
   | P2 | 1 | 1 |
   | P3 | 8 | 4 |
   | P4 | 4 | 2 |
   | P5 | 5 | 3 |

   The processes are assumed to have arrived in the order P1, P2, P3, P4, P5, all at time 0, and use the following scheduling algorithms: FCFS, SJF (same job length then FCFS), nonpreemptive priority (a larger priority number implies a higher priority, same priority then FCFS), and RR (quantum = 2).
   1. (20%, 5% for each algorithm) Draw four Gantt charts that illustrate the execution of these processes.
   2. (20%，5% for each algorithm) What is the turnaround time of each process for each of the scheduling algorithms.
   3. (20%，5% for each algorithm) What is the waiting time of each process for each of these scheduling algorithms?
   4. (20%，5% for each algorithm) Which of the algorithms results in the minimum average waiting time (over all processes)?

**Demo video**

* [Lab04: Thread scheduling](https://youtu.be/32r97obGzMs)

## References
* Linux
  * [POSIX Threads Programming](https://computing.llnl.gov/tutorials/pthreads/)
  * [pthread scheduling](http://man7.org/linux/man-pages/man3/pthread_getschedparam.3.html)
* Windows
  * [Scheduling Priorities](https://docs.microsoft.com/en-us/windows/win32/procthread/scheduling-priorities)
  * [SetThreadPriority function](https://docs.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-setthreadpriority?redirectedfrom=MSDN)
  * [Processes, Threads, and Jobs in the Windows Operating System](https://www.microsoftpressstore.com/articles/article.aspx?p=2233328&seqNum=7)
* C#
  * [Scheduling threads](https://docs.microsoft.com/en-us/dotnet/standard/threading/scheduling-threads)
  * [TaskScheduler Class](https://docs.microsoft.com/en-us/dotnet/api/system.threading.tasks.taskscheduler?view=netframework-4.8)
* Java
  * [Java 101: Understanding Java threads, Part 3: Thread scheduling and wait/notify](https://www.javaworld.com/article/2071214/java-101--understanding-java-threads--part-3--thread-scheduling-and-wait-notify.html)
  * [Thread Scheduling](https://www.math.uni-hamburg.de/doc/java/tutorial/essential/threads/priority.html)


**Where are the codes and tools?**
* [Windows Sysinternals](https://docs.microsoft.com/en-us/sysinternals/)
* [BCC - Tools for BPF-based Linux IO analysis, networking, monitoring, and more](https://github.com/iovisor/bcc)
* [OSC10e](https://github.com/greggagne/osc10e)


**Youtube Videos**
* [scheduling of threads](https://youtu.be/a2eShvUibf8)




