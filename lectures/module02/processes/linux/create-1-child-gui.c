// ref: 
// 1. man functions' name
// 2. https://stackoverflow.com/questions/29883211/gtkdialog-mapped-without-a-transient-parent
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	pid_t pid,cpid,ppid;

	/* fork a child process */
	printf("I'm going to fork a child.\n");
	pid = fork();

	if (pid < 0) { /* error occurred */ 
		fprintf(stderr, "Fork Failed"); 
		return 1;
	}

	if (pid == 0) { /* child process */
		printf("I'm the child process, I'm going to exec a GUI mate-color-select\n");
		execlp("/usr/bin/mate-color-select", "/usr/bin/mate-color-select", NULL);
	}
	else { /* parent process */
		// execlp will overwrite the process's memory, so ...
		/*
		printf("I'm the parent process, I'm going to exec a GUI mate-calc\n");
		execlp("/usr/bin/mate-calc", "/usr/bin/mate-calc", NULL);
		*/
		/* parent will wait for the child to complete */
		wait(NULL);
		printf("Child terminated\n");
		printf("Parent terminated.\n");
	}

	return 0;
}
