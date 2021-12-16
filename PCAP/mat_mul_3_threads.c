#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#define MAX 1024

int matA[MAX][MAX];
int matB[MAX][MAX];
int matC[MAX][MAX];
	
int n;
int step_i = 0;

void* multi(void* arg)
{
    int i = step_i++; //i denotes row number of resultant matC
   
    for (int j = 0; j < MAX; j++)
      for (int k = 0; k < MAX; k++)
        matC[i][j] += matA[i][k] * matB[k][j];
}


int main()
{
	int r1=MAX,c1=MAX,r2=MAX,c2=MAX,i,j,k;


	// Generating random values in matA
	for (i = 0; i < r1; i++)
			for (j = 0; j < c1; j++)
				matA[i][j] = rand() % 10;
		
	// Generating random values in matB
	for (i = 0; i < r1; i++)
			for (j = 0; j < c1; j++)
				matB[i][j] = rand() % 10;

	
	
	printf("Enter number of threads: ");
	scanf("%d", &n);
		
	pthread_t threads[n];
	
	// Creating four threads, each evaluating its own part
	for (int i = 0; i < n; i++) {
		int* p;
		pthread_create(&threads[i], NULL, multi, (void*)(p));
	}
	 
	// joining and waiting for all threads to complete
	for (int i = 0; i < n; i++)
		pthread_join(threads[i], NULL);   
	


	return 0;
}

