/** How to compile & run?
 * Compile: gcc diningPhilosophers.c -o diningPhilosophers -lpthread
 * Run: ./diningPhilosophers
*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 5
#define ROUNDS 10

int EAT[N] = {1,2,1,3,2};
int THINK[N] = {2,1,2,2,3};
int SLOTH[N] = {5,5,5,5,5};

pthread_t tphilosophers[N];
pthread_mutex_t chopsticks[N];

void *philosopher(void *arg)
{

    int pID = (int)arg;
    int r = ROUNDS;

    while (r>=0)
    {
        printf("Philosopher %d is THINKING...\n", pID);
        sleep(THINK[pID]);

        printf("Philosopher %d is trying picking up his LEFT chopstick\n", pID);
        pthread_mutex_lock(&chopsticks[pID]);
        printf("Philosopher %d picked up his LEFT chopstick\n", pID);

        /** TODO:
         * 1. compile, run, observe, describe your observation
         * 2. comment out line 40, compile, run, observe, describe your observation
         * 3. explain the difference
        */
        sleep(SLOTH[pID]);

        printf("Philosopher %d is trying picking up his RIGHT chopstick\n", pID);
        pthread_mutex_lock(&chopsticks[(pID+1)%N]);
        printf("Philosopher %d picked up his RIGHT chopstick\n", pID);

        printf("Philosopher %d has two chopsticks\n", pID);
        printf("Philosopher %d is dining now...\n", pID);
        sleep(EAT[pID]);

        printf("Philosopher %d put down his RIGHT chopstick\n", pID);
        pthread_mutex_unlock(&chopsticks[(pID+1)%N]);
        printf("Philosopher %d put down his LEFT chopstick\n", pID);
        pthread_mutex_unlock(&chopsticks[pID]);

        --r;
    }

    printf("Philosopher %d LEFT\n", pID);
    pthread_exit((void *)0);
}



int main(int argc, char *argv[])
{
    int i;

    void *status;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);


    printf("The philosophers party BEGINS...\n");
    printf("================================\n");
    for ( i = 0; i < N; i++)
    {
        pthread_mutex_init(&chopsticks[i], NULL);
        pthread_create(&tphilosophers[i], &attr, philosopher, (void *)i);
    }
    
    pthread_attr_destroy(&attr);


    for (i = 0; i < N; i++)
    {
        pthread_join(tphilosophers[i], &status);
    }

    printf("================================\n");
    printf("The philosophers party is OVER...\n");    

    for ( i = 0; i < N; i++)
    {
        pthread_mutex_destroy(&chopsticks[i]);
    }    
    
    pthread_exit(NULL);
}
