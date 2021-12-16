#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

pthread_t tid[4];
int counter;

void* try(void *arg) {
    unsigned long i = 0;
    counter += 1;
    printf("Job %d started\n", counter);

    for(i=0; i<100;i++);
    printf("Job %d finished\n", counter);

    return NULL;
}

int main(void) {
    int i = 0;
    int err;

    while(i < 4) {
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
    
    return 0;
}
