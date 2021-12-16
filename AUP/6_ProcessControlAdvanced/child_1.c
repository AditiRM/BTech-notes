#include <stdio.h>

//CHILD 1 : Prints array in ascending order & exits
//	    Becomes ZOMBIE

int main(int argc, char *argv[]){
	int i;
	printf("\nINSIDE CHILD 1\n");
	for(i = 0; i < argc; i++){
		printf("%s ", argv[i]);
	}
	return 0;
}
