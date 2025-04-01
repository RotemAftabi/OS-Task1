#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void print_memsize();
void int_to_str(int num, char *str);


int main(int argc, char *argv[])
{
    //(a) Print how many bytes of memory the running process is using by calling memsize.
    print_memsize();

    //(b) Allocate 20k more bytes of memory by calling malloc.
    char* buff = malloc(20000);

    //(c) Print how many bytes of memory the running process is using after the allocation.
    print_memsize();

    //(d) Free the allocated array.
    free(buff);
    
    //(e) Print how many bytes of memory the running process is using after the release.
    print_memsize();

    exit(0,"");
}

void print_memsize(){
    int size = memsize();
    char buffer[20];

    int_to_str(size, buffer);

    write(1, buffer, strlen(buffer));
    write(1, "\n", 1);
}

void int_to_str(int num, char *str) {
    int i = 0;
    int is_negative = 0;

    // Handle negative numbers
    if (num < 0) {
        is_negative = 1;
        num = -num;
    }

    // Extract digits (in reverse order)
    do {
        str[i++] = (num % 10) + '0';  // Convert digit to character
        num /= 10;
    } while (num > 0);

    // Add negative sign if needed
    if (is_negative) {
        str[i++] = '-';
    }

    // Null-terminate the string
    str[i] = '\0';

    // Reverse the string in-place
    for (int j = 0, k = i - 1; j < k; j++, k--) {
        char temp = str[j];
        str[j] = str[k];
        str[k] = temp;
    }
}
