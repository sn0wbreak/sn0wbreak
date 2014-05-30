#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define check(file) do { \
           struct stat lol; \
	if(stat(path, &lol) != 0) { \
	   exit(0);
#define check2(file) do { \
        int i = check(file);				\
		if(ret) {  \
		  printf("File doesn't exist")

int main(int argc, char *argv[])
{
    char **point = &argv;
    check2(&point);
    
    return 0;
}
