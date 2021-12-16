#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>


#define FACT_NUM 10
#define NO_OF_CHILDREN 2

long int fact(int n){
	long int f;
	if( n == 1){
		f = 1;
	}
	else{
		f = n * fact(n - 1);
	}
	return f;
	
}

void work_done_by_child(int child_num){
	int i;
	//PRINT FACTORIAL VALUES FROM n = 1 to FACT_NUM
	for(i = 1; i <= FACT_NUM; i++){
		printf("Process%d:fact(%d)=%ld\n", child_num, i, fact(i));
	}
	
}

int main(){
	int child, i;
	//STEP 1: CREATE CHILDREN
	//STEP 2: DISPATCH EACH CHILD TP CALCULATE & PRINT FACT (DONE USING work_done_by_child)
	for(i = 0; i < NO_OF_CHILDREN; i++){
		if((child = fork()) == -1){
			//FORK FAILED 
			perror("Creation of child process failed");
		}
		else if(child == 0){
			work_done_by_child(i + 1);
			return 0;
		}
	}

	return 0;
}


