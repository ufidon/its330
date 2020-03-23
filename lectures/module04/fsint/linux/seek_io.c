/*************************************************************************\
* Ref: http://man7.org/tlpi/code/online/dist/fileio/seek_io.c.html
\*************************************************************************/

/* seek_io.c

   Demonstrate the use of lseek() and file I/O system calls.

   Usage: seek_io file {r<length>|R<length>|w<string>|s<offset>}...

   This program opens the file named on its command line, and then performs
   the file I/O operations specified by its remaining command-line arguments:

           r<length>    Read 'length' bytes from the file at current
                        file offset, displaying them as text.

           R<length>    Read 'length' bytes from the file at current
                        file offset, displaying them in hex.

           w<string>    Write 'string' at current file offset.

           s<offset>    Set the file offset to 'offset'.

   Example:

        seek_io <file name> wxyz s1 r2
* How to compile & run?
* Compile: gcc seek_io.c -o seek_io
* Run: ./seek_io <file name> {r<length>|R<length>|w<string>|s<offset>}
* 1. Create a text file poem.txt with a poem from http://famouspoetsandpoems.com/top_poems.html
* 2. ./seek_io poem.txt s20 r100
* 3. ./seek_io poem.txt R100
* 4. ./seek_io poem.txt s0 w'This is a comment added on ...'
* 5. ./seek_io poem.txt s0 r30
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>


int main(int argc, char *argv[])
{
    size_t len;
    off_t offset;
    int fd, ap, j;
    unsigned char *buf;
    ssize_t numRead, numWritten;

    if (argc < 3 || strcmp(argv[1], "--help") == 0)
        printf("Usage: %s file {r<length>|R<length>|w<string>|s<offset>}...\n", argv[0]);

    fd = open(argv[1], O_RDWR | O_CREAT,
                S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
                S_IROTH | S_IWOTH);                     /* rw-rw-rw- */

    if (fd == -1)
    {
        printf("failed to open file %s\n", argv[1]);
        exit(1);
    }
        

    for (ap = 2; ap < argc; ap++) {
        switch (argv[ap][0]) {
        case 'r':   /* Display bytes at current offset, as text */
        case 'R':   /* Display bytes at current offset, in hex */
            len = atol(&argv[ap][1]);

            buf = malloc(len);
            if (buf == NULL)
            {
                printf("failed to allocate memory\n");
                exit(2);
            }

            numRead = read(fd, buf, len);
            if (numRead == -1)
            {
                printf("failed to read file\n");
                exit(2);
            }


            if (numRead == 0) {
                printf("%s: end-of-file\n", argv[ap]);
            } else {
                printf("%s: ", argv[ap]);
                for (j = 0; j < numRead; j++) {
                    if (argv[ap][0] == 'r')
                        printf("%c", isprint(buf[j]) ?  buf[j] : '?');
                    else
                        printf("%02x ", buf[j]);
                }
                printf("\n");
            }

            free(buf);
            break;

        case 'w':   /* Write string at current offset */
            numWritten = write(fd, &argv[ap][1], strlen(&argv[ap][1]));
            if (numWritten == -1)
            {
                printf("failed to write file\n");
                exit(2);
            }
            printf("%s: wrote %ld bytes\n", argv[ap], (long) numWritten);
            break;

        case 's':   /* Change file offset */
            offset = atol(&argv[ap][1]);
            if (lseek(fd, offset, SEEK_SET) == -1)
            {
                printf("failed to change to offset %ld\n", offset);
                exit(2);
            }
            printf("%s: seek succeeded\n", argv[ap]);
            break;

        default:
            printf("Argument must start with [rRws]: %s\n", argv[ap]);
        }
    }

    if (close(fd) == -1)
    {
        printf("failed to close file\n");
        exit(2);
    }

    exit(0);
}
