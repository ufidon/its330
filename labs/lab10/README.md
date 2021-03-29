# its330
Course materials and demos for labs

## Lab10: file system investigation

### 1. Description

In this lab,  investigate popular file system FAT/FAT32/NTFS on Windows using [sleuthkit](https://www.sleuthkit.org/sleuthkit/).

### 2. Tasks

1. Download and unarchive [sleuthkit](https://www.sleuthkit.org/sleuthkit/)
2. Add the bin folder of sleuthkit to the system environmental variable PATH, verify sleuthkit commands can be executed anywhere from a Command prompt or Powershell
3. Using Windows disk manager, create a 500MB virtual disk with GPT table, partition it into two equal partitions, one formatted as  


### 3. Review questions
1. Read articles [File attribute](https://en.wikipedia.org/wiki/File_attribute) and [Computer file](https://en.wikipedia.org/wiki/Computer_file), write a summary about file attributes and file operations.
2. Read article [File Access Methods in Operating System](https://www.geeksforgeeks.org/file-access-methods-in-operating-system/), write a summary about the difference between the two file accesses: sequential access vs direct access ( or relative access).
3. List out five file system operations that are to be executed on a directory. Refer to [OSC9e: Chapter 11](https://www.os-book.com/OS9/slide-dir/index.html) or [OSC10e: Chapter 13](https://www.os-book.com/OS10/slide-dir/index.html).
4. Explain the access rights of the following users on the file ‘key.md5’ base on the output of command ‘ls -l key.md5’: 

   -rw-rw-rw- 1 trump whitehouse 38 Oct 15 2018 key.md5

   It is know that the group ‘whitehouse={Trump, Mick, Kellyanne, Johnny, Jared}’. Can Pense access key.md5?

   Refer to: [File Permissions](https://help.ubuntu.com/community/FilePermissions), or [OSC9e: Chapter 11](https://www.os-book.com/OS9/slide-dir/index.html), or [OSC10e: Chapter 13](https://www.os-book.com/OS10/slide-dir/index.html).
5. Describe indexed allocation of disk space. Refer to [Allocation](https://en.wikibooks.org/wiki/Operating_System_Design/File_Systems/Allocation), or [OSC9e: Chapter 12](https://www.os-book.com/OS9/slide-dir/index.html), or [OSC10e: Chapter 14](https://www.os-book.com/OS10/slide-dir/index.html).
6. Consider a file system that uses inodes to represent files. Disk blocks are 8 KB in size, and a pointer to a disk block requires 4 bytes.  This file system has 12 direct disk blocks, as well as single, double, and triple indirect disk blocks. What is the maximum size of a file that can be stored in this file system? Refer to [OSC9e: Chapter 12](https://www.os-book.com/OS9/slide-dir/index.html), or [OSC10e: Chapter 14](https://www.os-book.com/OS10/slide-dir/index.html). 
7. A 1-TB disk with 4-KB blocks requires how many MB to store its bit map. 

## References
* _Windows
	* [TSK Tool Overview](https://wiki.sleuthkit.org/index.php?title=TSK\_Tool\_Overview)
  	* [sleuthkit](https://www.sleuthkit.org/sleuthkit/)
	* [FAT](https://wiki.osdev.org/FAT)
	* [exFAT file system specification](https://docs.microsoft.com/en-us/windows/win32/fileio/exfat-specification)
	* [Description of the FAT32 File System](https://support.microsoft.com/en-us/help/154997/description-of-the-fat32-file-system)
	* [Microsoft Extensible Firmware Initiative FAT32 File System Specification](http://www.cs.fsu.edu/~cop4610t/assignments/project3/spec/fatspec.pdf)
	* [NTFS overview](https://docs.microsoft.com/en-us/windows-server/storage/file-server/ntfs-overview)
	* [Security auditing](https://docs.microsoft.com/en-us/windows/security/threat-protection/auditing/security-auditing-overview)
* _Linux_
  * [Create blank disk image for file storage](https://askubuntu.com/questions/667291/create-blank-disk-image-for-file-storage)
  * [Open Source: NTFS-3G](https://www.tuxera.com/community/open-source-ntfs-3g/)
  * [ntfs-3g – Third Generation Read/Write NTFS Driver](https://www.tuxera.com/community/ntfs-3g-manual/)
  * [The Linux NTFS filesystem driver](https://www.kernel.org/doc/Documentation/filesystems/ntfs.txt)
  * [ntfs-3g - Third Generation Read/Write NTFS Driver](http://manpages.ubuntu.com/manpages/trusty/man8/ntfs-3g\.8\.html)





**Where are the codes and tools?**
* [Windows Sysinternals](https://docs.microsoft.com/en-us/sysinternals/)
* [BCC - Tools for BPF-based Linux IO analysis, networking, monitoring, and more](https://github.com/iovisor/bcc)
* [OSC10e](https://github.com/greggagne/osc10e)


**Youtube Videos**
* [Investigate file systems with sleuthkit on Windows server 2019](https://youtu.be/UkKIbABIeys)
* [Investigate file systems with sleuthkit on Ubuntu](https://youtu.be/wfxPla41WMw)




