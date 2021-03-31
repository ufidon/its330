/** client.c
 * Ref: Read ref 3. for writing your report
 * 1. https://docs.microsoft.com/en-us/windows/win32/winsock/getting-started-with-winsock
 * 2. https://docs.microsoft.com/en-us/windows/win32/winsock/complete-client-code
 * 3. https://docs.microsoft.com/en-us/windows/win32/winsock/finished-server-and-client-code 
 * How to compile and run?
 * Compile: cl client.c
 * Run: 
 * 1. Open two Developer Command Prompt for VS2019 terminal windows, 
 * or use ConEmu and open two command tabs of 'Developer Command Prompt for VS2019'
 * 2. run server first in one command window: .\server.exe
 * 3. then run client in the other terminal windows: .\client.exe localhost
*/

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>


// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

int __cdecl main(int argc, char **argv) 
{
    WSADATA wsaData;
    SOCKET ConnectSocket = INVALID_SOCKET;
    struct addrinfo *result = NULL,
                    *ptr = NULL,
                    hints;
    const char *clientMsg = "Hello, my server.";
    char recvbuf[DEFAULT_BUFLEN];
    int iResult;
    int recvbuflen = DEFAULT_BUFLEN;
    
    // Validate the parameters
    if (argc != 2) {
        printf("usage: %s server-name or IP address\n", argv[0]);
        return 1;
    }

    // Initialize Winsock
    printf("client 01: Initialize Winsock\n");
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        printf("client 01: WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory( &hints, sizeof(hints) );
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    printf("client 02: Resolve the server address and port\n");
    iResult = getaddrinfo(argv[1], DEFAULT_PORT, &hints, &result);
    if ( iResult != 0 ) {
        printf("client 02: getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Attempt to connect to an address until one succeeds
    printf("client 03: Attempt to connect to the server.\n");
    for(ptr=result; ptr != NULL ;ptr=ptr->ai_next) {

        // Create a SOCKET for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, 
            ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            printf("client 03: socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            return 1;
        }

        // Connect to server.
        printf("client 04: Connect to the server.\n");
        iResult = connect( ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET) {
        printf("client 04: Unable to connect to server!\n");
        WSACleanup();
        return 1;
    }

    // Send an initial buffer
    printf("client 05: I said '%s' to the server.\n", clientMsg);
    iResult = send( ConnectSocket, clientMsg, (int)strlen(clientMsg), 0 );
    if (iResult == SOCKET_ERROR) {
        printf("client 05: send failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    printf("client 05: Bytes Sent: %ld\n", iResult);

    // shutdown the connection since no more data will be sent
    iResult = shutdown(ConnectSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("client 06: shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    // Receive until the peer closes the connection
    do {

        iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
        if ( iResult > 0 ){
            printf("client 07: The server replied '%s' to me.\n", recvbuf);
            printf("client 07: Bytes received: %d\n", iResult);
        }
        else if ( iResult == 0 )
            printf("client 07: Connection closed\n");
        else
            printf("client 07: recv failed with error: %d\n", WSAGetLastError());

    } while( iResult > 0 );

    // cleanup
    printf("client 08: Disconnect from the server.\n");
    closesocket(ConnectSocket);
    WSACleanup();

    return 0;
}