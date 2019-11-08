/** modified from:
 * A pthread program illustrating how to
 * create a simple thread and some of the pthread API
 * This program implements the summation function where
 * the summation operation is run as a separate thread.
 *
 * Most Unix/Linux/OS X users
 * gcc thrd.c -lpthread
 *
 * Solaris users must enter
 * gcc thrd.c -lpthreads
 *
 * Figure 4.9
 *
 * @author Gagne, Galvin, Silberschatz
 * Operating System Concepts  - Ninth Edition
 * Copyright John Wiley & Sons - 2013
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* shared data between the reader, or consumer and writer or producer */
#define BUFFER_SIZE		10
typedef struct
{
	int data;
} item;
item buffer[BUFFER_SIZE];
int in = 0;
int out = 0;
int itemcount = 0;


void *reader(void *param); /* the reader thread */
void *writer(void *param); /* the reader thread */

int main(int argc, char *argv[])
{
	pthread_t tidr, tidw;		 /* the thread identifiers */
	pthread_attr_t attr; /* set of attributes for the threads */


	/* get the default attributes */
	pthread_attr_init(&attr);

	/* create the threads */
	pthread_create(&tidw, &attr, writer, NULL);
	pthread_create(&tidr, &attr, reader, NULL);

	/* now wait for the thread to exit */
	pthread_join(tidw, NULL);
	pthread_join(tidr, NULL);

	printf("Program will NOT come here!\n");

	return 0;
}

/**
 * The reader thread will begin control in this function
 */
void *reader(void *param)
{
	item next_consumed;

	while(1){
		while(in == out){
			; /* do nothing, busy waiting*/
		}

		next_consumed = buffer[out];
		out = (out + 1)%BUFFER_SIZE;

		sleep(1);
		printf("Reader consumed item: %d\n", next_consumed.data);		
	}
	

	pthread_exit(0);
}

/**
 * The writer thread will begin control in this function
 */
void *writer(void *param)
{
	item next_produced;

	while(1){
		while((in + 1)%BUFFER_SIZE == out){
			; /* do nothing, busy waiting*/
		}

		next_produced.data = ++itemcount;
		buffer[in] =  next_produced;
		in = (in + 1)%BUFFER_SIZE;
		sleep(1);
		printf("Writer produced item: %d\n", next_produced.data);		
	}
	

	pthread_exit(0);
}
