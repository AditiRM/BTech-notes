#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <omp.h>

#define THREADS 16

int main(int argc, char **argv) {
    // Initialize the matrices
    int SIZE = atoi(argv[1]);
	
    //block size
    int block_size  = 4;
    if (argc > 1){
		block_size = atoi(argv[1]);

    }

    int matrix_a[SIZE][SIZE];
    int matrix_b[SIZE][SIZE];
    int matrix_c[SIZE][SIZE];
    
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            matrix_a[i][j] = rand() % 10;
            matrix_b[i][j] = rand() % 10;
            matrix_c[i][j] = 0;
        }
    }
    
    omp_set_num_threads(THREADS);
    int x, y, k, i, j;
    for(i = 0; i < SIZE; i += block_size)
    {
       for(j = 0; j < SIZE; j += block_size){
       		#pragma omp parallel for collapse(2)
	       for(x = 0; x < block_size; ++x){
	       		for(y = 0; y < block_size; ++y){
				for(k = 0; k < SIZE; ++k){
					#pragma omp critical
					matrix_c[i + x][j + y] += matrix_a[i + x][k] * matrix_b[k][j + y];
				}
			}
	       }
       
       }
    }

    return 0;
}
