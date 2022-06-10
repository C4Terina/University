#include "RPC.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

void error(char *msg) { //Error messages
	perror(msg);
	exit(1);
}

void res_prog_1(char *host, float a, int n, int c, int *array, int newsockfd){
	CLIENT *clnt;
	avg  *result_1;
	input  rpc_avg_1_arg;
	min_max  *result_2;
	input  rpc_mm_1_arg;
	mult  *result_3;
	input  rpc_mult_1_arg;
	int length, i;
	char *str;

#ifndef	DEBUG
	clnt = clnt_create (host, RES_PROG, RES_VERS, "TCP");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

switch (c){
	case 1:
		// Initialize all our arguments
		rpc_avg_1_arg.a = a;
		rpc_avg_1_arg.Y.Y_len = n;
		rpc_avg_1_arg.Y.Y_val = (int *) calloc(rpc_avg_1_arg.Y.Y_len, sizeof(int));

		for(i = 0; i < n; i++)
			rpc_avg_1_arg.Y.Y_val[i] = array[i]; // Fill the array

		result_1 = rpc_avg_1(&rpc_avg_1_arg, clnt); // Call the RCP function

		if (result_1 == (avg *) NULL)
			clnt_perror (clnt, "call failed");

		// We can't send the average we found as a number so we will first convert it as a string and then send it to RCP soc where it will be converted back into a number
		// This process will be done multiple times

		length = snprintf(NULL, 0, "%.3lf", result_1->avgrs); // Find the length of the average
		str = (char *) calloc(length, sizeof(char));
		sprintf(str, "%lf", result_1->avgrs);
		send(newsockfd, str, 1000, 0); // Send string to RCP soc
		free(rpc_avg_1_arg.Y.Y_val);
		free(str);
		break;
	case 2:
		rpc_mm_1_arg.a = a;
		rpc_mm_1_arg.Y.Y_len = n;
		rpc_mm_1_arg.Y.Y_val = (int *) calloc(rpc_mm_1_arg.Y.Y_len, sizeof(int));

		for(i = 0; i < n; i++)
			rpc_mm_1_arg.Y.Y_val[i] = array[i]; // Fill the array

		result_2 = rpc_mm_1(&rpc_mm_1_arg, clnt); // Call the RCP function

		if (result_2 == (min_max *) NULL)
			clnt_perror (clnt, "call failed");


		str = (char *) calloc(length, sizeof(char));
		for (i = 0; i < 2; i++){
			sprintf(str, "%d", result_2-> mm.mm_val[i]); // Convert from integer to string
			send(newsockfd, str, 1000, 0); // Send the values
		}
		break;
	case 3:
		rpc_mult_1_arg.a = a;
		rpc_mult_1_arg.Y.Y_len = n;
		rpc_mult_1_arg.Y.Y_val = (int *) calloc(rpc_mult_1_arg.Y.Y_len, sizeof(int));

		for(i = 0; i < n; i++)
			rpc_mult_1_arg.Y.Y_val[i] = array[i]; // Fill the array

		result_3 = rpc_mult_1(&rpc_mult_1_arg, clnt); // Call the RCP function

		if (result_3 == (mult *) NULL)
			clnt_perror (clnt, "call failed");

		str = (char *) calloc(n, sizeof(char));
		for (i = 0; i < n; i++){
			sprintf(str, "%.3lf", result_3->mulrs.mulrs_val[i]); // Convert from integer to string
			send(newsockfd, str, 1000, 0); // Send the values
		}
		break;
	default:
		break;
}

#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int main (int argc, char *argv[]){
	char *host;
	int sockfd, newsockfd, portno, clilen;
	pid_t procId;

	float a;
	int n, c, *Y, i, temp, end, sum;
	char str[100];
	int children = 0;
    struct sockaddr_in serv_addr, cli_addr;

	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]); //Check if we use the correct arguments to run the server
		exit (1);
	}

     if (argc < 3) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }

     sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //Create TCP socket for server side
     if (sockfd < 0)
         error("ERROR opening socket");

     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[2]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_port = htons(portno);
     serv_addr.sin_addr.s_addr = INADDR_ANY;

     if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) //Bind to client socket
                  error("ERROR on binding");

     listen(sockfd,5);

 for (;;) {
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen); //Make new socket for each client that connects
     if (newsockfd < 0)
          error("ERROR on accept");
	if(fork() == 0) { // Create Child process
			close(sockfd); // Close Socket because we don't need it anymore
			printf("Connected.\n"); // Message to see we are connected
			end = 0; // For the while loop
			do
			{
				temp = recv(newsockfd, str, 10, 0); // Receive choice
				c = atoi(str); // Convert from string to integer
				if(c == 4) // If choice is 4 then the client chose "Exit"
					end = 1;
				else {
					temp = recv(newsockfd, str, 10, 0); // Receive A
					a = strtod(str, NULL); // Convert from string to float
					temp = recv(newsockfd, str, 10, 0); // Receive n
					n = atoi(str); // Convert from string to integer
					Y = (int *)calloc(n,sizeof(int)); // Calloc the array
					for( i = 0; i < n; i++) {
						temp = recv(newsockfd, str, 10, 0); // Receive the data for Y
						Y[i] = atoi(str); // Convert the data from string to integer and save it to the array
					}
					res_prog_1(argv[1], a, n, c, Y, newsockfd); // Call the RPC Client
				}
			} while(!end);
		}
		close(newsockfd);
		children++;
		while(children) {
			procId = waitpid((pid_t) - 1, NULL, WNOHANG);
			if(procId < 0)
				error("Waitpid error.\n");
			else if(procId == 0)
				break;
			else
				printf("Ending all processes...\n");
		}
	}
	 return 0;
}
