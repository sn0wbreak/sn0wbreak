/** @file file_get_contents.c
  * Implementation of the file_get_contents function
  *f from https://github.com/adamlamers/Utility-Classes
  */
#include <stdio.h>
#include <stdlib.h>
#include "file_get_contents.h"
/* If on windows, redefine E_OUTOFMEMORY to the standard Linux ENOMEM */
#ifdef WIN32
# include <windows.h>
#  ifndef ENOMEM
#   define ENOMEM E_OUTOFMEMORY
#  endif
#else
# include <errno.h>
#endif

/** Load all of a files contents into outputBuffer
  * @param filePath Path to the file to load.
  * @param outputBuffer Pointer to the buffer that holds the data (will be reallocated to the correct size)
  * @param outLength Pointer to an unsigned long that holds the number of bytes read into the buffer.
  */
int file_get_contents(const char *filePath, char **outputBuffer, unsigned long *outLength)
{
    FILE *infile = fopen(filePath, "rb");
    if(infile == NULL)
        return -1;

    *outLength = 0;

    void *buf = NULL;
    int bytesRead;
    do
    {
        buf = realloc(buf, *outLength + 4096);
        if(buf != NULL)
        {
            bytesRead = fread((char *)(buf + *outLength), sizeof(char), 4096, infile); //offset the buffer write location to the current position, then append the data into current memory
            *outLength += bytesRead;
        }
        else
        {
            return ENOMEM;
        }
    }while(bytesRead != 0);

    *outputBuffer = malloc(*outLength); //allocate output buffer
    memcpy(*outputBuffer, buf, *outLength); // write data to output buffer

    free(buf); //free temporary buffer, then return
    return 0;
}
