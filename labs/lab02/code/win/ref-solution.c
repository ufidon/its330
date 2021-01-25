/**
 * This program creates n separate processes using the CreateProcess() system call.
 * ref: https://docs.microsoft.com/en-us/windows/win32/procthread/creating-processes
 */


#include <windows.h>
#include <stdio.h>


// number of processes
#define N  4


void main( int argc, char *argv[] )
{
    int i;
    STARTUPINFO si[N];
    PROCESS_INFORMATION pi[N];
    HANDLE hProcesses[N];

    // the programs to be loaded
    //  The four processes below must be: File explorer, MS paint, Snipping tool and Event viewer.
    char* PROCESSES[N]={
        "C:\\WINDOWS\\system32\\mspaint.exe", 
        //"C:\\WINDOWS\\system32\\SnippingTool.exe",
        "C:\\Windows\\system32\\charmap.exe",
        "C:\\Windows\\system32\\eventvwr.exe",
        "C:\\WINDOWS\\explorer.exe"};

    // initialize data structures
    ZeroMemory( si, sizeof(si) );
    for (i = 0; i < N; i++)
    {
        si[i].cb = sizeof(si[i]);
    } 
    
    ZeroMemory( pi, sizeof(pi) );       

    // create child processes.
    printf("I am going to create %d child processes.\n", N);

    for (i = 0; i < N; i++)
    {
        if( !CreateProcess( PROCESSES[i], // Application name
            NULL,        // command line
            NULL,           // Process handle not inheritable
            NULL,           // Thread handle not inheritable
            FALSE,          // Set handle inheritance to FALSE
            0,              // No creation flags
            NULL,           // Use parent's environment block
            NULL,           // Use parent's starting directory 
            &si[i],            // Pointer to STARTUPINFO structure
            &pi[i] )           // Pointer to PROCESS_INFORMATION structure
        ) 
        {
            printf( "CreateProcess for %s failed (%d).\n", PROCESSES[i], GetLastError() );
            return;
        }

        printf("Child process %s is created.\n", PROCESSES[i]);        
    }
    


    for (i = 0; i < N; i++)
    {
        hProcesses[i] = pi[i].hProcess;
    }
    
    WaitForMultipleObjects(N, hProcesses,TRUE, INFINITE);


    
    // Close process handles. 
    for (i = 0; i < N; i++)
    {
        CloseHandle( pi[i].hProcess );
        CloseHandle( pi[i].hThread);
    }

    printf("parent process create-n-child terminated.\n");
}