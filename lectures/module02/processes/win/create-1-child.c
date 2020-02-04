/**
 * This program creates a separate process using the CreateProcess() system call.
 * ref: https://docs.microsoft.com/en-us/windows/win32/procthread/creating-processes
 */
 
#include <windows.h>
#include <stdio.h>
#include <tchar.h>

void _tmain( int argc, TCHAR *argv[] )
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );


    // Start the child process for mspaint.
    printf(TEXT("I am going to create a process for mspaint.\n"));

    if( !CreateProcess( TEXT("C:\\WINDOWS\\system32\\mspaint.exe"), // Application name
        NULL,        // command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        0,              // No creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory 
        &si,            // Pointer to STARTUPINFO structure
        &pi )           // Pointer to PROCESS_INFORMATION structure
    ) 
    {
        printf( TEXT("CreateProcess failed (%d).\n"), GetLastError() );
        return;
    }

    // Wait until child process exits.
    WaitForSingleObject( pi.hProcess, INFINITE );

     printf(TEXT("child process mspaint terminated.\n"));
    // Close process and thread handles. 
    CloseHandle( pi.hProcess );
    CloseHandle( pi.hThread );

    printf(TEXT("parent process create-one-child terminated.\n"));
}