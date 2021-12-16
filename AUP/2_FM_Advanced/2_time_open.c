#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>

int main(int argc, char *argv[]){
	int fd;

	if(argc != 2){
		fprintf(stderr, "USAGE: ./op <file_name>\n");
		return EINVAL;
	}

	if ((fd = open(argv[1], O_WRONLY | O_CREAT, 0777)) == -1) {
		perror(argv[1]);
		return errno;
	}

	close(fd);
	
	return 0;
}
