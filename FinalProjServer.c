#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), connect(), send(), and recv() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_addr() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */

#define MAXPENDING 5


void DieWithError(char *errorMessage);  /* Error handling function */
void HandleTCPClientWithMenu(int clntSocket);   /* TCP client handling function */

int main(int argc, char *argv[])
{
	    int servSock;                    /* Socket descriptor for server */
	    int clntSock;                    /* Socket descriptor for client */
	    struct sockaddr_in echoServAddr; /* Local address */
	    struct sockaddr_in echoClntAddr; /* Client address */
	    unsigned short echoServPort;     /* Server port */
	    unsigned int clntLen;            /* Length of client address data structure */

	    if (argc != 2)     /* Test for correct number of arguments */

	    {

		    fprintf(stderr, "Usage:  %s <Server Port>\n", argv[0]);

		    exit(1);

	    }


	
	    echoServPort = atoi(argv[1]);  /* First arg:  local port */


	
	    /* Create socket for incoming connections */

	    if ((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		{
		    DieWithError("socket() failed");
		    perror("Socket() failed");
		}


	    /* Construct local address structure */

	    memset(&echoServAddr, 0, sizeof(echoServAddr));   /* Zero out structure */

	    echoServAddr.sin_family = AF_INET;                /* Internet address family */

	    echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY); /* Any incoming interface */

	    echoServAddr.sin_port = htons(echoServPort);      /* Local port */


	
	    /* Bind to the local address */

	    if (bind(servSock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
		{
		    DieWithError("bind() failed");
		    perror("bind() failed");
		}

	
	    /* Mark the socket so it will listen for incoming connections */

	    if (listen(servSock, MAXPENDING) < 0)
	    {
		perror("listen() failed!");

		DieWithError("listen() failed");
	    }

	
	    for(;;) /* Run forever */

	    {

		    /* Set the size of the in-out parameter */

		    clntLen = sizeof(echoClntAddr);


		
		    /* Wait for a client to connect */

		    if ((clntSock = accept(servSock, (struct sockaddr *) &echoClntAddr, &clntLen)) < 0)
			{
			    DieWithError("accept() failed");
			    perror("accept() failed");
			}

		
		    /* clntSock is connected to a client! */


		
		    printf("Handling client %s\n", inet_ntoa(echoClntAddr.sin_addr));


		    HandleTCPClient(clntSock);
	    }

































		    /*
		    char userName[30];
		    char password[30];
		    char fullName[30];
		    
		    int recvSize;

		    

		    while (recvSize > 0)
		    {

		    if (recvSize = recv(clntSock, userName, sizeof(userName), 0) <= 0)
		    {
			//DieWithError("recv() failed");
			perror("recv() failed");

			
		    }

		    if(recvSize = recv(clntSock, password, sizeof(password), 0) <= 0)
		    {
			    perror("recv() failed!");
		    	
		    }

		    if(recvSize = recv(clntSock, fullName, sizeof(fullName), 0) <= 0)
		    {
			    perror("recv() failed!");
		    }

		    }

	       	    

		    
		    printf("%s\n", userName); 
		    //printf("%s\n", password);
		    //printf("%s\n", fullName);
		    

		    
	 	*Make function
	 	*
	 	*/

		    /*
	
		    FILE * fileToWriteData;

		    fileToWriteData = fopen("Information.txt", "w");

		    fprintf(fileToWriteData, "%s", userName);

		    fclose(fileToWriteData);*/
	

		    



		
		    //HandleTCPClient(clntSock);

	    
	
	    
	    

	    /* NOT REACHED */



}
