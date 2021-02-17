# its330
Course materials and demos for labs


## Lab07: memory allocation

### 1. Description

In this lab,  practice memory allocation using Windows API and C#.

### 2. Tasks (40%)

1. (20%) Practice application of memory-mapped file with template [share1.c](./code/win/share1.c), [share2.c](./code/win/share2.c) in Windows API.
2. (20%) Find the dot Net garbage collector information with template [gs.cs](./code/cs/gc.cs) in C#.

### 3. Review questions (60%)
1. (15%, 5% each algorithm) Given six memory partitions of 300 KB, 600 KB, 350 KB, 200 KB, 750 KB, and 125 KB (in order), how would the first-fit, best-fit, and worst-fit algorithms place processes of size 115 KB, 500 KB, 358 KB, 200 KB, and 375 KB (in order)? Find the total internal fragmentation and the total external fragmentation for each algorithm.
2. (10%, 5% each) Assuming a 1-KB page size, what are the page numbers and offsets for the following address references (provided as decimal numbers):
   1. 3085
   2. 42095
3. (10%) Consider a paging system with the page table stored in memory.
   1. (4%) If a memory reference takes 50 nanoseconds, how long does a paged memory reference take?
   2. (6%) If we add TLBs, and 75 percent of all page-table references are found in the TLBs, what is the effective memory reference time? (Assume that finding a page-table entry in the TLBs takes 2 nanoseconds, if the entry is present.)
4. (12%, 4% each)Consider the following segment table: 

   | Segment | Base | Length |
   | -- | ---- | ----- |
   | 0 | 219   | 600 |
   | 1 | 2300  | 14  |
   | 2 | 90    | 100 |
   | 3 | 1327  | 580 |
   | 4 | 1952  | 96  |

   What are the physical addresses for the following logical addresses?

   | segment | offset |
   | ------- | ------ |
   | 0 | 430 |
   | 3 | 400 |
   | 2 | 500 |

5. (13%) Suppose in a computer system, 8bits for logical address space with 4 bits for page number and 4 bits for page offset, 12 bits for physical address space with 8 bits frame number and 4 bits for frame offset. Give page table: 197,144,206,232,132,93,111,203,10,3,90,122,217,244,170,147 
   1. (4% each) Find the physical addresses for logical addresses: 99, 233
   2. (5%) What is the logical address generate physical address 3261?

## References
* Linux
  * [mmap](http://man7.org/linux/man-pages/man2/mmap.2.html)
  * [shm_overview](http://man7.org/linux/man-pages/man7/shm\_overview.7.html)

* Windows
  * [Creating Named Shared Memory](https://docs.microsoft.com/en-us/windows/win32/memory/creating-named-shared-memory)
  * [Enumerating a Heap](https://docs.microsoft.com/en-us/windows/win32/memory/enumerating-a-heap)

* C#
  * [GC Class](https://docs.microsoft.com/en-us/dotnet/api/system.gc?view=netframework-4.8)
  * [new operator](https://docs.microsoft.com/en-us/dotnet/csharp/language-reference/operators/new-operator)
  * [Object and Collection Initializers](https://docs.microsoft.com/en-us/dotnet/csharp/programming-guide/classes-and-structs/object-and-collection-initializers)
  * [Garbage Collection in C# | .NET Framework](https://www.geeksforgeeks.org/garbage-collection-in-c-sharp-dot-net-framework/)
* Java
  * [Garbage Collection in Java](https://www.geeksforgeeks.org/garbage-collection-java/)
  * [How to prevent objects of a class from Garbage Collection in Java](https://www.geeksforgeeks.org/how-to-prevent-objects-of-a-class-from-garbage-collection-in-java/)
* C/C++
  * [malloc](http://www.cplusplus.com/reference/cstdlib/malloc/)
  * [Dynamic Memory Allocation and Fragmentation in C and C++](https://www.design-reuse.com/articles/25090/dynamic-memory-allocation-fragmentation-c.html)
  * [Dynamic memory](http://www.cplusplus.com/doc/tutorial/dynamic/)
  * [Dynamic allocation in C/C++](http://www.cplusplus.com/articles/G6vU7k9E/)
  * [new and delete operators](https://docs.microsoft.com/en-us/cpp/cpp/new-and-delete-operators?view=vs-2019)
  * [Memory-Allocation Routines in C](https://docs.microsoft.com/en-us/cpp/c-runtime-library/memory-allocation?view=vs-2019)


**Where are the codes and tools?**
* [Windows Sysinternals](https://docs.microsoft.com/en-us/sysinternals/)
* [BCC - Tools for BPF-based Linux IO analysis, networking, monitoring, and more](https://github.com/iovisor/bcc)
* [OSC10e](https://github.com/greggagne/osc10e)






