// ref: 
// 1. man functions' name
// 2. https://stackoverflow.com/questions/29883211/gtkdialog-mapped-without-a-transient-parent
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define N 2

int main()
{
	int i;
	pid_t pid[N];

	const char *programs[] = {"/usr/bin/mate-color-select", "/usr/bin/mate-calc"};


	printf("I'm going to fork children.\n----------------------------\n");

	printf("fork the child 1\n");
	pid[0] = fork();
	if (pid[0] < 0) { /* creating 1-th child failed */ 
		fprintf(stderr, "Failed to fork child 1. \n"); 
		return 1;
	}
	else if (pid[0] == 0) { /* 1-th child process */
		printf("I'm the %d-th child process, I'm going to exec a GUI %s\n", 1, programs[0]);
		execlp(programs[0], programs[0], NULL);
	}
	else { /* parent process */
		printf("fork the child 2\n");
		pid[1] = fork();
		if (pid[1] < 0) { /* creating 2-th child failed */ 
			fprintf(stderr, "Failed to fork child 2. \n"); 
			return 1;
		}
		else if (pid[1] == 0) { /* 2-th child process */
			printf("I'm the %d-th child process, I'm going to exec a GUI %s\n", 2, programs[1]);
			execlp(programs[1], programs[1], NULL);
		}
		else { /* parent process */
			/* parent will wait for the child to complete, there is a problem, could you identify? */
			for (i = 0; i < N; i++)
			{
				waitpid(pid[i],NULL, 0);
				printf("Child %d terminated\n", i);
			}			
			
			printf("all children terminated.\n");
			printf("Parent terminated.\n");
			return 0;
		}

	}

#if BADCODE
	/* problematic: think aobut why?
	for (i = 0; i < N; i++)
	{
		pid[i] = fork();

		if (pid[i] < 0) { /* creating i-th child failed */ 
			fprintf(stderr, "Failed to fork %d-th child\n", i); 
			return 1;
		}

		if (pid[i] == 0) { /* i-th child process */
			printf("I'm the %d-th child process, I'm going to exec a GUI %s\n", i, programs[i]);
			execlp(programs[i], programs[i], NULL);
		}
		else { /* parent process */
			// execlp will overwrite the process's memory, so ...
			/*
			printf("I'm the parent process, I'm going to exec a GUI mate-calc\n");
			execlp("/usr/bin/mate-calc", "/usr/bin/mate-calc", NULL);
			*/
			/* parent will wait for the child to complete */
			wait(NULL);
			printf("Child %d terminated\n", i);
			printf("Parent terminated.\n");
			return 0;
		}			
	}
#endif	
}
