#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <stdbool.h>


int main(int argc, char **argv){
    int N, *A, *B, val, i, j, ans = 0, sum = 0, tid, chunk, nth, max = -5000, minred = 5000, min_no_red = 5000, min_no_red1 = 5000, min_no_red2 = 5000, min_no_red1_local = 5000;
    bool isddm;
    
    double start;
    double end;
    
    
    do {
        printf("\nPlease insert size of array: ");
        scanf("%d", &N);
        printf("\nPlease type number of threads: ");
        scanf("%d", &nth);
    } while(N <= 0 && nth <= 0);


    A = (int *) malloc(sizeof(int)*N*N);
    chunk = (N*N)/nth;

    printf("\nGive me %d numbers to fill in the array: ", N*N);
		for(i = 0; i < N * N; i ++){
			scanf("%d", &A[i]);
		}
			 
	printf("\nYour matrix is:\n");
		for(i = 0; i < N * N; i ++){
			printf(" %d ", A[i]);
			if(((i + 1) % N) == 0){
					printf("\n");
			}
		}
        start = omp_get_wtime(); //start counting speedup

/*========= START OF QUESTIONS =========*/

   #pragma omp parallel num_threads(nth) default(shared) private(i)
   {
        #pragma omp parallel for schedule(static, chunk) reduction (+:sum) //First reduction sum 
            for(i = 0; i < N*N; i++)
                sum += abs(A[i]);

        #pragma omp parallel for schedule(static, chunk) reduction (-:sum) //Second reduction, substract the diagon from sum 
            for(i = 0; i < N*N; i += N+1){
                sum -= abs(A[i]);
            
                if (abs(A[i]) < sum){ //check if matrix is diagonally dominant 
                    isddm = false;
                }else{ 
                    isddm = true;
                }
            }
        
        #pragma omp single //make one single thread print this 
        if (isddm){
            printf("\nThe matrix is diagonally dominant\n");
        } else {
            printf("\nThe matrix is not diagonally dominant\n");
            exit(0);
        }
    

        #pragma omp parallel for reduction (max:max) private(i) //find max 
            for(i = 0; i < N*N; i += N+1)
                    max = abs(A[i]);
       
        B = (int *) malloc(sizeof(int)*N*N); //dynamically allocate B and fill it 
        j = 0;

        #pragma omp parallel for num_threads(nth) shared(max) private(i)
            for(i = 0; i < N*N; i++){
                if(i != j){
                    B[i] = max - A[i];
                } else {
                    B[i] = max;
                    j += N+1;
                }
            }
         
        #pragma omp parallel for reduction (min:minred) private(i) //find min with reduction clause
            for(i = 0; i < N*N; i++)
                minred = abs(B[i]);
        
        #pragma omp parallel for shared (min_no_red) private(i) //find min without reduction clause 
            for(i = 0; i < N*N; i++){
                if(B[i] < min_no_red)
                    min_no_red = B[i];
            }
        
        #pragma omp parallel for  //find min without reduction clause with critical section protection 
            for(i = 0; i < N*N; i++){
                    if(B[i] < min_no_red1_local){
                        min_no_red1_local = B[i];
                    }
            }
            #pragma omp critical
            {
                if(min_no_red1_local < min_no_red1){
                        min_no_red1 = min_no_red1_local;
                    }
            }
   }

    end = omp_get_wtime(); //stop counting speedup 
    
 
    printf("\nThe max of the diagon is: %d\n", max);

    printf("\nYour matrix B is:\n");
		for(i = 0; i < N*N; i ++){
			printf(" %d ", B[i]);
			if(((i + 1) % N) == 0){
					printf("\n");
			}
		}
    
    printf("\nThe min of matrix B with reduction is: %d\n", minred);
    printf("\nThe min of matrix B without reduction is: %d\n", min_no_red);
    printf("\nThe min of matrix B without reduction with critical is: %d\n", min_no_red1);

    printf("\nWork took %f seconds\n", end-start);

    free(A);
    free(B);
}