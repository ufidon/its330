/** Program: Using C program to allocate memory using malloc on Linux to test OOM killer behavior 
* How to compile & run?
* Compile: gcc mem.c -o mem
* How to use:
* 1. open two terminals
* 2. In terminal 1, run: 
* free -h
* pay attention to the values of used and free of row mem
* 3. In terminal 2, run:
* mem
* in the prompt, type 277777777
* before mem complete, it lasts for 10 seconds, switch to terminal 1, run:
* free -h
* pay attention to the NEW values of used and free of row mem
* 4. wait until mem exit, or freed the allocated memory, run:
* free -h
* pay attention to the NEW values of used and free of row mem
* 5. Switch to terminal 1, run:
* free -h
* in the prompt, type 22222222222
* record and explain the program output
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  int * ptr;
  unsigned long i, n;
  printf("Enter number of int(4 byte) you want to allocate:");
  scanf("%lu", & n);

  printf("Allocating %lu bytes......\n", n * sizeof(int));
  ptr = (int * ) malloc(n * sizeof(int));
  if (ptr == NULL) {
    printf("ERROR!Memory not allocated!");
    exit(0);
  }
  printf("Filling int into memory.....\n");
  for (i = 0; i < n; i++) {
    ptr[i] = 1;
  }
  printf("Sleep 10 seconds......\n");
  sleep(10);
  printf("Free memory.\n");
  free(ptr);
  return 0;
}

/**
* Refs:
* 1. http://www.openkb.info/2014/05/using-c-program-to-allocate-memory.html
* 2. https://serverfault.com/questions/606185/how-does-vm-overcommit-memory-work
* 3. https://www.tecmint.com/change-modify-linux-kernel-runtime-parameters/
* 4. https://manned.org/proc
* 5. https://www.kernel.org/doc/Documentation/vm/overcommit-accounting
*/