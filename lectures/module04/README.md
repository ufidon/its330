# its330
Course materials and demos for lectures


## Module04: Persistent storage management
### Storage devices
* _Concepts_
 * [Computer data storage](https://en.wikipedia.org/wiki/Computer_data_storage)
   * [Hard disk drive](https://en.wikipedia.org/wiki/Hard_disk_drive)
     * [List of disk drive form factors](https://en.wikipedia.org/wiki/List_of_disk_drive_form_factors)
     * [Hard disk drive interface](https://en.wikipedia.org/wiki/Hard_disk_drive_interface)
     * [Hard disk drive performance characteristics](https://en.wikipedia.org/wiki/Hard_disk_drive_performance_characteristics)
     * [Cylinder-head-sector (CHS) addressing](https://en.wikipedia.org/wiki/Cylinder-head-sector)
     * [Logical block addressing (LBA) ](https://en.wikipedia.org/wiki/Logical_block_addressing)
   * [Solid-state drive](https://en.wikipedia.org/wiki/Solid-state_drive)
     * [Flash memory](https://en.wikipedia.org/wiki/Flash_memory)
   * [RAM drive](https://en.wikipedia.org/wiki/RAM_drive)
     * [Tmpfs](https://en.wikipedia.org/wiki/Tmpfs)
   * [Optical disc](https://en.wikipedia.org/wiki/Optical_disc)
   * [Magnetic tape](https://en.wikipedia.org/wiki/Magnetic_tape)
   * [RAID](https://en.wikipedia.org/wiki/RAID)
   * [Network-attached storage](https://en.wikipedia.org/wiki/Network-attached_storage)
     * [Storage area network](https://en.wikipedia.org/wiki/Storage_area_network)
     * [Network File System (NFS)](https://en.wikipedia.org/wiki/Network_File_System)
     * [Server Message Block](https://en.wikipedia.org/wiki/Server_Message_Block)
     * [WebDAV (Web Distributed Authoring and Versioning) ](https://en.wikipedia.org/wiki/WebDAV)
   * [Cloud storage](https://en.wikipedia.org/wiki/Cloud_storage)
 * [I/O scheduling](https://en.wikipedia.org/wiki/I/O_scheduling)
   * [Disk Scheduling Algorithms](https://www.geeksforgeeks.org/disk-scheduling-algorithms/)
   * [Noop scheduler](https://en.wikipedia.org/wiki/Noop_scheduler)
 * [Disk formatting](https://en.wikipedia.org/wiki/Disk_formatting)
 * [Disk partitioning](https://en.wikipedia.org/wiki/Disk_partitioning)
   * [Partition alignment](https://en.wikipedia.org/wiki/Partition_alignment)
   * [Advanced Format (AF)](https://en.wikipedia.org/wiki/Advanced_Format)
   * [Partition table](https://en.wikipedia.org/wiki/Partition_table)
     * [GUID Partition Table](https://en.wikipedia.org/wiki/GUID_Partition_Table)
     * [Master boot record](https://en.wikipedia.org/wiki/Master_boot_record)
       * [Extended boot record](https://en.wikipedia.org/wiki/Extended_boot_record)
   * [Partition type](https://en.wikipedia.org/wiki/Partition_type)
   * [Logical Volume Manager (LVM)](https://en.wikipedia.org/wiki/Logical_Volume_Manager_(Linux))
   * [List of disk partitioning software](https://en.wikipedia.org/wiki/List_of_disk_partitioning_software)
* _Youtube video_
  * [Mass storage systems](https://www.youtube.com/watch?v=KMETs6ONOoI)
    * [Explaining Solid State Disks](https://www.youtube.com/watch?v=viac3j6MeII)
    * [Mass storage structure](https://www.youtube.com/playlist?list=PLskQvPDUk0sIpg-7EGPiE_kPjpAakY_ey)
    * [Mass storage and disk scheduling](https://www.youtube.com/watch?v=Obv6wAg1f08)
  * [File system implementation](https://www.youtube.com/playlist?list=PLskQvPDUk0sKgGGReUz7nMwYkDTbevUC1)
    * [File system: Implementation](https://www.youtube.com/watch?v=G74QFfuOghE&list=PLacuG5pysFbDQU8kKxbUh4K5c1iL5_k7k&index=16)
### File system interface & implementation
* _Concepts_
  * [Computer file](https://en.wikipedia.org/wiki/Computer_file)
    * [Directory](https://en.wikipedia.org/wiki/Directory_(computing))
      * [Directory structure](https://en.wikipedia.org/wiki/Directory_structure)
        * [Structures of Directory in Operating System](https://www.geeksforgeeks.org/structures-of-directory-in-operating-system/)
        * [Tree structure](https://en.wikipedia.org/wiki/Tree_structure)
      * [Path](https://en.wikipedia.org/wiki/Path_(computing))
    * [File format](https://en.wikipedia.org/wiki/File_format)
      * [List of file formats](https://en.wikipedia.org/wiki/List_of_file_formats)
    * [Filename](https://en.wikipedia.org/wiki/Filename)
      * [Fully qualified name](https://en.wikipedia.org/wiki/Fully_qualified_name)
      * [Long filename](https://en.wikipedia.org/wiki/Long_filename)
    * [Data](https://en.wikipedia.org/wiki/Data_(computing))
    * [Device file](https://en.wikipedia.org/wiki/Device_file)
  * [File attribute](https://en.wikipedia.org/wiki/File_attribute)
    * [Extended file attributes](https://en.wikipedia.org/wiki/Extended_file_attributes)
    * [Hidden file and hidden directory](https://en.wikipedia.org/wiki/Hidden_file_and_hidden_directory)
  * [File-system permissions](https://en.wikipedia.org/wiki/File-system_permissions)
    * [access-control list (ACL)](https://en.wikipedia.org/wiki/Access-control_list)
  * [File manager](https://en.wikipedia.org/wiki/File_manager)
  * [File sharing](https://en.wikipedia.org/wiki/File_sharing)
  * [Mounting ](https://en.wikipedia.org/wiki/Mount_(computing))
  * [Windows File Protection](https://en.wikipedia.org/wiki/Windows_File_Protection)
    * [Windows Resource Protection](https://en.wikipedia.org/wiki/Windows_Resource_Protection)
    * [System File Checker](https://en.wikipedia.org/wiki/System_File_Checker)
  * [File system](https://en.wikipedia.org/wiki/File_system)
    * [Virtual file system](https://en.wikipedia.org/wiki/Virtual_file_system)
    * [Comparison of file systems](https://en.wikipedia.org/wiki/Comparison_of_file_systems)
    * [List of file systems](https://en.wikipedia.org/wiki/List_of_file_systems)
    * [Unix filesystem](https://en.wikipedia.org/wiki/Unix_filesystem)
      * [Filesystem Hierarchy Standard](https://en.wikipedia.org/wiki/Filesystem_Hierarchy_Standard)
    * [Inode](https://en.wikipedia.org/wiki/Inode)
      * [Bitmap](https://en.wikipedia.org/wiki/Bitmap)
      * [Bit array](https://en.wikipedia.org/wiki/Bit_array)
    * [Boot sector](https://en.wikipedia.org/wiki/Boot_sector)
  * [File system API](https://en.wikipedia.org/wiki/File_system_API)
    * [File Control Block](https://en.wikipedia.org/wiki/File_Control_Block)
      * [File descriptor](https://en.wikipedia.org/wiki/File_descriptor)
* _Popular filesystems_
  * [Linux: Extended file system](https://en.wikipedia.org/wiki/Extended_file_system)
    * [second extended file system](https://en.wikipedia.org/wiki/Ext2)
      * [third extended filesystem](https://en.wikipedia.org/wiki/Ext3)
      * [ext4 journaling file system](https://en.wikipedia.org/wiki/Ext4)
    * [ZFS Zettabyte file system](https://en.wikipedia.org/wiki/ZFS)
  * _Windows file systems_
    * [FAT: File Allocation Table](https://en.wikipedia.org/wiki/File_Allocation_Table)
      * [ExFAT: Extensible File Allocation Table](https://en.wikipedia.org/wiki/ExFAT)
    * [NTFS: New Technology File System](https://en.wikipedia.org/wiki/NTFS)
      * [NTFS-3G](https://en.wikipedia.org/wiki/NTFS-3G)
      * [Open Source: NTFS-3G](https://www.tuxera.com/community/open-source-ntfs-3g/)
* _Youtube video_
  * [File system interface](https://www.youtube.com/playlist?list=PLskQvPDUk0sLsU1Vv5jSr-P-1yTt0AqdJ)
    * [File system: Interface](https://www.youtube.com/watch?v=Y46WruvvIKc&list=PLacuG5pysFbDQU8kKxbUh4K5c1iL5_k7k&index=15)
  * [Explaining File Systems: NTFS, exFAT, FAT32, ext4 & More](https://youtu.be/_h30HBYxtws)
    * [Learning the Linux File System](https://youtu.be/HIXzJ3Rz9po)
    * [Windows File Systems](https://youtu.be/TLKZEU1DZ9c)
* _FS API_
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
    * [Java File](http://www.java2s.com/Tutorials/Java/Java_io/index.htm)
### Textbooks
* [Operating System Concepts (OSC) 10e](https://www.os-book.com/OS10/index.html)
* [Operating System Concepts (OSC) 9e](https://www.os-book.com/OS9/index.html)