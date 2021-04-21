# its330
Course materials and demos for labs

## Lab12: protection & security

### 1. Description

In this lab,  practice protection & security programming in Windows API and C#.
1. Digital signature signing and verification
2. Cryptographical hash generation and verification
3. AES cipher encryption and decryption

### 2. Tasks (30%)

1. (10%) Practice digital signature signing and verification programming in Windows API with template [signverify.c](./code/win/signverify.c)
2. (10%) Practice AES cipher encryption and decryption programming in Windows API with template [aes.cpp](./code/win/aes.cpp)
3. (10%) Practice cryptographical hash generation and verification programming in C# with template [hmacsha256.cs](./code/cs/hmacsha256.cs)


### 3. Review questions (70%)

Write a concise summary for each of the following questions.

1. (8%) Describe the key, time-tested guiding principle for protection — OSC9e: Section 14.2 Principles of Protection. Page 626-627 or OSC10e: Section 17.2 Principles of Protection. Page 668-669.
2. (8%) Describe the three ways of implementing a domain. OSC9e: Section 14.3.1 Domain Structure. Page 629-632 or OSC10e: Section 17.4.1 Domain Structure. Page 673-674
3. (8%) In an access matrix, the copy and owner rights allow a process to change the entries in a column. A mechanism is also needed to change the entries in a row. The control right is applicable only to domain objects. OSC9e: Page 635 or OSC10e: Page 678
4. (8%) Describe and compare the four ways to implement access matrix. OSC9e: Section 14.5 Implementation of the Access Matrix. Page 636-639 or OSC10e: 17.6 Implementation of the Access Matrix. Page 679-682
5. (8%) Describe the schemes that implement revocation for capabilities. OSC9e: 14.7 Revocation of Access Rights Page 640-641 or OSC10e: Section 17.7 Revocation of Access Rights. Page 682-683
6. (8%) Describe several forms of accidental and malicious security violations. OSC9e: Section 15.1 The Security Problem. Page 658-661 or OSC10e: Section 16.1 The Security Problem. Page 621-625
7. (8%) Describe several forms(categories) of viruses. OSC9e: Section 15.2.5 Viruses Page 666-669 or OSC10e: Section 16.2.3 Viruses and Worms. Page 631-634
8. (6%) Describe the three things user authentication is based on:  OSC9e: Section 15.5 User Authentication. Page 685-689 or OSC10e: Section 16.5 User Authentication. Page 648-653
9. (8%) Describe the major methods, tools, and techniques that can be used to improve resistance to threats. OSC9e: Section 15.6 Implementing Security Defenses Page 689-696 or OSC10e: Section 16.6 Implementing Security Defenses Page 653-661


**Demo video**

* [Lab12 Security and Protection](https://youtu.be/SqA8OXUF8NI)


## References

* _Windows
  * [Cryptography](https://docs.microsoft.com/en-us/windows/win32/seccrypto/cryptography-portal)
  * [Cryptography API: Next Generation](https://docs.microsoft.com/en-us/windows/win32/seccng/about-cng)
* _Linux_
  * [EVP Symmetric Encryption and Decryption](https://wiki.openssl.org/index.php/EVP_Symmetric_Encryption_and_Decryption)
  * [Advanced Encryption Standard (AES)](https://en.wikipedia.org/wiki/Advanced\_Encryption\_Standard)
  * [Block cipher mode of operation](https://en.wikipedia.org/wiki/Block\_cipher\_mode\_of\_operation)
  * [OpenSSL](https://www.openssl.org/)
  * [OpenSSL Wiki](https://wiki.openssl.org/index.php/Main_Page)
* _C#_
  * [HMACSHA256 Class](https://docs.microsoft.com/en-us/dotnet/api/system.security.cryptography.hmacsha256?view=netframework-4.8)
  * [Cryptography in Microsoft.NET Part I: Encryption](https://www.c-sharpcorner.com/article/cryptography-in-microsoft-net-part-i-encryption/)
  * [Cryptography in Microsoft.NET Part II: Digital Envelop and Digital Signatures](https://www.c-sharpcorner.com/article/cryptography-in-microsoft-net-part-ii-digital-envelop-and-d/)
  * [Security in .NET](https://docs.microsoft.com/en-us/dotnet/standard/security/)

**Where are the codes and tools?**
* [Windows Sysinternals](https://docs.microsoft.com/en-us/sysinternals/)
* [BCC - Tools for BPF-based Linux IO analysis, networking, monitoring, and more](https://github.com/iovisor/bcc)
* [OSC10e](https://github.com/greggagne/osc10e)






