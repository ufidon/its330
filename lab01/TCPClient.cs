/*
* https://docs.microsoft.com/en-us/dotnet/api/system.net.sockets.tcpclient?view=netframework-4.7.2
*/

using System;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Text;

class MyTcpClient
{
	static void Connect(String server, String message) 
	{
	  try 
	  {
		// Create a TcpClient.
		// Note, for this client to work you need to have a TcpServer 
		// connected to the same address as specified by the server, port
		// combination.
		Int32 port = 13000;
		TcpClient client = new TcpClient(server, port);
		
		// Translate the passed message into ASCII and store it as a Byte array.
		Byte[] data = System.Text.Encoding.ASCII.GetBytes(message);         

		// Get a client stream for reading and writing.
	   //  Stream stream = client.GetStream();
		
		NetworkStream stream = client.GetStream();

		// Send the message to the connected TcpServer. 
		stream.Write(data, 0, data.Length);

		Console.WriteLine("Sent: {0}", message);         

		// Receive the TcpServer.response.
		
		// Buffer to store the response bytes.
		data = new Byte[256];

		// String to store the response ASCII representation.
		String responseData = String.Empty;

		// Read the first batch of the TcpServer response bytes.
		Int32 bytes = stream.Read(data, 0, data.Length);
		responseData = System.Text.Encoding.ASCII.GetString(data, 0, bytes);
		Console.WriteLine("Received: {0}", responseData);         

		// Close everything.
		stream.Close();         
		client.Close();         
	  } 
	  catch (ArgumentNullException e) 
	  {
		Console.WriteLine("ArgumentNullException: {0}", e);
	  } 
	  catch (SocketException e) 
	  {
		Console.WriteLine("SocketException: {0}", e);
	  }
		
	  Console.WriteLine("\n Press Enter to continue...");
	  Console.Read();
	}
  public static void Main()
  { 

    try
    {
      // Set the TcpListener on port 13000.
      //Int32 port = 13000;
      //IPAddress localAddr = IPAddress.Parse("127.0.0.1");
      
	  Connect("127.0.0.1", "Hello from client!");

      
    }
    catch(SocketException e)
    {
      Console.WriteLine("SocketException: {0}", e);
    }


      
    Console.WriteLine("\nHit enter to continue...");
    Console.Read();
  }   
}