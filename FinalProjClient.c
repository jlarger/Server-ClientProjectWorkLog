#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), connect(), send(), and recv() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_addr() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */

#define MAXPENDING 5

/*
 *
 * Remember: to .exe this, you need to put 127.0.0.1 and port 3000 after ./FinalProjClient
 *
 *
 */

struct menu{
  unsigned char line1[300];

  unsigned char line2[50];

  unsigned char line3[50];

  unsigned char line4[50];

  unsigned char line5[50];
};

struct homePage{
   unsigned char line1[50];
   unsigned char line2[50];
   unsigned char line3[50];
   unsigned char line4[50];
   unsigned char line5[50];
   unsigned char line6[50];
};

struct EDITINFO
{
   unsigned char line1[50];
   unsigned char line2[50];
   unsigned char line3[50];
   unsigned char line4[50];
   unsigned char line5[50];
   unsigned char line6[50];
};






char getUserSelection(char userChoice);
//void setUserInfo(USERDATA* data);
void talkToServer(int sock);	
void sendEmail(int sock);
void sendNumber(int sock);
unsigned int displayMenuAndSendSelection(int sock);
void sendFullName(int sock);	
unsigned int displayHomePageInformation(int sock);
void sendEditedMaterial(int sock);


int main(int argc, char *argv[])
{

    


    int sock;
    struct sockaddr_in FinalProjServer;
    unsigned short FinalProjServerPort;
    char * serverIP;
    //char serverBuffer[100];
    int bytesRcvd, bytesRead;

    serverIP = argv[1];             /* First arg: server IP address (dotted quad) */

    FinalProjServerPort = atoi(argv[2]); /* Second arg: port number */


    memset(&FinalProjServer, 0, sizeof(FinalProjServer));     /* Zero out structure */
    FinalProjServer.sin_family = AF_INET;             /* Internet address family */
    FinalProjServer.sin_addr.s_addr = inet_addr(serverIP);   /* Server IP address */
    FinalProjServer.sin_port = htons(FinalProjServerPort); /* Server port */

        

        if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
	{
		printf("error");
	}

     /* Establish the connection to the echo server */
        if (connect(sock, (struct sockaddr *) &FinalProjServer, sizeof(FinalProjServer)) < 0)
	{
		//DieWithError("connect() failed");
	}

	// Connected!!
	
	//talkToServer(sock);



	talkToServer(sock);

	char userChoice;
	
	


	/*
	 *	Make function
	 */
	

	/*if(send(sock, data.username, userStringLen, 0) != userStringLen)
	{
		printf("Error!");
	}
	

	if(send(sock, data.password, passwordStringLen, 0) != passwordStringLen)
	{
		printf("Error!");
	}

	if(send(sock, data.fullName, fullNameStringLen, 0) != fullNameStringLen)
	{
		printf("Error!");
	}*/

	close(sock);


}




/*char getUserSelection(char userChoice)
{

	
	
	printf("Hello! Welcome to your automated application to keep track of recent work projects.\n");
		
	printf("Would you like to sign up or sign in?\n");

	printf("If you would like to sign in, enter c.\n");
							
	printf("If you would like to sign up, enter u.\n"); 
							
	printf("If you would like to quit, enter q.\n");

        scanf("%c", &userChoice);

	switch(userChoice)
	{
		case'c':
		printf("Will be a function that takes care of this\n");
		break;
		case 'u':
		//setUserInfo(data);
		break;
		case 'q':
		printf("Bye!");
		break;
		default:
		printf("Wrong key!\n");
	}

	return userChoice;
}*/


/*
 * Receiving first menu
 */
unsigned int displayMenuAndSendSelection(int sock)

{

    struct menu menuBuffer;     /* Buffer for echo string */
    unsigned int response = 0;

    unsigned int output;



    printf("Inside client display menu\n");

    get(sock, &menuBuffer, sizeof(struct menu));  //in this case server is also sending null

    printf("%s\n", menuBuffer.line1);

    printf("%s\n", menuBuffer.line2);

    printf("%s\n", menuBuffer.line3);

    printf("%s\n", menuBuffer.line4);

    printf("%s\n", menuBuffer.line5);

    scanf("%d", &response);

    output = htonl(response);

   

    put(sock, &output, sizeof(unsigned int));

    return response;

}

unsigned int displayHomePageInformation(int sock)
{
    struct homePage homeInfo;
    unsigned int response = 0;
    unsigned int output;

    get(sock, &homeInfo, sizeof(struct homePage));

    printf("%s\n", homeInfo.line1);
    printf("%s\n", homeInfo.line2);
    printf("%s\n", homeInfo.line3);
    printf("%s\n", homeInfo.line4);
    printf("%s\n", homeInfo.line5);
    printf("%s\n", homeInfo.line6);

    scanf("%d", &response);

    output = htonl(response);

    put(sock, &output, sizeof(unsigned int));

    return response;
}


void talkToServer(int sock)
{

    unsigned int selection = 0;

    unsigned int secondSelection = 0;

    unsigned char bye[5];

    int flag = 1;

    while(flag)

    {

        selection = displayMenuAndSendSelection(sock);

        printf("Client selected: %d\n", selection);

        switch(selection)

        {

            case 1:
		/*
		 * Have to authenticate.
		 */
		sendEmail(sock);
		sendNumber(sock);

		secondSelection = displayHomePageInformation(sock);
		
		secondSelection = htonl(secondSelection);

		put(sock, secondSelection, sizeof(char));

		sendEditedMaterial(sock);



		

		flag = 0;
		
		break;

            case 2:
		sendEmail(sock);
		sendNumber(sock);
		sendFullName(sock);

		flag = 0;
                
                break;

            }

        if(selection == 'q') break;

    }

    selection = htonl(selection);

    put(sock, selection, sizeof(char));

    get(sock, bye, 5);

    printf("%s\n", bye);
}


void sendEditedMaterial(int sock)
{

	struct EDITINFO editInfo;
	unsigned char msg[21];

	char nameOfProject[100];
	char description[1000];
	char data[8];
	char dueData[8];

	get(sock, &editInfo, sizeof(struct EDITINFO));

	printf("%s\n", editInfo.line1);
	scanf("%s", &nameOfProject);
	printf("%s\n", editInfo.line2);
	scanf("%s", &description);
	printf("%s\n", editInfo.line3);
	scanf("%s", &data);
	printf("%s\n", editInfo.line4);
	scanf("%s", &dueData);
	printf("%s\n", editInfo.line5);
	printf("%s\n", editInfo.line6);

	put(sock, &nameOfProject, 100);
	put(sock, &description, 1000);
	put(sock, &data, 8);
	put(sock, &dueData, 8);


	memset(msg, 0, sizeof(msg));
	get(sock, msg, sizeof(msg));

}
	

	







void sendEmail(int sock)

{



    unsigned char msg[21];

    unsigned char name[21];



    memset(msg, 0, sizeof(msg));

    get(sock, msg, sizeof(msg));

    printf("Please enter your email: \n");

    memset(name, 0, 21);

    scanf("%s", name);

    printf("Your email: %s\n", name);

    put(sock, &name, 21);

}



void sendNumber(int sock)

{

    unsigned char msg[21];

    int number;



    memset(msg, 0, sizeof(msg));

    get(sock, msg, sizeof(msg));

    printf("%s\n", msg);

    scanf("%d", &number);

    number = htonl(number);

    put(sock, &number, sizeof(int));

}

void sendFullName(int sock)

{
    unsigned char msg[21];

    unsigned char fullName[21];

    memset(msg, 0, sizeof(msg));

    get(sock, msg, sizeof(msg));

    printf("Please enter your full name: \n");

    memset(fullName, 0, 21);

    scanf("%s", fullName);

    printf("Your full name: %s \n", fullName);

    put(sock, &fullName, 21);

}






/*void setUserInfo(USERDATA* data)
{
	char usernameArray[30];
	char passwordArray[30];
	char fullNameArray[50];

	printf("You've decided to sign up. Please enter your e-mail address, as this will be used as your username: \n");
	
	 * Reading into userArray due to needing to copy that into the struct mem "username"
	 *
	 
	scanf("%s", &usernameArray);
	strcpy(data->username, usernameArray);

	printf("Now enter a password. The password must be at least 8 characters long.\n");
	scanf("%s", &passwordArray);

	if(strlen(passwordArray) > 8)
	{
		strcpy(data->password, passwordArray);
	}
	else
	{
		printf("Password needs to be at least 8 characters.\n");
	}

	printf("Please enter your full name: \n");
	scanf("%s", &fullNameArray);

	if(strlen(fullNameArray) < 50)
	{
		strcpy(data->fullName, fullNameArray);
	}
	else
	{
		printf("Too many charcaters, try again.");
	}

	



	
	 * implement other ways similar to this
	 *
	 *
	 */
	







