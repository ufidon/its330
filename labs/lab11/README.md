# its330
Course materials and demos for labs

## Lab11: Network and I/O programming

### 1. Description

In this lab,  practice basic socket-programming in Windows API and C#.

### 2. Tasks (40%)

1. (20%) Practice basic socket-programming in Windows API with template [client.c](./code/win/client.c) and [server.c](./code/win/server.c)
2. (20%) Practice basic socket-programming in C# with template [csClient.cs](./code/cs/csClient.cs) and [csServer.cs](./code/cs/csServer.cs)


### 3. Review questions (60%)
1. (20%) Read articles [Asynchronous I/O](https://en.wikipedia.org/wiki/Asynchronous_I/O) and [Interrupt](https://en.wikipedia.org/wiki/Interrupt), write a summary about polling(synchronous) I/O vs. interrupt(asynchronous) I/O. You may refer to [OSC9e: Chapter 13](https://www.os-book.com/OS9/slide-dir/index.html), or [OSC10e: Chapter 12](https://www.os-book.com/OS10/slide-dir/index.html) for additional information.
2. (20%) Read article [Direct memory access (DMA)](https://en.wikipedia.org/wiki/Direct_memory_access), write a summary on the steps in a DMA transfer. You may refer to [OSC9e: Chapter 13](https://www.os-book.com/OS9/slide-dir/index.html), or [OSC10e: Chapter 12](https://www.os-book.com/OS10/slide-dir/index.html) for additional information.
3. (20%) Describe the life cycle of an I/O request based on the article [Example I/O Request - An Overview](https://docs.microsoft.com/en-us/windows-hardware/drivers/kernel/example-i-o-request---an-overview). You may refer to [OSC9e: Chapter 13](https://www.os-book.com/OS9/slide-dir/index.html), or [OSC10e: Chapter 12](https://www.os-book.com/OS10/slide-dir/index.html) for additional information.

**Demo video**

* [Lab11 Network programming](https://youtu.be/icQjUYDCefw)


## References

* _Windows_
  * [Getting Started with Winsock](https://docs.microsoft.com/en-us/windows/win32/winsock/getting-started-with-winsock)
  * [Complete Winsock Client Code](https://docs.microsoft.com/en-us/windows/win32/winsock/complete-client-code)
  * [Complete Winsock Server Code](https://docs.microsoft.com/en-us/windows/win32/winsock/complete-server-code)
  * [Running the Winsock Client and Server Code Sample](https://docs.microsoft.com/en-us/windows/win32/winsock/finished-server-and-client-code)
* _Linux_
  * [Socket Programming in C](https://www.geeksforgeeks.org/socket-programming-cc/)
* _C#_
  * [Network Programming in the .NET Framework](https://docs.microsoft.com/en-us/dotnet/framework/network-programming/)
  * [Socket Programming in C#](https://www.geeksforgeeks.org/socket-programming-in-c-sharp/)
  * [How to C# Socket programming](http://csharp.net-informations.com/communications/csharp-socket-programming.htm)
  * [Socket Programming In C#](https://www.c-sharpcorner.com/article/socket-programming-in-C-Sharp/)
* _Java_
  * [Socket Programming in Java](https://www.geeksforgeeks.org/socket-programming-in-java/)

**Where are the codes and tools?**
* [Windows Sysinternals](https://docs.microsoft.com/en-us/sysinternals/)
* [BCC - Tools for BPF-based Linux IO analysis, networking, monitoring, and more](https://github.com/iovisor/bcc)
* [OSC10e](https://github.com/greggagne/osc10e)





