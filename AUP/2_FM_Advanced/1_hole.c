#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#include <sys/types.h>
#include <sys/stat.h>

#define TEXT "ADITIADITI"

int main(int argc, char* argv[]){
	//fs : file descriptor for source file
        //ft : file descriptor for target file

	int fs, ft;
	char buf1[256];
	char buf2[256];
	int bytes;

	//Check valid arguments list
	if (argc != 3){
		fprintf(stderr, "usage: ./1_hole <fs> <ft>");
		return EINVAL;
	}

	if ((ft = open))

	
	return 0;
}
