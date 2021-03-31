/** client.c
 * Ref: Read ref 3. for writing your report
 * 1. https://docs.microsoft.com/en-us/windows/win32/winsock/complete-server-code
 * 2. https://docs.microsoft.com/en-us/windows/win32/winsock/getting-started-with-winsock
 * 3. https://docs.microsoft.com/en-us/windows/win32/winsock/finished-server-and-client-code
 * How to compile and run?
 * Compile: cl server.c
 * Run: 
 * 1. Open two Developer Command Prompt for VS2019 terminal windows, 
 * or use ConEmu and open two command tabs of 'Developer Command Prompt for VS2019'
 * 2. run server first in one command window: .\server.exe
 * 3. then run client in the other terminal windows: .\client.exe localhost
*/

#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

int __cdecl main(void) 
{
    WSADATA wsaData;
    int iResult;

    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;

    struct addrinfo *result = NULL;
    struct addrinfo hints;

    int iSendResult;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;

    const char *serverMsg = "Hello, my client.";
    
    // Initialize Winsock
    printf("server 01: Initialize Winsock\n");
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        printf("server 01: WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if ( iResult != 0 ) {
        printf("server 02: getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Create a SOCKET for connecting to server
    printf("server 03: Create a SOCKET for listening clients.\n");
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        printf("server 03: socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    // Setup the TCP listening socket
    printf("server 04: Bind the listening SOCKET.\n");
    iResult = bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("server 04: bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(result);

    printf("server 05: listening clients.\n");
    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        printf("server 05: listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    // Accept a client socket
    printf("server 06: accepting clients.\n");
    ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
        printf("server 06: accept failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    // No longer need server socket
    closesocket(ListenSocket);

    // Receive until the peer shuts down the connection
    do {

        iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
        if (iResult > 0) {
            printf("server 07: Bytes received: %d from the client.\n", iResult);
            printf("Server 07: The client said '%s' to me.\n", recvbuf);
            

        // Say hello  to the sender
            printf("server 09: I said '%s' to the client.\n", serverMsg);
            iSendResult = send( ClientSocket, serverMsg, strlen(serverMsg), 0 );
            if (iSendResult == SOCKET_ERROR) {
                printf("server 09: send failed with error: %d\n", WSAGetLastError());
                closesocket(ClientSocket);
                WSACleanup();
                return 1;
            }
            printf("server 09: Bytes sent: %d\n", iSendResult);
        }
        else if (iResult == 0)
            printf("server 10: Connection closing...\n");
        else  {
            printf("server 10: recv failed with error: %d\n", WSAGetLastError());
            closesocket(ClientSocket);
            WSACleanup();
            return 1;
        }

    } while (iResult > 0);

    // shutdown the connection since we're done
    printf("server 11: Disconnect from the client.\n");
    iResult = shutdown(ClientSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("server 11: shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ClientSocket);
        WSACleanup();
        return 1;
    }

    // cleanup
    closesocket(ClientSocket);
    WSACleanup();

    return 0;
}