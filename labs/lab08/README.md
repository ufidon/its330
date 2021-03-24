# its330
Course materials and demos for labs

## Lab08: virtual memory allocation

### 1. Description

In this lab, practice virtual memory allocation using Windows API and C#.

### 2. Tasks (10%)

1. (5%) Practice reserving and committing virtual memory with template [rescom-mem.c](./code/win/rescom-mem.c) in Windows API.
2. (5%) Investigate C# program memory allocation with template [vmem.cs](./code/cs/vmem.cs) in C#.

### 3. Review questions (80%)
1. (10%) In demanding paging system, effective access time is directly proportional to the page-fault rate. If the page fault rate is 0.1%, i.e., one access out of 1,000 causes a page fault, find the slowdown (or performance degradation) percentage caused by page faults. Given,
   1. an average page-fault service time of 8 milliseconds
   2. and a memory access time of 200 nanoseconds

   Hints:

   (effective access time) = (1- page fault rate)× (memory access time) + (page fault rate)× (average page-fault service time)

   ( performance degradation) =[(effective access time) - (memory access time)]/(memory access time)
2. (30%) Find the number of page defaults of the reference string below

   4, 2, 1, 7, 9, 8, 3, 5, 2, 6, 8, 1, 0, 7, 2, 4, 1, 3, 5, 8

   for page replacement algorithms FIFO, LRU and OPT 
   1. (15%, 5% for each algorithm) given 3 frames
   2. (15%, 5% for each algorithm) Given 5 frames
3. (30%) The page table shown below is for a system with 16-bit virtual and physical addresses and with 4,096-byte pages. The reference bit is set to 1 when the page has been referenced. Periodically, a thread zeroes out all values of the reference bit. A dash for a page frame indicates the page is not in memory. The page-replacement algorithm is localized LRU, and all numbers are provided in decimal.
   1. (20%, 4% for each, %3 for the address, 1% for the reference bit) Convert the following virtual addresses (in hexadecimal) to the equivalent physical addresses. Provide answers in hexadecimal, also set the reference bit for the appropriate entry in the page table.

    |page | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 |
    | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
    |frame | 9 | 1 | 14 | 10 |  - | 13 | 8 | 15 | - | 0 | 5 | 4 | - | - | 3 | 2 |
    |ref bit | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |

      1. 0xE12C 
      2. 0x3A9D 
      3. 0xA9D9 
      4. 0x7001 
      5. 0xACA1

      Hints: 
      * page size = 4096 bytes, i.e. 2^12 bytes, so the left 4=16-12 bits of address are used for pages
      * page size = frame size
      * logical address = page number * page size + offset
      * physical address = frame number * frame size + offset

   2. (5%) Using the above addresses as a guide, provide an example of a logical address (in hexadecimal) that results in a page fault.
   3. (5%) From what set of page frames will the LRU page-replacement algorithm choose in resolving a page fault?

   Hints:
   The reference bit can NOT tell which page is referenced before which.

4. (10%) Find the number of pages allocated to the following three processes with proportional allocation from 100 pages. Suppose left pages are kept as free pages.
   1. process A of 20KB
   2. process B of 30KB
   3. process C of 50KB

   Hints:
   * memory A : memory B: memory C = process A : process B : process C
   * memory A + memory B + memory C <= total pages

5. (10%) Reading and writing
   1. (4%) Read the article [Virtual memory](https://en.wikipedia.org/wiki/Virtual_memory), write a summary about 
      1. the advantages and disadvantages of virtual memory, 
      2. the steps that operating systems used to handle page fault.
   2. (3%) Read the article [Thrashing](https://en.wikipedia.org/wiki/Thrashing_(computer_science)), write a summary about the causes and solutions of thrashing.
   3. (3%) Read the article [Bélády's anomaly](https://en.wikipedia.org/wiki/B%C3%A9l%C3%A1dy%27s_anomaly), write a summary about whether Belady's anomaly happens in FIFO, OPT and LRU.

   You may refer to [OSC9e Chapter 9](https://www.os-book.com/OS9/slide-dir/index.html), or [OSC10e Chapter 10](https://www.os-book.com/OS10/slide-dir/index.html) for further information.

**Demo video**

* [Lab08 Page replacement algorithms](https://youtu.be/ufktq7cHbd8)


## References

* Linux
  * [Memory](https://www.win.tue.nl/~aeb/linux/lk/lk-9.html)
  * [SystemProgramming](https://github.com/angrave/SystemProgramming/wiki)
  * [System Programming](http://cs241.cs.illinois.edu/coursebook/index.html)
  * [The Linux Kernel/Memory](https://en.wikibooks.org/wiki/The\_Linux\_Kernel/Memory)
  * [Virtual Memory and Linux](https://elinux.org/images/b/b0/Introduction\_to\_Memory\_Management\_in\_Linux\.pdf)
  * [The Right Way to Monitor Virtual Memory on Linux](https://www.logicmonitor.com/blog/the-right-way-to-monitor-virtual-memory-on-linux)
  * [Memory Management APIs](https://www.kernel.org/doc/html/latest/core-api/mm-api.html)
  * [Understanding the Linux® Virtual Memory Manager](https://pdos.csail.mit.edu/~sbw/links/gorman\_book.pdf)

* Windows
  * [Reserving and Committing Memory](https://docs.microsoft.com/en-us/windows/win32/memory/reserving-and-committing-memory)
  * [Virtual Address Space](https://docs.microsoft.com/en-us/windows/win32/memory/virtual-address-space)
  * [Virtual Memory Functions](https://docs.microsoft.com/en-us/windows/win32/memory/virtual-memory-functions)
  * [Managing Virtual Memory in Win32](https://www.labri.fr/perso/betrema/winnt/virtmm.html)

* C#
  * [Process.VirtualMemorySize64 Property](https://docs.microsoft.com/en-us/dotnet/api/system.diagnostics.process.virtualmemorysize64?view=netframework-4.8)
  * [Looking at .NET Memory Usage Using Performance Counters](https://csharp.2000things.com/tag/virtual-memory/)
  * [How to determine the appropriate page file size for 64-bit versions of Windows](https://docs.microsoft.com/en-us/windows/client-management/determine-appropriate-page-file-size)
  * [How To: Change the operating system's virtual memory settings](https://support.esri.com/en/technical-article/000002245)
* Java
  * [What is JVM?](http://www.javachain.com/core-java/java-virtual-memory/)
  * [Java Heap Space vs. Stack Memory: How Java Applications Allocate Memory](https://stackify.com/java-heap-vs-stack/)
  * [Java Memory Management for Java Virtual Machine (JVM)](https://betsol.com/java-memory-management-for-java-virtual-machine-jvm/)
  * [JVM tuning, How to control Virtual Memory size](https://liferay.dev/forums/-/message_boards/message/4680640)
  * [Virtual Memory Usage from Java under Linux, too much memory used](https://stackoverflow.com/questions/561245/virtual-memory-usage-from-java-under-linux-too-much-memory-used)

* C/C++
  * [Unix And C/C++ Runtime Memory Management For Programmers](https://scis.uohyd.ac.in/~atulcs/COOS/linux-internals/memory-management.html)



**Where are the codes and tools?**
* [Windows Sysinternals](https://docs.microsoft.com/en-us/sysinternals/)
* [BCC - Tools for BPF-based Linux IO analysis, networking, monitoring, and more](https://github.com/iovisor/bcc)
* [OSC10e](https://github.com/greggagne/osc10e)






