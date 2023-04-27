#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int	cmpfunc(const void *, const void *);
//void generate_list(int *, int);
void print_list(int *, int);
void merge(int *, int *, int *, int *, int *);
void multisort(int *, int *, int);

int cmpfunc(const void *a, const void *b){
    return (*(int*)a - *(int*)b);
}

void merge(int *X, int *size_X, int *tmp, int *size_tmp, int *res){
	while (X <= size_X && tmp <= size_tmp) {
		if (*X < *tmp)
			*res++ = *X++;
		else
			*res++ = *tmp++;
	}
	while (X <= size_X) //merging the lower half
		*res++ = *X++;
	while (tmp <= size_tmp) //merging the upper half
		*res++ = *tmp++;
}

void multisort(int *X, int *tmp, int n){
    int chunk = n/4; 
    int *startA, *startB, *startC, *startD, *spaceA, *spaceB, *spaceC, *spaceD;

    if (chunk < 4){ //if the list is too short for the amount of threads we have then use quicksort
        qsort(&X[0], n, sizeof(int), cmpfunc);
    } else {
        startA = X;            
        spaceA = tmp;
        startB = startA + chunk; 
        spaceB = spaceA + chunk;
        startC = startB + chunk; 
        spaceC = spaceB + chunk;
        startD = startC + chunk; 
        spaceD = spaceC + chunk;
                    
        //split the input array to 4 subarrays
        #pragma omp task
            multisort(startA, spaceA, chunk);
        #pragma omp task
            multisort(startB, spaceB, chunk);
        #pragma omp task
            multisort(startC, spaceC, chunk);
        #pragma omp task
            multisort(startD, spaceD, n - 3 * chunk);
        #pragma omp taskwait
        //merge the 4 subarrays in couples

        //merge the couples together
        #pragma omp task
            merge(startA, startA + chunk - 1, startB, startB + chunk - 1, spaceA);
        #pragma omp task
            merge(startC, startC + chunk - 1, startD, X + n - 1, spaceC);
        #pragma omp taskwait
            merge(spaceA, spaceC - 1, spaceC, tmp + n - 1, X);
    }

}


int main(){
    int n, i, nth; 
    int *X, *tmp;
    float start, end;
    
    printf("Give me size of array: \n");
    scanf("%d", &n);

    printf("Please give me number of threads: \n");
    scanf("%d", &nth);

    X = malloc(sizeof(int)*n);
    tmp =  malloc(sizeof(int)*n);
    srand(time(NULL));

    for (i = 0; i < n; i++)
		X[i] = rand() % 100;
    
    printf("Randomizing list...\nYour list is: \n");
    for (i = 0; i < n; i++) 
      printf("%d ", X[i]);
    
    start = omp_get_wtime(); //start counting 
    
    omp_set_num_threads(nth);
	multisort(X, tmp, n);
    printf("\nYour list after the sort: ");
	for (i = 0; i < n; i++) 
      printf("%d ",X[i]);

	end = omp_get_wtime(); //stop counting 
	
    printf("\nTotal time: %f seconds\n", end - start);

	free(X);
    free(tmp);
    
    return 0;
}

