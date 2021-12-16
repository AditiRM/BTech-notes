#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <omp.h>

int main(int argc, char** argv){

    if(argc < 2) {
        printf("Enter the correct arguments\n");
        return 1;
    }
    int threads = atoi(argv[1]);
    omp_set_num_threads(threads);
    
    int partial_Sum, total_Sum = 0, shared_sum = 0;
    sem_t semaphore;
    sem_init(&semaphore, 0, 1);
    
    #pragma omp parallel private(partial_Sum) shared(total_Sum, shared_sum)
    {
        partial_Sum = 0;

        #pragma omp for
        for(int i = 1; i <= 1000; i++){
            partial_Sum += i;
            sem_wait(&semaphore);
            shared_sum += i;
            sem_post(&semaphore);
        }
        
        #pragma omp critical
        {
            printf("Sum Calculated by Thread No. %d is %d\n", omp_get_thread_num(), partial_Sum);
            total_Sum += partial_Sum;
        }
    }
    sem_destroy(&semaphore);
    printf("Total Sum: %d\n", total_Sum);
    printf("Shared Sum: %d\n", shared_sum);
    return 0;
}
