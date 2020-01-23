// header files
#include <stdio.h>
#include <stdlib.h>

// global variables, in data segment
int x;
int y = 15;

// functions and processing codes, in text segment
// its parameters, in stack
int main(int argc, char *argv[])
{
    // local static varables, in bss segment
    int static const=10;
    // local variables, in stack
    int *values;
    int i;

    printf("program start...\n");
    // dynamic allocated memory, in heap
    values = (int *) malloc(sizeof(int)*5);

    for ( i = 0; i < 5; i++)
    {
        values[i] = i;
        
    }

    printf("program is going to terminate!\n");
    
    scanf("%d", &x);

    return 0;
}

