#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error(char *msg){
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[]){
    //Variables
    int sockfd, portno;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    int c, n, i, y, temp, min, max;
    float a, num, average;
    char str[1000];
    int end = 0;

    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]); //Check if client has put the correct arguments
       exit(0);
    }

    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0); //Create socket

    if (sockfd < 0)
        error("ERROR opening socket");


    printf("Opening socket...\n");

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portno);
    inet_aton(argv[1], &serv_addr.sin_addr);

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) //Connecting to TCP server or RCP client
        error("ERROR connecting");

    printf("Connected..\n");

/*======================================= START OF MENU =======================================*/
    do {
        printf("Choose which action you want to perform: \n");
        printf("\n1. Find average of array \n");
        printf("\n2. Find min and max of array \n");
        printf("\n3. Multiply array with number \n");
        printf("\n4. Exit \n");
        printf("\nChoose: ");
        fgets(str, 100, stdin); // Store answer in char array str
		c = atoi(str); // Turn string into an int and store it in c variable

        while(c > 4 || c < 1){
            printf("Wrong input. Please try again.\n");
            fgets(str, 100, stdin); // Store answer in char array str
            c = atoi(str);
        }

        send(sockfd, str, strlen(str), 0); // Send c to RCP client

        if(c != 4){
             printf("\nEnter the number a to multiply the array with: \n");
                fgets(str, 100, stdin);
                a = strtod(str, NULL); // Turn string into a float and store it in a variable
                send(sockfd, str, strlen(str), 0); // Send float a to RCP client

             printf("\nEnter the size of array: \n");
                fgets(str, 10, stdin);
                n = atoi(str); // Turn string into an int and store it in n variable

                while(n <= 0){
                    printf("\nSize can't be negative or zero. Enter again: \n");
                    fgets(str, 100, stdin);
                    n = atoi(str);
                }
                send(sockfd, str, strlen(str), 0); // Send n to RCP client

                printf("\nFill the array\n");
                for(i = 0; i < n; i++){
                    printf("Y[%d]:", i);
                    fgets(str, 100, stdin);
                    y = atoi(str);
                    send(sockfd, str, strlen(str), 0); // Send Y to RCP client
                }

/*======================================= START OF CHOICES =======================================*/

            switch(c){
                case(1):
                    temp = recv(sockfd, str, 1000, 0); // Receive average
                    str[temp] = '\0'; // Str is a char array and by default the value of str[temp] is NULL. We want the last position to be equal to '\0' which is what the end of a string is so the conversion below is done correctly
                    average = strtod(str,NULL); // Convert string to float
                    printf("Average is: %.3lf\n", average );
                    break;
                case(2):
                    temp = recv(sockfd, str, 1000, 0); // Receive minimum
                    str[temp] = '\0';
                    min = atoi(str);
                    temp = recv(sockfd, str, 1000, 0); // Receive maximum
                    str[temp] = '\0';
                    max = atoi(str);
                    printf("Min is: %d\n", min); // Print min
                    printf("Max is: %d\n", max); // Print max
                    break;
                case(3):
                    printf("The multiplied array is: \n");
                    for(i = 0; i < n; i++) {
                        temp = recv(sockfd, str, 1000, 0); // Receive input
                        num = strtod(str, NULL);
                        printf("X[%d]:%.3lf\n", i + 1, num); // Print muplied array
                    }
                    break;
                default:
                    printf("Exiting....\n");
                    break;
            }
        } else
            end = 1;

    } while(!end);

    printf("\nGoodbye!\n");
    close(sockfd);
    return 0;
}
