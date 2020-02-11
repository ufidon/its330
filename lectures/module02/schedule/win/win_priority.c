// ref: https://docs.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-setthreadpriority?redirectedfrom=MSDN
// ref: https://social.msdn.microsoft.com/Forums/Windows/en-US/df40db25-1635-4ea9-a077-0fe71c4d1ae2/moving-project-to-vs2015-solving-linker-errors?forum=vcgeneral
#include <windows.h>
#include <tchar.h>
#include <stdio.h>

int main( void )
{
   DWORD dwError, dwThreadPri;

	// Get and print the default priority
	// TODO: get and print out the default priority
	// 
	

   if(!SetThreadPriority(GetCurrentThread(), THREAD_MODE_BACKGROUND_BEGIN))
   {
      dwError = GetLastError();
      if( ERROR_THREAD_MODE_ALREADY_BACKGROUND == dwError)
         printf(TEXT("Already in background mode\n"));
      else printf(TEXT("Failed to enter background mode (%d)\n"), dwError);
      goto Cleanup;
   } 

   // Display thread priority
	
	printf(TEXT("I'm going to change the priority\n"));
   dwThreadPri = GetThreadPriority(GetCurrentThread());

   printf(TEXT("The new thread priority is 0x%x\n"), dwThreadPri);

   //
   // Perform background work
   //
   ;

   if(!SetThreadPriority(GetCurrentThread(), THREAD_MODE_BACKGROUND_END))
   {
      printf(TEXT("Failed to end background mode (%d)\n"), GetLastError());
   }

Cleanup:
   // Clean up
   ;
return 0;
}