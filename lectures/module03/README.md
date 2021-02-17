# its330
Course materials and demos for lectures


## Module03: Non-persistent Storage resource management

### Main memory
* _Concepts_
 * [Computer data storage](https://en.wikipedia.org/wiki/Computer\_data\_storage)
 * [Computer memory](https://en.wikipedia.org/wiki/Computer\_memory)
   * [Memory hierarchy](https://en.wikipedia.org/wiki/Memory\_hierarchy)
   * [Locality of reference](https://en.wikipedia.org/wiki/Locality\_of\_reference)
   * [Endianness](https://en.wikipedia.org/wiki/Endianness)
 * [Semiconductor memory](https://en.wikipedia.org/wiki/Semiconductor\_memory)
   * [Dynamic random-access memory](https://en.wikipedia.org/wiki/Dynamic\_random\-access\_memory)
     * [Memory geometry](https://en.wikipedia.org/wiki/Memory\_geometry)
   * [DDR SDRAM](https://en.wikipedia.org/wiki/DDR\_SDRAM)
* _Addressing_
  * [Memory address](https://en.wikipedia.org/wiki/Memory\_address)
    * [Logical and Physical Address in Operating System](https://www.geeksforgeeks.org/logical-and-physical-address-in-operating-system/)
    * [Memory segmentation](https://en.wikipedia.org/wiki/Memory_segmentation)
      * [X86 memory segmentation](https://en.wikipedia.org/wiki/X86_memory_segmentation)
        * [Intel Memory Model](https://en.wikipedia.org/wiki/Intel_Memory_Model)
          * [Real mode](https://en.wikipedia.org/wiki/Real_mode)
          * [Protected mode](https://en.wikipedia.org/wiki/Protected_mode)
          * [Long mode](https://en.wikipedia.org/wiki/Long_mode)
    * [Flat memory model](https://en.wikipedia.org/wiki/Flat\_memory\_model)
    * [Address space](https://en.wikipedia.org/wiki/Address\_space)
      * [Virtual address space](https://en.wikipedia.org/wiki/Virtual\_address\_space)
        * [Mapping Virtual Addresses to Physical Addresses](https://www.geeksforgeeks.org/mapping-virtual-addresses-to-physical-addresses/)
        * [Memory address register](https://en.wikipedia.org/wiki/Memory\_address\_register)
* _Youtube videos_
  * [Memory management](https://www.youtube.com/playlist?list=PLskQvPDUk0sJnmLgi4qBRyshlmHydbsAJ)

### Memory partition
* _Concepts_
  * [Fixed (or static) Partitioning in Operating System](https://www.geeksforgeeks.org/fixed-or-static-partitioning-in-operating-system/)
  * [Variable (or dynamic) Partitioning in Operating System](https://www.geeksforgeeks.org/variable-or-dynamic-partitioning-in-operating-system/)
  * [Paging](https://en.wikipedia.org/wiki/Paging)
    * [Page table](https://en.wikipedia.org/wiki/Page\_table)
      * [Page (computer memory)](https://en.wikipedia.org/wiki/Page\_\(computer\_memory\))
      * [Page Table Entries in Page Table](https://www.geeksforgeeks.org/page-table-entries-in-page-table/)
    * [Paging in Operating System](https://www.geeksforgeeks.org/paging-in-operating-system/)
    * [Inverted Page Table in Operating System](https://www.geeksforgeeks.org/inverted-page-table-in-operating-system/)
    * [Hashed Page Tables in Operating System](https://www.geeksforgeeks.org/hashed-page-tables-in-operating-system/)
    * [Two Level Paging and Multi Level Paging in OS](https://www.geeksforgeeks.org/two-level-paging-and-multi-level-paging-in-os/)
      * [Multilevel Paging in Operating System](https://www.geeksforgeeks.org/multilevel-paging-in-operating-system/)
  * [Memory segmentation](https://en.wikipedia.org/wiki/Memory\_segmentation)
    * [Segmentation in Operating System](https://www.geeksforgeeks.org/segmentation-in-operating-system/)
    * [x86 memory segmentation](https://en.wikipedia.org/wiki/X86\_memory\_segmentation)
    * [Object file](https://en.wikipedia.org/wiki/Object\_file)
      * [Code segment](https://en.wikipedia.org/wiki/Code\_segment)
      * [Data segment](https://en.wikipedia.org/wiki/Data\_segment)
      * [.bss](https://en.wikipedia.org/wiki/\.bss)
    * [Segmentation fault](https://en.wikipedia.org/wiki/Segmentation\_fault)
    * [Intel Memory Model](https://en.wikipedia.org/wiki/Intel\_Memory\_Model)
    * [AMD64](https://en.wikipedia.org/wiki/AMD64)
    * [IA-64](https://en.wikipedia.org/wiki/IA\-64)

### Cache
* _Concepts_
  * [CPU cache](https://en.wikipedia.org/wiki/CPU\_cache)
    * [Cache ](https://en.wikipedia.org/wiki/Cache\_\(computing\))
    * [Cache hierarchy](https://en.wikipedia.org/wiki/Cache\_hierarchy)
    * [Cache prefetching](https://en.wikipedia.org/wiki/Cache\_prefetching)
    * [Cache replacement policies](https://en.wikipedia.org/wiki/Cache\_replacement\_policies)
      * [Cache coloring](https://en.wikipedia.org/wiki/Cache\_coloring)
  * [Cache coherence](https://en.wikipedia.org/wiki/Cache\_coherence)
    * [Bus snooping](https://en.wikipedia.org/wiki/Bus\_snooping)
    * [Directory-based cache coherence](https://en.wikipedia.org/wiki/Directory-based\_cache\_coherence)
  * [Cache stampede](https://en.wikipedia.org/wiki/Cache\_stampede)
    * [Cascading failure](https://en.wikipedia.org/wiki/Cascading\_failure)

### Memory management
* [Memory management](https://en.wikipedia.org/wiki/Memory_management)
  * [Non-Contiguous Allocation in Operating System](https://www.geeksforgeeks.org/non-contiguous-allocation-in-operating-system/)
  * [Free list](https://en.wikipedia.org/wiki/Free_list)
  * [Buddy memory allocation](https://en.wikipedia.org/wiki/Buddy_memory_allocation)
    * [Buddy System – Memory allocation technique](https://www.geeksforgeeks.org/buddy-system-memory-allocation-technique/)
  * [Memory pool](https://en.wikipedia.org/wiki/Memory_pool)
    * [Slab allocation](https://en.wikipedia.org/wiki/Slab_allocation)
    * [Object pool pattern](https://en.wikipedia.org/wiki/Object_pool_pattern)
  * [Partition Allocation Methods in Memory Management](https://www.geeksforgeeks.org/partition-allocation-methods-in-memory-management/)
    * [First-Fit Allocation](https://www.geeksforgeeks.org/first-fit-allocation-in-operating-systems/)
      * [program](https://www.geeksforgeeks.org/program-first-fit-algorithm-memory-management/)
      * [next-fit program](https://www.geeksforgeeks.org/program-for-next-fit-algorithm-in-memory-management/)
    * [Best-Fit Allocation](https://www.geeksforgeeks.org/best-fit-allocation-in-operating-system/)
      * [program](https://www.geeksforgeeks.org/program-best-fit-algorithm-memory-management/)
    * [Worst-Fit Allocation](https://www.geeksforgeeks.org/worst-fit-allocation-in-operating-systems/)
      * [program](https://www.geeksforgeeks.org/program-worst-fit-algorithm-memory-management/)
    * [Overlays in Memory Management](https://www.geeksforgeeks.org/overlays-in-memory-management/)
  * [C dynamic memory allocation](https://en.wikipedia.org/wiki/C\_dynamic\_memory\_allocation)
  * [Stack-based memory allocation](https://en.wikipedia.org/wiki/Stack-based\_memory\_allocation)
* [Fragmentation (computing)](https://en.wikipedia.org/wiki/Fragmentation_(computing))

### Virtual memory

* _Concepts_
  * [Virtual memory](https://en.wikipedia.org/wiki/Virtual\_memory)
    * [Virtual Memory in Operating System](https://www.geeksforgeeks.org/virtual-memory-in-operating-system/)
    * [Memory management unit](https://en.wikipedia.org/wiki/Memory\_management\_unit)
    * [Memory protection](https://en.wikipedia.org/wiki/Memory\_protection)
    * [Page replacement algorithm](https://en.wikipedia.org/wiki/Page\_replacement\_algorithm)
      * [Dirty bit](https://en.wikipedia.org/wiki/Dirty\_bit)
      * [Page cache](https://en.wikipedia.org/wiki/Page\_cache)
        * [Translation lookaside buffer](https://en.wikipedia.org/wiki/Translation_lookaside_buffer)
      * [Demand paging](https://en.wikipedia.org/wiki/Demand\_paging)
      * [Page fault](https://en.wikipedia.org/wiki/Page_fault)
        * [Bélády's anomaly](https://en.wikipedia.org/wiki/B%C3%A9l%C3%A1dy%27s_anomaly)
        * [Storage violation](https://en.wikipedia.org/wiki/Storage_violation)
      * [Page Replacement Algorithms in Operating Systems](https://www.geeksforgeeks.org/page-replacement-algorithms-in-operating-systems/)
  * [Virtual Memory in Operating System](https://www.geeksforgeeks.org/virtual-memory-in-operating-system/)
    * [How Virtual Memory Works](https://computer.howstuffworks.com/virtual-memory.htm)
    * [An Introduction to Virtual Memory in Windows](https://www.c-sharpcorner.com/uploadfile/SamTomato/an-introduction-to-virtual-memory-in-windows/)
      * [What is Performance Monitor telling me when my page faults / second are high?](https://superuser.com/questions/240578/what-is-performance-monitor-telling-me-when-my-page-faults-second-are-high)
        * [The Basics of Page Faults](https://techcommunity.microsoft.com/t5/ask-the-performance-team/the-basics-of-page-faults/ba-p/373120)
        * [Memory pages per second](https://docs.microsoft.com/en-us/azure/monitoring/infrastructure-health/vmhealth-windows/winserver-memory-pagespersec)
* _Youtube videos_
  * [Virtual memory](https://www.youtube.com/playlist?list=PLiwt1iVUib9s2Uo5BeYmwkDFUh70fJPxX)


### Popular operating systems and libraries
* _Linux_
  * [Virtual Memory and Linux](https://elinux.org/images/b/b0/Introduction\_to\_Memory\_Management\_in\_Linux\.pdf)
  * [Some details about Linux memory management](https://www2.cs.duke.edu/courses/spring04/cps210/projects/mmlinux.html)
  * [Memory Management](https://www.kernel.org/doc/html/latest/admin-guide/mm/index.html)
  * [LDP Memory Management](https://www.tldp.org/LDP/tlk/mm/memory.html)
  * [Kernel Memory Management Source Code](https://elixir.bootlin.com/linux/latest/source/mm)
  * [proc - process information pseudo-filesystem](http://man7.org/linux/man-pages/man5/proc.5.html)
  * [Complete virtual memory map with 4-level page tables](https://www.kernel.org/doc/Documentation/x86/x86\_64/mm.txt)
  * [The Memory Layout of a 64-bit Linux Process](https://simonis.github.io/Memory/)
  * [Understanding the Memory Layout of Linux Executables](https://gist.github.com/CMCDragonkai/10ab53654b2aa6ce55c11cfc5b2432a4)
  * [Understanding glibc malloc](https://sploitfun.wordpress.com/2015/02/10/understanding-glibc-malloc/)

* _Windows_
  * [Memory Management](https://docs.microsoft.com/en-us/windows/win32/memory/memory-management)
  * [Anatomy of a Program in Memory](https://manybutfinite.com/post/anatomy-of-a-program-in-memory/)
* _C#_
  * [Memory Management and Garbage Collection in .NET](https://docs.microsoft.com/en-us/dotnet/standard/garbage-collection/memory-management-and-gc)
  * [Memory Management in .NET](https://www.c-sharpcorner.com/article/memory-management-in-net/)
  * [C# Memory Management - Part 1](https://medium.com/c-programming/c-memory-management-part-1-c03741c24e4b)
  * [Find, Fix, and Avoid Memory Leaks in C# .NET: 8 Best Practices](https://michaelscodingspot.com/find-fix-and-avoid-memory-leaks-in-c-net-8-best-practices/)
* _Java_
  * [Understanding Memory Management](https://docs.oracle.com/cd/E13150_01/jrockit_jvm/jrockit/geninfo/diagnos/garbage_collect.html)
  * [Memory Management in Java](https://www.javatpoint.com/memory-management-in-java)
  * [Java Memory Management](https://dzone.com/articles/java-memory-management)
  * [Java Memory Management](https://www.geeksforgeeks.org/java-memory-management/)
* _FreeRTOS_
  * [Static Vs Dynamic Memory Allocation](https://www.freertos.org/Static\_Vs\_Dynamic\_Memory\_Allocation\.html)
* _C/C++_
  * [C++](http://www.cplusplus.com/reference/new/)
  * [C](http://www.cplusplus.com/reference/cstdlib/malloc/)

