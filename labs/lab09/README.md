# its330
Course materials and demos for labs

## Lab09: file system API

### 1. Description

In this lab,  practice file operations with file system interfaces below:
1. file system API in Windows using Windows API
2. file system classes using C#

### 2. Tasks (40%)

1. (20%) Practice creating, moving and deleting files; reading, manipulating and writing file contents with template [tempfile.c](./code/win/tempfile.c) in Windows API
2. (20%) Practice traversing folders and files; reading and displaying file contents with template [patternedfile.cs](./code/cs/patternedfile.cs) in C#

### 3. Review questions (60%)
1. (12%) Read articles [Hard disk drive](https://en.wikipedia.org/wiki/Hard_disk_drive) and [Solid-state drive](https://en.wikipedia.org/wiki/Solid-state_drive), answer questions below:
   1.  (6%) What are the major factors that affect the performance of magnetic disks?
   2.  (6%) Do solid-state disks suffer from these factors?

2. (12%, each algorithm 2%) Read article [Disk Scheduling Algorithms](https://www.geeksforgeeks.org/disk-scheduling-algorithms/) and write a summary about these disk scheduling algorithms: FCFS, SSTF, SCAN, C-SCAN, LOOK, C-LOOK.

3. (36%) Find the total head movements in cylinder for disk scheduling algorithms FCFS, SSTF, SCAN, C-SCAN, LOOK and C-LOOK with the following disk queue with requests for I/O to blocks on cylinders: 

   98, 183, 37, 122, 14, 124, 65, 67 

   given that the disk has 202 cylinders (i.e. the largest cylinder number is 201, since the cylinder number starts from 0) in total and it is currently serving on cylinder 55, 
   1. (18%, each algorithm 3%) Case 1: the previous block served is on cylinder 4. 
   2. (18%, each algorithm 3%) Case 2: If the previous block served is on cylinder 60, redo the problem.



## References

* _Windows
	* [Local File Systems](https://docs.microsoft.com/en-us/windows/win32/fileio/file-management)
* _Linux_
	* [The Linux man-pages project](https://www.kernel.org/doc/man-pages/)
	* [Linux Programmer's Manual: open](http://man7.org/linux/man-pages/man2/open.2.html)
	* [Linux Filesystems API](https://www.kernel.org/doc/html/v4.14/filesystems/index.html)
* _C#_
	* [File and Stream I/O](https://docs.microsoft.com/en-us/dotnet/standard/io/)
* _Java_
	* [Basic IO](https://docs.oracle.com/javase/tutorial/essential/io/)
	* [Java File](http://www.java2s.com/Tutorials/Java/Java\_io/index.htm)




**Where are the codes and tools?**
* [Windows Sysinternals](https://docs.microsoft.com/en-us/sysinternals/)
* [BCC - Tools for BPF-based Linux IO analysis, networking, monitoring, and more](https://github.com/iovisor/bcc)
* [OSC10e](https://github.com/greggagne/osc10e)






