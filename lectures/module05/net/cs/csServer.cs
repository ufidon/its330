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

class tcpserver
{
  public static void Main(string[] args)
  {
      if (args.Length == 1)
      {
        TcpListener server=null;   
        try
            {
            // Set the TcpListener on port args[0].
            Int32 port = Int32.Parse(args[0]);
            //IPAddress localAddr = IPAddress.Parse("127.0.0.1");
            IPAddress localAddr = IPAddress.Parse("0.0.0.0");
            
            // TcpListener server = new TcpListener(port);
            Console.Write("Server: Create TcpListener...\n");
            server = new TcpListener(localAddr, port);
            //server = new TcpListener(IPAddress.Any, port);

            // Start listening for client requests.
            Console.Write("Server: Start listening for client requests... \n");
            server.Start();
                
            // Buffer for reading data
            Byte[] bytes = new Byte[1024];
            String data = null;

            // Enter the listening loop.
            while(true) 
            {
                Console.Write("Server: Waiting for a connection from clients or press ctrl+c to exit...\n");
                
                // Perform a blocking call to accept requests.
                // You could also user server.AcceptSocket() here.
                
                TcpClient client = server.AcceptTcpClient();
                IPEndPoint remoteIpEndPoint = client.Client.RemoteEndPoint as IPEndPoint;
                IPEndPoint localIpEndPoint = client.Client.LocalEndPoint as IPEndPoint;

                Console.Write("Server: accepted client from {0}. \n", remoteIpEndPoint.Address);        
                Console.WriteLine("Server: Connected to client {0}!", remoteIpEndPoint.Address);

                data = null;

                // Get a stream object for reading and writing
                NetworkStream stream = client.GetStream();

                int i;

                // Loop to receive all the data sent by the client.
                Console.Write("Server: keep reading data from client {0}. \n", remoteIpEndPoint.Address);
                while((i = stream.Read(bytes, 0, bytes.Length))!=0) 
                {   
                    // Translate data bytes to a ASCII string.
                    data = System.Text.Encoding.ASCII.GetString(bytes, 0, i);
                    Console.WriteLine("Server: Received message '{0}' from client {1} ", data, remoteIpEndPoint.Address);
                
                    // Process the data sent by the client.
                    data = data.ToUpper();
                    Console.WriteLine("Server: Convert client message to upcase");

                    byte[] msg = System.Text.Encoding.ASCII.GetBytes(data);

                    // Send back a response.
                    stream.Write(msg, 0, msg.Length);
                    Console.WriteLine("Server: Sent '{0}' back to client {1}", data, remoteIpEndPoint.Address);            
                }
                
                // Shutdown and end connection
                Console.WriteLine("Disconnect from client {0}", remoteIpEndPoint.Address);
                client.Close();
            }
        }
        catch(SocketException e)
        {
            Console.WriteLine("Server: SocketException: {0}", e);
        }
        finally
        {
            // Stop listening for new clients.
            server.Stop();
        }

        Console.WriteLine("\nServer: Hit enter to continue...");
        Console.Read(); 
      }
      else
      {
        Console.WriteLine("Usage: csServer <port number> \n");
      }     
  }   
}