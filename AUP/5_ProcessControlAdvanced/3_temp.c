#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>

void child_1_States(void){
	printf("I am the first-born: %d\n", getpid());
	exit(0);
}

void child_2_States(void){
	sleep(100);
	exit(0);s
}

int main(int argc, char*argv[]){
	int child_pid, i;

	void(*child_States[])(void) = {child_1_States, child_2_States};

	for(i = 0; i < 2; i++) {
		if ((child_pid = fork()) == -1) {
			perror("fork");
			return errno;
		}
		else if	(!child_pid){
			//IN CHILD
			child_States[i]();
			//WILL NEVER RETURN HERE ....LOL....
			//FUNCTION HAS exit() in it
		}
		
	}

	if(system("ps -o command,pid,ppid,state") == -1)
		perror("ps -o command, pid, ppid, state");

	return 0;
}
