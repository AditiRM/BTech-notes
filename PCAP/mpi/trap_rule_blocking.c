#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

const double a = 0;
const double b = 10000;

double trapezoid_area(double left_endpt, double right_endpt, int trap_count, double base_len);
double F(double x);


int main(int argc, char** argv) {
	int rank, size, n_trapezoids, n;
	double x0, x1, h, process_integral, final_integral;
	int source;
	
	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	if (argc!= 2){
		printf("Enter the command as : mpirun -np <N> %s <number of trapezoids> \n", argv[0]);
		n_trapezoids = -1;
		MPI_Finalize();
		exit(-1);
	} 
	else {
		n_trapezoids = atoi(argv[1]);
	}
	MPI_Bcast(&n_trapezoids, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	
	//For every process, h and n will be same
	h = (b-a)/n_trapezoids;
	n = n_trapezoids/size;
	
	//For calculating the interval of integration for each process
	x0 = a + rank * n * h;
	x1 = x0 + n * h;
	
	MPI_Barrier(MPI_COMM_WORLD);
	
	//calculate integral of each process
	process_integral = trapezoid_area(x0, x1, n, h);
	
	if (rank != 0) {
		MPI_Send(&process_integral, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
	}
	else {
		final_integral = process_integral;
	      	for (source = 1; source < size; source++) {
			MPI_Status status;
		 	MPI_Recv(&process_integral, 1, MPI_DOUBLE, source, 0, MPI_COMM_WORLD, &status);
			final_integral += process_integral;
	      	}
	      
	      	printf("For n = %d trapezoids:\n", n_trapezoids);
	     	printf("Integration of x^2 from %0.2f to %0.2f = %f\n", a, b, final_integral);
	}
	
	MPI_Finalize();

	return 0;

}	
	
double F(double x) {
	return x * x;
}
	
double trapezoid_area(double left_endpt, double right_endpt, int trapezoid_count, double base_len) {
	double integral, x;
	int i;
	
	integral = (F(left_endpt) + F(right_endpt))/2.0;
	for (i = 1; i <= trapezoid_count-1; i++) {
		x = left_endpt + i * base_len;
		integral += F(x);
	}
	integral = integral * base_len;

	return integral;
}
	
			 
	
	
	
