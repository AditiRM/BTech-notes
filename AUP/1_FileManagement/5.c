#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "%s\n", "OP file name missing.");
        return 1;
    }
    char buffer[1024] = {0};
    int fd = open(argv[1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) {
        fprintf(stderr, "%s\n", "OP file create failed.");
        return 2;
    }
    ssize_t nread = 0;
    while((nread = read(STDIN_FILENO, buffer, 1024)) != 0) {
        if (write(STDOUT_FILENO, buffer, nread) != nread) {
            fprintf(stderr, "%s\n", "Failed to write to stdout");
            return 3;
        }
        if (write(outfd, buffer, nread) != nread) {
            fprintf(stderr, "%s\n", "Failed to write to file");
            return 4;
        }
    };
    return 0;
}
