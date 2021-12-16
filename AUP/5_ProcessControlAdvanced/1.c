#include <stdio.h> //fflush defined
#include <stdlib.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>

#include <string.h> //for memcpy
#define BUF_SIZE 100
#define N 10
#define MOD 1000

#define ZOMBIE 1
#define ORPHAN 2

static int buf[BUF_SIZE];
static int arr[BUF_SIZE];

//Generate Random Integer Array
void rand_arr(int *arr, int n, int limit){
	int i;
	for(i = 0; i < n; i++){
		arr[i] = rand() % limit;
	}
}

//Binary Search Algo
int binary_search(int *arr, int n, int x){
	int left, right, mid;
	int mid_element;

	left = 0;
	right = n-1;

	while(left <= right){
		mid = (left + right) / 2;
		mid_element = arr[mid];

		if(x < mid_element)
			right = mid + 1;
		else if(x > mid_element)
			left = mid + 1;
		else
			return mid;
	}
	return -1;
}

//MERGES a[left:mid], a[mid:right], using temp
void merge(int *a, int left, int right, int *buf){
	int mid;
	int size = left;
	int lp, rp;

	mid = (left + right) / 2;

	lp = left;
	rp = mid;

	while(lp < mid && rp < right){
		if(a[lp] <= a[rp]){
			buf[size++] = a[lp++];
		}
		else{
			buf[size++] = a[rp++];
		}
	}

	int start, end;
	if (lp == mid){
		start = rp;
		end = right;
	}
	else{
		start = lp;
		end = mid;
	}

	while(start < end){
		buf[size++] = a[start++];
	}

	memcpy(a + left, buf + left, sizeof(int) * (right - left));
}

void serial_MergeSort(int *a, int left, int right, int *buf){
	int mid = (left + right) / 2;
	
	//Already sorted
	if((right - left) <= 1)
		return;

	serial_MergeSort(a, left, mid, buf);
	serial_MergeSort(a, mid, right, buf);

	merge(a, left, right, buf);
}

void arr_print(int *arr, int n){
	int i;
	for(i = 0; i < n; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

int main(int argc, char *argv[]){
	int elem, index;
	int n = N;

	rand_arr(arr, n, MOD);
	
	serial_MergeSort(arr, 0, n, buf);

	//PARENT
	if(fork()) {
#if SCENARIO == ZOMBIE
		sleep(10);
		exit(0);
#elif SCENARIO == ORPHAN
		exit(0);
#endif
	}
	//CHILD
	else{
		arr_print(arr, n);
		printf("\nElement :");

		//Usage of fflush : flush a stream
		//fflush()  forces  a  write  of  all user-space
		//buffered data for the given output or update stream via the  stream's
	      	// underlying write function.
		fflush(stdin);

		scanf("%d", &elem);
		index = binary_search(arr, n, elem);

		if(index >= 0){
			printf("Element %d found @ %d\n", elem, index);
		}
		else{
			printf("Element %d not found\n", elem);
		}
#if SCENARIO == ORPHAN
		printf("CHILD = %d\tPARENT = %d\n",getpid(), getppid());
#endif
	}

}

