#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

pthread_t tid[4];
int counter;
pthread_mutex_t lock;

void* try(void *arg) {
    pthread_mutex_lock(&lock);

    unsigned long i = 0;
    counter += 1;
    printf("Job %d started\n", counter);

    for(i=0; i<100;i++);

    printf("Job %d finished\n", counter);

    pthread_mutex_unlock(&lock);

    return NULL;
}

int main(void) {
    int i = 0;
    int err;

    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }

    while(i < 4)
    {
        err = pthread_create(&(tid[i]), NULL, &try, NULL);
        if (err != 0)
            printf("\ncan't create thread :[%s]", strerror(err));
        i++;
    }
    int j = 0;
    while(j < 4) {
    	pthread_join(tid[j], NULL);
    	j++;
    }
    
    pthread_mutex_destroy(&lock);

    return 0;
}