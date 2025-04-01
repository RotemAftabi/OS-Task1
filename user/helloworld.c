#include "kernel/types.h"
#include "user/user.h"
int main() 
{
    char *msg = "Hello World xv6\n";
    write(1, msg ,strlen(msg));
    exit(0,"");
}
