// ref: https://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.html

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>

void *functionC();
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int counter = 0;

int main(void)
{
   int rc1, rc2;
   pthread_t thread1, thread2;

   /* Create independent threads each of which will execute functionC */

   if ((rc1 = pthread_create(&thread1, NULL, &functionC, NULL)))
   {
      printf("Thread 1 creation failed: %d\n", rc1);
   }

   if ((rc2 = pthread_create(&thread2, NULL, &functionC, NULL)))
   {
      printf("Thread 2 creation failed: %d\n", rc2);
   }

   /* Wait till threads are complete before main continues. Unless we  */
   /* wait we run the risk of executing an exit which will terminate   */
   /* the process and all threads before the threads have completed.   */

   pthread_join(thread1, NULL);
   pthread_join(thread2, NULL);

   exit(0);
}

void *functionC()
{
   int i = 0;
   pthread_t myid;

   for (i = 0; i < 5; i++)
   {
      
      pthread_mutex_lock(&mutex1);
      // Refer to: http://man7.org/linux/man-pages/man3/pthread_self.3.html
      // TODO : SHOW "thread id modified counter from ? to ?"
      myid = pthread_self();
      counter++;
      printf("Thread %ld  changed counter value to be: %d\n", myid, counter);
      
      // End of TODO
      pthread_mutex_unlock(&mutex1);
   }
}
