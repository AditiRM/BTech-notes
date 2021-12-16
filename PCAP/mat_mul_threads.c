#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#define MAX 1024


//Each thread computes single element in the resultant matrix
void *mult(void* arg)
{

	int *data = (int *)arg;
	int k = 0, i = 0;
	
	int x = data[0];
	for (i = 1; i <= x; i++) {
		k += data[i]*data[i+x];
	}
	
	int *p = (int*)malloc(sizeof(int));
	*p = k;

	pthread_exit(p);
}


int main()
{

	int n;
	printf("Enter matrix size: ");
	scanf("%d", &n);
	
	int matA[n][n];
	int matB[n][n];
	int matC[n][n];
	
	int r1=n,c1=n,r2=n,c2=n,i,j,k;


	// Generating random values in matA
	for (i = 0; i < r1; i++)
			for (j = 0; j < c1; j++)
				matA[i][j] = rand() % 10;
		
	// Generating random values in matB
	for (i = 0; i < r1; i++)
			for (j = 0; j < c1; j++)
				matB[i][j] = rand() % 10;
	/*
	printf("Matrix A: \n");
	for (i = 0; i < r1; i++){
		for(j = 0; j < c1; j++)
			printf("%d ",matA[i][j]);
		printf("\n");
	}
			
	printf("Matrix B: \n");			
	for (i = 0; i < r2; i++){
		for(j = 0; j < c2; j++)
			printf("%d ",matB[i][j]);
		printf("\n");
	}
	*/
	
	int max = r1*c2;

	
	//declaring array of threads of size r1*c2	
	pthread_t *threads;
	threads = (pthread_t*)malloc(max*sizeof(pthread_t));
	
	int count = 0;
	int* data = NULL;
	for (i = 0; i < r1; i++) {
		for (j = 0; j < c2; j++) {
			data = (int *)malloc((max)*sizeof(int));
			data[0] = c1;
	
			for (k = 0; k < c1; k++)
				data[k+1] = matA[i][k];
	
			for (k = 0; k < r2; k++)
				data[k+c1+1] = matB[k][j];

			pthread_create(&threads[count++], NULL, mult, (void*)(data));

				
		}
	}

	int store[max];
	
	k = 0;
	for(i = 0; i<n;i++){
		for(j = 0; j < n; j++){
			void *p;
			pthread_join(threads[k], &p);
			int *c = (int *)p;
			store[k] = *c;
			matC[i][j] = store[k];
			k++;
		}
	}

	/*
	printf("Matrix Multiplication: \n");			
	for (i = 0; i < n; i++){
		for(j = 0; j < n; j++)
			printf("%d ",matC[i][j]);
		printf("\n");
	}
	*/
	return 0;
}

