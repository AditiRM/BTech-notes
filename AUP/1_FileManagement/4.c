#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
 #include <sys/wait.h>

#include <stdlib.h>
#include <sys/types.h>
int main() {

    printf("Starting main\n");

     int fd1 = open("test.txt", O_WRONLY | O_TRUNC | O_CREAT, 0666);

     int fd2 = dup(STDOUT_FILENO);

     dup2(fd1, STDOUT_FILENO);

     pid_t child_pid = fork();

    if (child_pid != 0) {

          wait(NULL); printf("In parent\n"); }

    else { dup2(fd2, STDOUT_FILENO); printf("In child\n"); }

    printf("Ending main: %d\n", child_pid);

}


