/**
 * This program creates two separate processes using the CreateProcess() system call.
 * ref: https://docs.microsoft.com/en-us/windows/win32/procthread/creating-processes
 */
 
#include <windows.h>
#include <stdio.h>
#include <tchar.h>

void _tmain( int argc, TCHAR *argv[] )
{
    STARTUPINFO si, si1;
    PROCESS_INFORMATION pi, pi1;

    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );

    ZeroMemory( &si1, sizeof(si1) );
    si.cb = sizeof(si1);
    ZeroMemory( &pi1, sizeof(pi1) );


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
        printf( TEXT("CreateProcess for mspaint failed (%d).\n"), GetLastError() );
        return;
    }

    // Start the child process for notepad.
    printf(TEXT("I am going to create a process for notepad.\n"));

    if( !CreateProcess( TEXT("C:\\WINDOWS\\system32\\notepad.exe"), // Application name
        NULL,        // command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        0,              // No creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory 
        &si1,            // Pointer to STARTUPINFO structure
        &pi1 )           // Pointer to PROCESS_INFORMATION structure
    ) 
    {
        printf( TEXT("CreateProcess for notepad failed (%d).\n"), GetLastError() );
        return;
    }    


#ifdef BADCODE   
    /* code block one, problematic  */
        // Wait until child process mspaint exits.
        WaitForSingleObject( pi.hProcess, INFINITE );
        printf(TEXT("child process mspaint terminated.\n"));

        // Wait until child process notepad exits.
        WaitForSingleObject( pi1.hProcess, INFINITE );
        printf(TEXT("child process notepad terminated.\n"));        
#else
    /* code block two, good  */
        const HANDLE hProcesses[2] = { pi.hProcess,  pi1.hProcess}; 
        WaitForMultipleObjects(2, hProcesses,TRUE, INFINITE);
#endif
    

    
    // Close process handles. 
    CloseHandle( pi.hProcess );
    CloseHandle( pi1.hThread );

    printf(TEXT("parent process create-2-child terminated.\n"));
}