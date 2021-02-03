# its330
Course materials and demos for labs

## Lab05: process/thread synchronization

### 1. Description

In this lab,  demonstrate the use of synchronization primitives below on Windows:
* semaphore in Windows API
* monitor in C#

### 2. Tasks (20%)
1. (10%) Using template [semaphore.c](./code/win/semaphore.c), simulate the scenario that 10 computers print on 5 printers.
2. (10%) Using template [monitor.cs](./code/cs/monitor.cs), analyze the scenario of using Monitor for synchronization.

### 3. Review questions (80%)
1. Consider the following set of processes, with the length of the CPU burst and arrival time given in milliseconds:
   
   | Process | Arrival Time | Burst Time | Priority |
   | ------- | ------------ | ---------- | -------- |
   | P1 | 1 | 2 | 2 |
   | P2 | 0 | 1 | 1 |
   | P3 | 2 | 8 | 4 |
   | P4 | 1 | 4 | 2 |
   | P5 | 3 | 5 | 3 |

   The processes are assumed to have arrived in the order P2, P1, P4, P3, P5 as indicated,  and use the following scheduling algorithms: FCFS, preemptive SJF (same job length then FCFS) or SRTF, preemptive priority (a larger priority number implies a higher priority, same priority then FCFS), and RR (time slice or quantum = 2).
   1. (20%, 5% for each algorithm) Draw four Gantt charts that illustrate the execution of these processes.
   2. (20%，5% for each algorithm) What is the turnaround time of each process for each of the scheduling algorithms.
   3. (20%，5% for each algorithm) What is the waiting time of each process for each of these scheduling algorithms?
   4. (20%，5% for each algorithm) Which of the algorithms results in the minimum average waiting time (over all processes)?


## References
* Linux
  * [POSIX thread (pthread) libraries](https://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.html)
  * [POSIX Threads Programming](https://computing.llnl.gov/tutorials/pthreads/)
* Windows
  * [Using Semaphore Objects](https://docs.microsoft.com/en-us/windows/win32/sync/using-semaphore-objects)
* C#
  * [Monitor Class](https://docs.microsoft.com/en-us/dotnet/api/system.threading.monitor?view=netframework-4.8)
* Java
  * [High Level Concurrency Objects](https://docs.oracle.com/javase/tutorial/essential/concurrency/highlevel.html)


**Where are the codes and tools?**
* [Windows Sysinternals](https://docs.microsoft.com/en-us/sysinternals/)
* [BCC - Tools for BPF-based Linux IO analysis, networking, monitoring, and more](https://github.com/iovisor/bcc)
* [OSC10e](https://github.com/greggagne/osc10e)


**Youtube Videos**
* [synchronization](https://youtu.be/GpTDNMjXsFM)




