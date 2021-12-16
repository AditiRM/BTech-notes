#include <stdio.h>
#include <mpi.h>
#include <math.h>
#include <string.h>

int main(int argc, char* argv) {
	MPI_Status status;
	int num;
	
	MPI_Request request;
	//Initialize MPI computation
	MPI_Init(NULL, NULL);
	//Determine a process's ID number
	MPI_Comm_rank(MPI_COMM_WORLD, &num);
	
	double d = 100.0;
	char arr[] = "Hello World";
	
	int tag = 1;
	
	if(num == 0) {
		MPI_Isend(arr, strlen(arr)+1, MPI_BYTE, 1, tag, MPI_COMM_WORLD, &request);
		MPI_Irecv(arr, strlen(arr)+1, MPI_BYTE, 1, tag, MPI_COMM_WORLD, &request);
		MPI_Wait(&request, &status);
		printf("%s revcieved from process %d\n", arr, num);
	}
	else {
		MPI_Isend(arr, strlen(arr)+1, MPI_BYTE, 0, tag, MPI_COMM_WORLD, &request);
		MPI_Irecv(arr, strlen(arr)+1, MPI_BYTE, 0, tag, MPI_COMM_WORLD, &request);
		MPI_Wait(&request, &status);
		printf("%s revcieved from process %d\n", arr, num);
	}
	
	MPI_Finalize();
	return 0;
}
