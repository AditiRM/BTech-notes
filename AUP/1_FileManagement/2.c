#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define BUF_SIZE 512
#define READ_CHARS 10

int main(int argc, char*argv[]){

	//Case : If command line input is incorrect 
	if (argc != 2) {
		fprintf(stderr,"USAGE : R10W <file_name>\n");
		return EINVAL;
	}

	int fd, count;
	char buff_small[READ_CHARS + 1];

	//Case : open file in Read & write mode failed
	if ((fd = open(argv[1], O_RDWR)) == -1) {
		perror(argv[1]);
		return errno;
	}

	//Now read first 10 char from the file
	if (read(fd, buff_small, READ_CHARS) != READ_CHARS) {
		fprintf(stderr, "This %s file does not have %d char!!!\n", argv[1], READ_CHARS);
		return EINVAL;
	}

	buff_small[READ_CHARS] = '\n';

	//Now write this first 10 characters (which are read using "read()" to stdout)
	if ((count = write(0, buff_small, READ_CHARS + 1)) != READ_CHARS + 1) {
		
		//Write syscall failed!
		if (count == -1) {
			perror(argv[1]);
			return errno;
		}
		else {
			fprintf(stderr, "Unable to write %d characters to STDOUT\n", READ_CHARS + 1);
			return EINVAL;
		}
	}

	//Close file from R&W mode
	close(fd);

	//Open file again in write only +  append mode

	//Case : open failed
	if ((fd = open(argv[1], O_WRONLY | O_APPEND)) == -1) {
		perror(argv[1]);
		return errno;
	}

	//Store our target string(which needs to be written) in a small buffer 
	strcpy(buff_small, "hello");

	if ((count = write(fd, buff_small, strlen(buff_small))) != strlen(buff_small)) {

		if (count == -1){
			perror(argv[1]);
			return errno;
		}
		else {
			fprintf(stderr, "Unable tp write %s at the EOF of %s\n", buff_small, argv[1]);
			return EINVAL;
		}

	}

	return 0;	
}
