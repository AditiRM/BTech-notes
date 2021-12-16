#include <stdio.h> 
#include <stdlib.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>

#include <sys/wait.h>

#define SIZE 100

static pid_t children[SIZE];
static int child_sleep_time[SIZE];

int main(int argc, char *argv[]){
	if(argc < 3){
		fprintf(stderr, "USAGE : ./2 <NO_of_CHILDERN> <PARENT_SLEEP_TIME>\
				[<child1_sleeptime> ...]\n");
		return EINVAL;
	}

	int n_child, n_parent_sleep;

	n_child = atoi(argv[1]);

	if(n_child > SIZE){
		fprintf(stderr, "Maximum number of Children is %d\n", SIZE);
		return EINVAL;
	}

	if(argc != (n_child + 3)){
		fprintf(stderr, "Specify Sleep Time for Each Child\n");
		return EINVAL;
	}

	n_parent_sleep = atoi(argv[2]);

	int i;
	int status;
	int pid_ret;

	for(i = 0; i < n_child; i++){
		child_sleep_time[i] = atoi(argv[3 + i]);
	}

	for(i = 0; i < n_child; i++){
		if ((children[i] = fork()) == -1){
			perror("fork");
			return errno;
		}
		else if (!children[i]){
			sleep(child_sleep_time[i]);
			exit(0);
		}
	}

	sleep(n_parent_sleep);

	for(i = 0; i < n_child; i++){
		printf("CHILD : %d\t", children[i]);
		//Child Process has not changed state, is still running
		if ((pid_ret = waitpid(children[i], &status, WNOHANG)) == 0){
			printf("RUNNING\n");
		}
		else if (pid_ret != -1){
			printf("EXITED\n");
		}
		else{
			printf("ERROR\n");
		}
	}
	return 0;

}
