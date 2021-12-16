#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

//CHILD 2: Prints array in descending order 
//	   Exits after parent becoming ORPHAN

int main(int argc, char *argv[]){
	int i;
	printf("\nINSIDE CHILD 2\n");

	for(i = argc -1; i > -1; i--){
		printf("%s ", argv[i]);
	}

	fflush(stdout);

	sleep(5);

	system("ps -o pid,ppid,stat,comm");

	printf("Second Child became ORPHAN\n");
	return 0;
}
