# its330
Course materials and demos for labs

## Lab06: deadlock

### 1. Description
In this lab,  practice deadlock in [the Philosopher Dining Problem](https://en.wikipedia.org/wiki/Dining\_philosophers\_problem) using Windows API and C#.

### 2. Tasks (50%)
1. (25%) Using template [diningPhilosophers.c](./code/win/diningPhilosophers.c) in Windows API, simulate the deadlock scenario that 5 philosophers dining 10 rounds.
2. (25%) Using template [DiningPhilosophers2.cs](./code/cs/DiningPhilosophers2.cs) in C#, simulate the deadlock scenario that 5 philosophers dining 10 rounds.

### 3. Review questions (50%)
1. Given the following snapshot of a system, answer the questions below using the banker's algorithm.
   | process | allocation | max  | available   |
   | ------- | ---------- | ---  | ---------   |
   |         | A B C D | A B C D | A B C D |
   | P0      | 0 0 1 2 | 0 0 1 2 | 1 5 2 0 |
   | P1      | 1 0 0 0 | 1 7 5 0 | |
   | P2      | 1 3 5 4 | 2 3 5 6 | |
   | P3      | 0 6 3 2 | 0 6 5 2 | |
   | P4      | 0 0 1 4 | 0 6 5 6 | |
   
   1. (10%) What is the content of matrix need?
   2. (20%) Is the system in a safe state?
   3. (20%) If a request from process P1 arrives for (0,4,2,0), can the request be granted immediately?


## References

* Linux
  * [POSIX thread (pthread) libraries](https://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.html)
  * [POSIX Threads Programming](https://computing.llnl.gov/tutorials/pthreads/)
  * [The Dining Philosophers Source File](https://docs.oracle.com/cd/E19205-01/820-0619/gepji/index.html)
  * [Dining Philosopher Problem Using Semaphores](https://www.geeksforgeeks.org/dining-philosopher-problem-using-semaphores/)
  * [ThreadMentor: The Dining Philosophers Problem](https://pages.mtu.edu/~shene/NSF-3/e-Book/MUTEX/TM-example-philos-1.html)
* Windows
  * [Using Mutex Objects](https://docs.microsoft.com/en-us/windows/win32/sync/using-mutex-objects)
  * [Walkthrough: Using join to Prevent Deadlock](https://docs.microsoft.com/en-us/cpp/parallel/concrt/walkthrough-using-join-to-prevent-deadlock?view=vs-2019)
* C#
  * [Mutex Class](https://docs.microsoft.com/en-us/dotnet/api/system.threading.mutex?view=netframework-4.8)
* Java
  * [Deadlock](https://docs.oracle.com/javase/tutorial/essential/concurrency/deadlock.html)
  * [Dining Philosophers](https://www.doc.ic.ac.uk/~jnm/concurrency/classes/Diners/Diners.html)
* [Dining philosophers](https://rosettacode.org/wiki/Dining_philosophers)

**Where are the codes and tools?**
* [Windows Sysinternals](https://docs.microsoft.com/en-us/sysinternals/)
* [BCC - Tools for BPF-based Linux IO analysis, networking, monitoring, and more](https://github.com/iovisor/bcc)
* [OSC10e](https://github.com/greggagne/osc10e)






