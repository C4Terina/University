#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"
#include <limits.h>


int main(int argc, char* argv[]) {
	
	/* Variables */ 
	int i, j, size, rank, sum = 0, local_num, n, temp = 0, ans, final_ans = 0, final_max = -3000, max, min = 3000, final_min;
	MPI_Status status; 
 	int root = 0;
 	int *A, *A_loc, *x, *B, *B_loc;
 	
 	struct {
		int value;
		int index;
	} in, out;
 
	
	/* Initialize MPI */
	MPI_Init(&argc, &argv);                
  	MPI_Comm_size(MPI_COMM_WORLD, &size);    /* Get size of processes */
  	MPI_Comm_rank(MPI_COMM_WORLD, &rank);    /* Get own identifier */
  	
  		
  		/* Start of first question of the assignment */	
		/* Process 0 does this */
  		if (rank == 0) {   
  			printf("Please type the number N.\n");
			scanf("%d", &n);
			if((n * n) % size != 0) // ERROR message.
			{ 
			    printf("Wrong, arguments.\nN squared must be an integer multiple of the number of processes\n");
			    MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
			}
			
			A = (int *)malloc(sizeof(int) * n * n); // Dynamic allocation of array x
			local_num = (n*n)/size;
			
			printf("\nGive me %d numbers to fill in the array", n*n);
			for(i = 0; i < n * n; i ++){
			    scanf("%d", &A[i]);
			}
			 
			 /* Print out the matrix before it is distributed */
			 printf("\nYour matrix is:\n");
			 for(i = 0; i < n * n; i ++){
				    printf(" %d ", A[i]);
				    if(((i + 1) % n) == 0){
					printf("\n");
				    }
			}
		}
		
		MPI_Bcast(&n, 1, MPI_INT, root, MPI_COMM_WORLD);
		MPI_Bcast(&size, 1, MPI_INT, root, MPI_COMM_WORLD);
		MPI_Bcast(&local_num, 1, MPI_INT, root, MPI_COMM_WORLD);
		
		A_loc = (int *)malloc(sizeof(int) * local_num); // Malloc for each process
		x = (int *)malloc(sizeof(int) * size);
		
		/* Scatter array by rows using MPI_Scatter */
		MPI_Scatter(A, local_num, MPI_INT, A_loc, local_num, MPI_INT, root, MPI_COMM_WORLD);  
			    
		/* Find sum of each row */
		
		for (j = 0; j < local_num; j++){              
			sum += abs(A_loc[j]);   
		}
			
			for(i = rank*(n/size); i < local_num; i += n+1){
				sum -= abs(A_loc[i]); //remove element in the diagonal so we can check if our matrix it's SDD
				
				if (abs(A_loc[i]) < sum){ 
					  ans = 0; //if yes then the final answer is no
				}
				else {
					  ans = 1; //if no then the final answer is yes
				}
			}	
			
		MPI_Gather(&ans, 1, MPI_INT, x, 1, MPI_INT, root, MPI_COMM_WORLD); //gather all answer in array a
	    	
	    	/*If I'm the main process */
	    	if (rank == 0){	 
	    		for(i = 0; i < size; i++){
	    			final_ans += x[i]; //calculate how many sums we got
	    		}
	    			
		 		if (final_ans == size){ //if the amount of sums is equal to the amount of processors then it means that every processor has ans = 1 and so our matrix is SDD
		  			printf("\nYes\n");
		  		}
		  		else {
		  			printf("\nNo\n");
		  		}	
		    }
		 
		/* End of first question */
		MPI_Bcast(&final_ans, 1, MPI_INT, root, MPI_COMM_WORLD); //bcast final answer to use for the second question 
		 
		/*Start of second question: find diagonal max in the array if matrix is SDD*/
		if(final_ans == size){
		 	max = 0;
			for(i = rank*(n/size); i < local_num; i += n+1){ // check only diagonal max  
				if(A_loc[i] > max) 
					max = A_loc[i];
		 	}
		 	
		 	//printf("\n Process %d: local max = %d \n", rank, max);

		 	root = 0;
		 	MPI_Reduce(&max, &final_max, 1, MPI_INT, MPI_MAX, root, MPI_COMM_WORLD);
		 	
		 	if (rank == 0){
				printf("\n The max is: %d \n", final_max); 
			}
			
			// Send final_max to all processes for question 3 
			MPI_Bcast(&final_max, 1, MPI_INT, root, MPI_COMM_WORLD);
		 } 
		 else {
		 	printf("Your array isn't diagonally dominant. Exiting....\n");
		 	exit(0);
		}
		/* End of second question */
		
		/* Start of third question */
		B = (int *)malloc(sizeof(int) * n * n); //Dynamic allocation of B
		B_loc = (int *)malloc(sizeof(int) * local_num); //Dynamic allocation of B_loc
		
		if(final_max != -3000){
			min = 0;
			j = rank*(n/size); //initialize j so we can check the diagonal 
			for(i = 0; i < local_num; i++){
					if(i != j){
						B_loc[i] = final_max - abs(A_loc[i]);
					}
					else{
						B_loc[i] = final_max;
						j += n+1; //if it's in the diagonal then add n+1 so it checks the next element in the diagonal
					}
			}
			in.value = B_loc[0]; 
			in.index = 0; 
			for (i = 1; i < local_num; i++) 
				if (in.value > B_loc[i]) { 
					in.value = B_loc[i]; 
					in.index = i; 
				} 
		}
		
		in.index = (rank * local_num * n) + in.index;
		MPI_Reduce(&in, &out, 1, MPI_2INT, MPI_MINLOC, root, MPI_COMM_WORLD); 
		//Gather everything and put them in array B 
		MPI_Gather(B_loc, local_num, MPI_INT, B, local_num, MPI_INT, root, MPI_COMM_WORLD);
	    	
	    	if (rank == 0){
				printf("Your new matrix B is:\n");
					for(i = 0; i < n * n; i ++){
						printf(" %d ", B[i]);
						if(((i + 1) % n) == 0){
							printf("\n");
				        	}
			         	}
			printf("The min is %d and the min's location is B[%d][%d]", out.value, out.index / n, out.index % n);
		}
		
		
		/* End of third and fourth question */ 
		free(B_loc);
		free(A_loc);
		
		if (rank == 0){
			free(A);
			free(B);
			free(x);
		} 
	    	MPI_Finalize();
}
