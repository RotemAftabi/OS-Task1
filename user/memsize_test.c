#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int main(int argc, char *argv[])
{
    //(a) Print how many bytes of memory the running process is using by calling memsize.
    printf("%d\n", memsize());

    //(b) Allocate 20k more bytes of memory by calling malloc.
    char *buff = malloc(20000);

    //(c) Print how many bytes of memory the running process is using after the allocation.
    printf("%d\n", memsize());

    //(d) Free the allocated array.
    free(buff);
    
    //(e) Print how many bytes of memory the running process is using after the release.
    printf("%d\n", memsize());

    exit(0,"");
}

