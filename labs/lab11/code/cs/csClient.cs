/** TCP client
* Ref: 
* 1. https://docs.microsoft.com/en-us/dotnet/api/system.net.sockets.tcplistener?view=netframework-4.8
* 2. https://docs.microsoft.com/en-us/dotnet/api/system.net.sockets.tcpclient?view=netframework-4.8
* 3. https://docs.microsoft.com/en-us/dotnet/csharp/programming-guide/types/how-to-convert-a-string-to-a-number
* 4. https://docs.microsoft.com/en-us/dotnet/api/system.net.ipaddress.parse?view=netframework-4.8
* How to compile & run?
* Compile:
* On Windows: csc csServer.cs
* On Ubuntu: mcs csServer.cs
* Run:
* A. Run both csServer and csClient on Ubuntu:
*   1. Open two terminals, one for csServer and the other for csClient
*   2. First run csServer in one terminal: ./csServer.exe 12345
*   3. then run csClient in the other terminal: ./csClient 127.0.0.1 12345
* B. Run both csServer and csClient on Windows:
*   1. Open two Command Prompts or two tabs on ConEmu, one for csServer and the other for csClient
*   2. First run csServer in one command window: .\csServer.exe 12345
*   3. then run csClient in the other command window: .\csClient 127.0.0.1 12345
**
* C. Run csServer on Ubuntu while csClient on Windows
*   1. On Ubuntu, open a terminal window, run command 'ifconfig -a' 
*       to find the ip address of its network adapter. 
*   2. then run csServer: ./csServer.exe 54321
*   3. On Windows, open a command prompt or a tab in ConEmu, run csClient: .\csClient "ubuntu ip address found in step 1" 54321
* D. Run csServer on Windows while csClient on Ubuntu
*   1. On Windows, open a command prompt or a tab in ConEmu, run command 'ipconfig /all' 
*       to find the ip address of its network adapter. 
*   2. then run csServer: .\csServer.exe 54321
*   3. On Ubuntu, open a terminal window, run csClient: ./csClient "Windows ip address found in step 1" 54321
*/


using System;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Text;

class tcplcient
{
  public static void Main(string[] args)
  { 
      if (args.Length == 2)
      {
            try 
            {
                // Create a TcpClient.
                // Note, for this client to work you need to have a TcpServer 
                // connected to the same address as specified by the server, port
                // combination.

                string server = args[0];
                //IPAddress sipAddress = IPAddress.Parse(server);
                Int32 port = Int32.Parse(args[1]);
                //IPEndPoint ipremoteEndPoint = new IPEndPoint(sipAddress, port);
                                

                Console.WriteLine("Client 01: Create TcpClient and connect to server {0}", server);
                //TcpClient client = new TcpClient(ipremoteEndPoint);
                TcpClient client = new TcpClient(server, port);

                IPEndPoint remoteIpEndPoint = client.Client.RemoteEndPoint as IPEndPoint;
                IPEndPoint localIpEndPoint = client.Client.LocalEndPoint as IPEndPoint;
                
                // Translate the passed message into ASCII and store it as a Byte array.
                string message = "Hello, my server.";
                Byte[] data = System.Text.Encoding.ASCII.GetBytes(message);         

                // Get a client stream for reading and writing.
                //  Stream stream = client.GetStream();
                
                NetworkStream stream = client.GetStream();

                // Send the message to the connected TcpServer. 
                stream.Write(data, 0, data.Length);
                Console.WriteLine("Client 02: I said '{0}' to the server {1}.", message, remoteIpEndPoint.Address);         

                // Receive the TcpServer.response.
                
                // Buffer to store the response bytes.
                data = new Byte[256];

                // String to store the response ASCII representation.
                String responseData = String.Empty;

                // Read the first batch of the TcpServer response bytes.
                Int32 bytes = stream.Read(data, 0, data.Length);

                responseData = System.Text.Encoding.ASCII.GetString(data, 0, bytes);

                Console.WriteLine("Client 03: Server {0} replied '{1}' to me", remoteIpEndPoint.Address, responseData);         

                // Close everything.
                stream.Close();         
                client.Close(); 
                Console.WriteLine("Client 04: I disconnected from Server {0}", remoteIpEndPoint.Address);        
            } 
            catch (ArgumentNullException e) 
            {
                Console.WriteLine("Client 01: ArgumentNullException: {0}", e);
            } 
            catch (SocketException e) 
            {
                Console.WriteLine("Client 02: SocketException: {0}", e);
            }
                
            Console.WriteLine("\n Client 05: Press Enter to continue...");
            Console.Read();
        }
      else
      {
          Console.WriteLine("\nUsage: csClient <server ip> <port number>");
      }
  }   
}