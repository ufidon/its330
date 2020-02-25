/** Ref:
 * 1. https://docs.microsoft.com/en-us/windows/win32/sync/using-semaphore-objects
 * How to compile & run?
 * Compile: cl /MD diningPhilosophers.c
 * Run: .\diningPhilosophers.exe
*/
#include <windows.h>
#include <stdio.h>

#define N 5
#define ROUNDS 10

int EAT[N] = {1000,2000,1000,3000,2000};
int THINK[N] = {1200,18000,1400,15000,19000};
int SLOTH[N] = {5000,5000,5000,5000,5000};


HANDLE chopsticks[N];

DWORD WINAPI philosopher( LPVOID lpParam );


DWORD WINAPI philosopher( LPVOID lpParam )
{

    // lpParam not used in this example
    int pID = *(int*) lpParam;
    int r = ROUNDS;
    DWORD dwWaitResult; 
    while (r>=0)
    {
        printf("Philosopher %d is THINKING...\n", pID);
        Sleep(THINK[pID]);

        printf("Philosopher %d is trying picking up his LEFT chopstick\n", pID);
        //pthread_mutex_lock(&chopsticks[pID]);
        dwWaitResult = WaitForSingleObject( 
            chopsticks[pID],   // handle to semaphore
            INFINITE);           // zero-second time-out interval
        printf("Philosopher %d picked up his LEFT chopstick\n", pID);

        /** TODO:
         * 1. compile, run, observe, describe your observation
         * 2. comment out line 47, compile, run, observe, describe your observation
         * 3. explain the difference
        */
        //Sleep(SLOTH[pID]);

        printf("Philosopher %d is trying picking up his RIGHT chopstick\n", pID);
        //pthread_mutex_lock(&chopsticks[(pID+1)%N]);
        dwWaitResult = WaitForSingleObject( 
            chopsticks[(pID+1)%N],   // handle to semaphore
            INFINITE);           // zero-second time-out interval

        printf("Philosopher %d picked up his LEFT chopstick\n", pID);
        
        printf("Philosopher %d picked up his RIGHT chopstick\n", pID);

        printf("Philosopher %d has two chopsticks\n", pID);
        printf("Philosopher %d is dining now...\n", pID);
        Sleep(EAT[pID]);

        printf("Philosopher %d put down his RIGHT chopstick\n", pID);
        //pthread_mutex_unlock(&chopsticks[(pID+1)%N]);
        if (!ReleaseSemaphore( 
                        chopsticks[(pID+1)%N],  // handle to semaphore
                        1,            // increase count by one
                        NULL) )       // not interested in previous count
        {
            printf("ReleaseSemaphore error: %d\n", GetLastError());
        }
        printf("Philosopher %d put down his LEFT chopstick\n", pID);
        //pthread_mutex_unlock(&chopsticks[pID]);
        if (!ReleaseSemaphore( 
                        chopsticks[pID],  // handle to semaphore
                        1,            // increase count by one
                        NULL) )       // not interested in previous count
        {
            printf("ReleaseSemaphore error: %d\n", GetLastError());
        }

        --r;
    }

    printf("Philosopher %d LEFT\n", pID);
    return TRUE;
 
}

int main( void )
{
    HANDLE philosophers[N];
    DWORD ThreadID;
    int* pDataArray[N];
    int i;

    // Create chopsticks as semaphores
    for(i=0; i<N; ++i)
    {
        chopsticks[i] = CreateSemaphore( 
            NULL,           // default security attributes
            1,  // initial count
            1,  // maximum count
            NULL);   // UNNAMED semaphore

        if (chopsticks[i] == NULL) 
        {
            printf("Fail to create chopstick %d, error: %d\n", i, GetLastError());
            return 1;
        }        
    }


    // Create philosopher threads
    printf("The philosophers party BEGINS...\n");
    printf("================================\n");
    for( i=0; i < N; i++ )
    {
        pDataArray[i] =  HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,
                sizeof(int));
        *(pDataArray[i]) = i;
        philosophers[i] = CreateThread( 
                     NULL,       // default security attributes
                     0,          // default stack size
                     (LPTHREAD_START_ROUTINE) philosopher, 
                     (LPVOID)pDataArray[i],       // no thread function arguments
                     0,          // default creation flags
                     &ThreadID); // receive thread identifier

        if( philosophers[i] == NULL )
        {
            printf("Fail to create philosopher %d, Thread error: %d\n", i, GetLastError());
            return 1;
        }
    }

    // Wait for all threads to terminate

    WaitForMultipleObjects(N, philosophers, TRUE, INFINITE);
    printf("================================\n");
    printf("The philosophers party is OVER...\n");  
    // Close thread and semaphore handles
    for( i=0; i < N; i++ )
    {
        CloseHandle(philosophers[i]);
        CloseHandle(chopsticks[i]);
    }

    return 0;
}

