#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#define MAX 1024

int main()
{
	int n;
	printf("Enter matrix size: ");
	scanf("%d", &n);
	
	int matA[n][n];
	int matB[n][n];
	int mul[n][n];
	
	int r1=n,c1=n,r2=n,c2=n,i,j,k;

	for (i = 0; i < r1; i++) {
		for (j = 0; j < c1; j++) {
			matA[i][j] = rand() % 10;
		}
	}

	for (i = 0; i < r1; i++) {
		for (j = 0; j < c1; j++) {
			matB[i][j] = rand() % 10;
		}
	}
	/*
	printf("Matrix A: \n");
	for (i = 0; i < r1; i++){
		for(j = 0; j < c1; j++) {
			printf("%d ",matA[i][j]);
		}
		printf("\n");
	}
			
	printf("Matrix B: \n");			
	for (i = 0; i < r2; i++){
		for(j = 0; j < c2; j++) {
			printf("%d ",matB[i][j]);
		}
		printf("\n");
	}
	*/
	for(i=0;i<r1;i++) {    
		for(j=0;j<c2;j++) {    
			mul[i][j]=0;    
			for(k=0;k<c1;k++) {
				mul[i][j] += matA[i][k] * matB[k][j];    
			}    
		}    
	}
	/*
	printf("Matrix Multiplication: \n");
	for (i = 0; i < r1; i++){
		for(j = 0; j < c2; j++) {
			printf("%d ",mul[i][j]);
		}
		printf("\n");
	}  
	*/
	return 0;
}
