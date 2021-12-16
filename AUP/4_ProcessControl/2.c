#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>

void print_env(char **envp){
	while(*envp){
		printf("%s\n", *envp);
		envp++;
	}
}

int main(){
	extern char **environ;

	print_env(environ);
	printf("\n");

	if(putenv("PATH=/usr/bin") == -1){
		perror("putenv");
		return errno;
	}

	printf("Changed PATH\n");

	print_env(environ);
	return 0;
}


