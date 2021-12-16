#include <stdio.h>
#include <mpi.h>
#include <math.h>
#include<unistd.h>
#include<stdlib.h>

MPI_Status status;


int main(int argc, char **argv)  {
	int rank, size;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	if(argc < 2) {
		printf("Enter the correct arguments\n");
		return 1;
	}
	
	int N = atoi(argv[1]);
	
	double a[N][N],b[N][N],c[N][N];

	
	int workers, rows, offset, dest, source, r1=N, c1=N,i,j,k;
	
	if(rank == 0)  {
		for (i = 0; i < r1; i++) {
			for (j = 0; j < c1; j++) {
				a[i][j] = rand() % 10;
				b[i][j] = rand() % 10;
			}
		}
		
		workers = size - 1;

		
		rows = N/workers;
		offset = 0;
		
		for(dest = 1; dest <= workers; dest++) {
			MPI_Send(&offset, 1, MPI_INT, dest, 1, MPI_COMM_WORLD);
			MPI_Send(&rows, 1, MPI_INT, dest, 1, MPI_COMM_WORLD);
			MPI_Send(&a[offset][0], rows*N, MPI_DOUBLE,dest,1, MPI_COMM_WORLD);
			MPI_Send(&b, N*N, MPI_DOUBLE, dest, 1, MPI_COMM_WORLD);
			offset = offset + rows;
		}
		
		for (i=1; i<=workers; i++) {
			source = i;
			MPI_Recv(&offset, 1, MPI_INT, source, 2, MPI_COMM_WORLD, &status);
			MPI_Recv(&rows, 1, MPI_INT, source, 2, MPI_COMM_WORLD, &status);
			MPI_Recv(&c[offset][0], rows*N, MPI_DOUBLE, source, 2, MPI_COMM_WORLD, &status);
		}
		
		
		printf("Matrix multiplication is done\n");
		/*
		for (i=0; i<N; i++) {
			for (j=0; j<N; j++)
				printf("%6.2f   ", c[i][j]);
			printf ("\n");
		}
		*/
	}
	
	if (rank > 0) {
		source = 0;
		MPI_Recv(&offset, 1, MPI_INT, source, 1, MPI_COMM_WORLD, &status);
		MPI_Recv(&rows, 1, MPI_INT, source, 1, MPI_COMM_WORLD, &status);
		MPI_Recv(&a, rows*N, MPI_DOUBLE, source, 1, MPI_COMM_WORLD, &status);
		MPI_Recv(&b, N*N, MPI_DOUBLE, source, 1, MPI_COMM_WORLD, &status);
		
		for (k=0; k<N; k++) {
			for (i=0; i<rows; i++) {
				c[i][k] = 0.0;
				for (j=0; j<N; j++)
			  		c[i][k] = c[i][k] + a[i][j] * b[j][k];
		      	}
		}

		MPI_Send(&offset, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
		MPI_Send(&rows, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
		MPI_Send(&c, rows*N, MPI_DOUBLE, 0, 2, MPI_COMM_WORLD);
		
	}
	

	
	
	MPI_Finalize();
	return 0;
}	

