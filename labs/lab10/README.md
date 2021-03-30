# its330
Course materials and demos for labs

## Lab10: file system investigation

### 1. Description

In this lab,  investigate popular file system FAT/FAT32/NTFS/ext4/minix on Windows using [sleuthkit](https://www.sleuthkit.org/sleuthkit/).

### 2. Tasks (60%)

1. (3%) Download and unarchive [sleuthkit](https://www.sleuthkit.org/sleuthkit/)
2. (4%) Add the bin folder of sleuthkit to the system environmental variable PATH, verify sleuthkit commands can be executed anywhere from a Command prompt or Powershell
3. (3%) Download the archive file [hd.7z](./code/hd.7z), unzip it to get example image file hd.img
4. (50%, 5% for each command) Use the following [sleuthkit commands](http://wiki.sleuthkit.org/index.php?title=TSK_Tool_Overview) to investigate the file systems on hd.img
   
   | command | purpose |
   | ------- | ------- |
   | mmls | Display the partition layout of a volume system (partition tables). |
   | mmstat | Display details about the volume system (partition tables). |
   | mmcat | Output the contents of a partition to stdout. |
   | fsstat | Display general details of a file system. |
   | fls | List file and directory names in a disk image. |
   | ils | List inode information. |
   | icat | Output the contents of a file based on its inode number. |
   | blkls | List or output file system data units. |
   | blkstat | Display details of a file system data unit (i.e. block or sector). |
   | blkcat | Display the contents of file system data unit in a disk image. |


### 3. Review questions (40%)
1. (10%) Describe indexed allocation of disk space. Refer to [Allocation](https://en.wikibooks.org/wiki/Operating_System_Design/File_Systems/Allocation), or [OSC9e: Chapter 12](https://www.os-book.com/OS9/slide-dir/index.html), or [OSC10e: Chapter 14](https://www.os-book.com/OS10/slide-dir/index.html).
2. (20%) Consider a file system that uses inodes to represent files. Disk blocks are 8 KB in size, and a pointer to a disk block requires 4 bytes.  This file system has 12 direct disk blocks, as well as single, double, and triple indirect disk blocks. What is the maximum size of a file that can be stored in this file system? Refer to [OSC9e: Chapter 12](https://www.os-book.com/OS9/slide-dir/index.html), or [OSC10e: Chapter 14](https://www.os-book.com/OS10/slide-dir/index.html). 
3. (10%) How many MB does a 1-TB disk with 4-KB blocks require to store its bit map? Refer to [OSC10e: Chapter 14](https://www.os-book.com/OS10/slide-dir/index.html)

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




