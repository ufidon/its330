// create one child process

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int value = 5;

int main()
{
	pid_t pid, ppid, cpid;

	pid = fork();
	


	if (pid == 0) { /* child process */
		printf("I'm the first child.\n");
		cpid = getpid();
		printf("First child id is %d\n", cpid);
        pause();
		return 0;
	}
	else if (pid > 0) { /* parent process */
		printf("I'm the parent!, my child pid is:%d\n", pid);
		ppid = getpid();
		printf("Parent id is %d\n", ppid);

        // create another child-------------
        pid = fork();
        if (pid == 0) //another child
        {
            printf("I'm the second child.\n");
            cpid = getpid();
            printf("Second child id is %d\n", cpid);

            // create a grandchild
            pid = fork();
            if (pid == 0) { /* child process */
                printf("I'm the grandchild.\n");
                cpid = getpid();
                printf("Grandchild id is %d\n", cpid);
                pause();
                return 0;
            }
            else if(pid>0) //second child
            {
                printf("I'm the parent of the grand child.\n");;
            }

            pause();
            return 0;
        }

        // another child ------------
        

		wait(NULL);

		return 0;
	}

	
}
