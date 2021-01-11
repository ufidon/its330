# its330
Course materials and demos for labs


## Lab01: Setup lab environment
**1.Description**

Setup environment for developing C/C++, C#, Python and Java(Optional) programs.

If your host PC is NOT Windows, you may setup one virtual machine for Windows 10/Windows server and put it in a NAT network of VMWare Workstation Player/VirtualBox. It is optional to create another VM for Ubuntu LTS, both use the latest stable versions.

If your host is Windows 10, you may use it in this course instead of guest Windows in virtual machine.

**2.Steps**

1. (40%) Create VMs, NAT network, download and install ISOs and software
   1. Setup Windows server, then install chrome browser, visual studio, windows SDK, Anaconda, git, Zulu OpenJDK(Optional), and Eclipse(Optional)
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
   1. (each file 10%) On the Windows server VM or Windows host, compile and run the following: win32-pipe-child.c, all C# files and DateClient.java(Optional)
   2. (Optional) On the Ubuntu Linux VM, compile and run the following: shm-posix-consumer.c, DateClient.java and all C# files


## References
**Where are the OSes and tools?** 
  * [VMware Workstation Player](https://www.vmware.com/products/workstation-player.html)
  * [VirtualBox 6](https://www.virtualbox.org/)
  * [Ubuntu mate LTS](https://ubuntu-mate.org/)
  * [Windows server](https://www.microsoft.com/en-us/cloud-platform/windows-server)
  * [Windows 10 SDK](https://developer.microsoft.com/en-us/windows/downloads/windows-10-sdk)
  * [Visual Studio](https://visualstudio.microsoft.com/vs/)
  * [Visual Studio code](https://code.visualstudio.com/)
  * [dotnet](https://dotnet.microsoft.com)

**Youtube Videos** 
  * [Create empty virtual machines for Ubuntu & Windows Server 2019 in VirtualBox 6](https://youtu.be/3PbnBVNWXpk)
  * [Install Ubuntu 18.04LTS in VirtualBox 6](https://youtu.be/3BHsizTRUg0)
  * [Install Windows Server 2019 in VirtualBox 6](https://youtu.be/fQZFoSTSuPM)
  * [Create SEED Ubuntu 16.04 virtual machines and NAT network](https://youtu.be/pwSlVJSCpu0)
  * [How to run VirtualBox virtual machines on other computers with VirtualBox?](https://youtu.be/Ps30RJ1MzgQ)
  * [Compile C/C# code on Windows Server 2019 and Ubuntu 18.04LTS](https://youtu.be/ajTLkAqamKs)

* [Zulu OpenJDK](https://www.azul.com/downloads/zulu-community)
* [Setup JAVA_HOME,JDK_HOME, and JRE_HOME](https://confluence.atlassian.com/doc/setting-the-java_home-variable-in-windows-8895.html)



