#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

int main () {
    long result;
    errno = 0;

    printf("Method 1 : Using sysconf \n");
    if ((result = sysconf (_SC_OPEN_MAX)) == -1)
        if (errno == 0)
        puts ("OPEN_MAX is not supported.");
        else perror ("sysconf () error");
    else 
        printf("_SC_OPEN_MAX = %ld\n", result);
    

    printf("Method 2 : Using For loop \n");
    int i;
    for (i = 0; i < 10000; ++i){
        if (!fopen("/dev/null", "r")) {
            printf("i = %d\n", i);
            perror("fopen"); 
            exit(1);
        }
    }
    return 0;
}