# its330
Course materials and demos for labs


## Lab01: Setup lab environment
**1.Description**

Setup environment for developing C/C++, C#, Python and Java(Optional) programs.

If your host PC is NOT Windows, you may setup one virtual machine for Windows 10/Windows server and put it in a NAT network of VMWare Workstation Player/VirtualBox. It is optional to create another VM for Ubuntu LTS, both use the latest stable versions.

If your host is Windows 10, you may use it in this course instead of guest Windows in virtual machine.

**2.Steps**

1. (20%) Create VMs, NAT network, download and install ISOs and software
   1. Setup Windows server, then install chrome browser, visual studio(5%), windows SDK(5%), Python3(5%), git(5%), Zulu OpenJDK(Optional), and Eclipse(Optional)
   2. (Optional) Setup Ubuntu, open a terminal run the following commands then install visual studio code

```bash
# Inside Ubuntu, open a terminal, run the following commands
sudo apt update
sudo apt upgrade
sudo apt install terminator build-essential git cmake vim
sudo apt install apt-transport-https dirmngr
sudo apt-get install openjdk-11-jdk mono-mcs
```
2. (60%) Download and compile the source code files in c and c# programs, fix the compilation errors and run them to get the results
   1. (each file 12%) On the Windows server VM or Windows host, compile and run the following: win32-pipe-child.c, all four C# files and DateClient.java(Optional)
   2. (Optional) On the Ubuntu Linux VM, compile and run the following: shm-posix-consumer.c, DateClient.java and all C# files

3. (20%) Review questions
   1. (10%) A [binary prefix](https://en.wikipedia.org/wiki/Binary_prefix) is a unit prefix for multiples of units in data processing, data transmission, and digital information, notably the bit and the byte, to indicate multiplication by a power of 2. *Fill in the following blanks and show your calculation.*
      1. (5%, %1 for each) A ISO file of size 4.253GB = ?MB = ?KB = ?Gb = ?TB = ?B
      2. (5%, %1 for each) In the specification of [USB 3.1](https://en.wikipedia.org/wiki/USB_3.0), USB 3.1 Gen 2 – SuperSpeed+, new 10 Gbit/s data rate over 1 lane using 128b/132b encoding. Its effective data rate can be up to 1212 MB/s = ?GB/s= ?GB/min= ?KB/s= ?Mb/min= ?bps
   2. (10%) Rank the following storage systems from slowest to fastest, show your references: a. Hard-disk drives b. Registers c. Optical disk d. Main memory e. Nonvolatile memory f. Magnetic tapes g. Cache

**Demo video**
* [Lab01: Setup lab environment](https://youtu.be/vtiv_vyaKk0)

## References
**Where are the OSes and tools?** 

* [VMware Workstation Player](https://www.vmware.com/products/workstation-player.html)
* [VirtualBox 6](https://www.virtualbox.org/)
* [Ubuntu mate LTS](https://ubuntu-mate.org/)
* [Windows server](https://www.microsoft.com/en-us/cloud-platform/windows-server)
* [Windows 10 SDK](https://developer.microsoft.com/en-us/windows/downloads/windows-10-sdk)
* [Visual Studio](https://visualstudio.microsoft.com/vs/)
* [Visual Studio code](https://code.visualstudio.com/)
* [Python3](https://www.python.org/)
 * [CMD opens window store when I type python](https://stackoverflow.com/questions/58754860/cmd-opens-window-store-when-i-type-python)
* [git](https://git-scm.com/)
* [dotnet](https://dotnet.microsoft.com)
* [Computer Storage Units Conversion Calculator](https://www.calculatorsoup.com/calculators/conversions/computerstorage.php)
* [Data Transfer Rate Converter](https://www.thecalculatorsite.com/conversions/datarate.php)

**Youtube Videos** 

* [Create empty virtual machines for Ubuntu & Windows Server 2019 in VirtualBox 6](https://youtu.be/3PbnBVNWXpk)
* [Install Ubuntu 18.04LTS in VirtualBox 6](https://youtu.be/3BHsizTRUg0)
* [Install Windows Server 2019 in VirtualBox 6](https://youtu.be/fQZFoSTSuPM)
* [Create SEED Ubuntu 16.04 virtual machines and NAT network](https://youtu.be/pwSlVJSCpu0)
* [How to run VirtualBox virtual machines on other computers with VirtualBox?](https://youtu.be/Ps30RJ1MzgQ)
* [Compile C/C# code on Windows Server 2019 and Ubuntu 18.04LTS](https://youtu.be/ajTLkAqamKs)
* [Zulu OpenJDK](https://www.azul.com/downloads/zulu-community)
* [Setup JAVA_HOME,JDK_HOME, and JRE_HOME](https://confluence.atlassian.com/doc/setting-the-java_home-variable-in-windows-8895.html)



