#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

int done = 1;
int counter;
// Thread function
void* try()
{

	// acquire a lock
	pthread_mutex_lock(&lock);
	if (done == 1) {
		done = 2;
		pthread_cond_wait(&cond1, &lock);
	}
	else {
		counter += 1;
		printf("Job %d started\n", counter);
		for(int i=0; i<100;i++);
		pthread_cond_signal(&cond1);
		printf("Job %d finished\n", counter);
		
	}
	pthread_mutex_unlock(&lock);

	//printf("Returning thread\n");

	return NULL;
}

int main()
{
	pthread_t tid[5];
	int i = 0, err;
	while(i < 5) {
		err = pthread_create(&(tid[i]), NULL, &try, NULL);
		if (err != 0)
		    printf("\ncan't create thread :[%s]", strerror(err));
		i++;
	}

	int j = 0;
	while(j < 5) {
	    	pthread_join(tid[j], NULL);
	    	j++;
	}

	return 0;
}

