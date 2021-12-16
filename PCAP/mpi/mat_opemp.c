#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <omp.h>

#define THREADS 16

int main(int argc, char **argv) {
    // Initialize the matrices
    int SIZE = atoi(argv[1]);
    
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
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        #pragma omp for
            for(int i = id*(SIZE/THREADS); i < (id + 1)*(SIZE/THREADS); i++) {
                for(int c = 0; c < SIZE; c++) {
                    matrix_c[i][c] = 0;
                    for(int k = 0; k < SIZE; k++) {
                        matrix_c[i][c] += matrix_a[i][k]*matrix_b[k][c];
                    }
                }
            }
    }

    return 0;
}
