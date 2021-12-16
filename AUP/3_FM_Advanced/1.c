#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>          
#include <errno.h>
#include <dirent.h>

//argv  1 - foo.txt
// 	2 - bar.txt
// 	3 - bar1.txt

// ./prog1 < foo.txt > bar.txt 2>bar1.txt
//Meaning I undestand
// take input from foo.txt to prog1
// redirect content of foo.txt to bar.txt 
// 	if successfull content of foo.txt will get copied into bar.txt
// 	else error will be redirected to file bar1.txt as "2" represents "stderr"
int main(int argc, char* argv[]){
	int fd1, fd2, fd3;
	fd1 = open(argv[1], O_RDWR| O_CREAT, 0777);
	fd2 = open(argv[2], O_RDWR | O_CREAT| O_APPEND, 0777);
	fd3 = open(argv[3], O_RDWR | O_CREAT| O_APPEND, 0777);

	//Take input from foo.txt into ./prog1 via STDIN
	//dup2(fd1, 0);
	close(0);
	dup(fd1);
//	close(fd1);

//	fd1 = open(argv[1], O_RDWR| O_CREAT, 0777);
	//Redirect content of foo.txt to bar.txt
	if(dup2(fd2, fd1) == -1){
		//redirect STDERR i.e. "2" to bar1.txt if above statement fails 
		dup2(fd3, 2);
	}

	close(fd1);
	close(fd2);
	close(fd3);

	return 0;
}

