# its330
Course materials and demos for labs

## Lab02: Create processes

**1.Description**

In this lab,  create processes on Windows using Windows API and C#.


**2.Tasks(80%, each process 10%)**
The four processes below must be: File explorer, MS paint, Snipping tool and Event viewer.

1. Design, code, compile and test a console program using Windows API to create four processes.
2. Design, code, compile and test a console program using C# to create four processes.

**3.Review questions(20%)**
1. (10%) What is the purpose of [system calls](https://en.wikipedia.org/wiki/System_call)?
2. (10%) List examples of Windows API and Linux system calls. Refer to [System Call in OS: Types and Examples](https://www.guru99.com/system-call-operating-system.html). Complete the following table, each cell must be filled with **at least 5 functions**.

A comparison of Linux system calls and Windows API

| services | Linux system calls | Windows API |
| ------- | ----------------- | ----------- |
| Process Control	|  |  |
| File Manipulation	|  |  |
| Device Manipulation	|  |  |
| Information Maintenance	|  |  |
| Communication	|  |  |
| Security and Protection	|  |  |

* [Searchable Linux Syscall Table for x86 and x86_64](https://filippo.io/linux-syscall-table/)
  * [Classification and Grouping of
Linux System Calls](http://seclab.cs.sunysb.edu/sekar/papers/syscallclassif.htm)
* [Complete list of Windows API](https://docs.microsoft.com/en-us/windows/win32/apiindex/windows-api-list)
  * [List of Microsoft Windows application programming interfaces and frameworks](https://en.wikipedia.org/wiki/List_of_Microsoft_Windows_application_programming_interfaces_and_frameworks)
  * [Windows X86 System Call Table](https://j00ru.vexillium.org/syscalls/nt/32/)

## References
1. Use [Linux process API](http://faculty.salina.k-state.edu/tim/CMST302/study_guide/topic8/multi.html) to create processes
2. Use [Windows API](https://docs.microsoft.com/en-us/windows/win32/procthread/processes-and-threads) to create processes
3. Create processes using [C# Process class](https://docs.microsoft.com/en-us/dotnet/api/system.diagnostics.process?view=netframework-4.8)
4. Create processes using [Java.lang.Process calss](https://www.geeksforgeeks.org/java-lang-process-class-java/)

**Where are the codes and tools?** 
* [Windows Sysinternals](https://docs.microsoft.com/en-us/sysinternals/)
* [BCC - Tools for BPF-based Linux IO analysis, networking, monitoring, and more](https://github.com/iovisor/bcc)
* [OSC10e](https://github.com/greggagne/osc10e)

**Youtube Videos**
  * [parent children relationship between windows processes](https://youtu.be/xf4G962ObAY)
  * [create child processes using C#](https://youtu.be/i7kf7DAxLL8)
  * [parent children relationship between Linux processes](https://youtu.be/SGlbhKXSFeQ)




