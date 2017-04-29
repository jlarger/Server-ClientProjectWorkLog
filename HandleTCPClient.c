#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for recv() and send() */
#include <unistd.h>     /* for close() */
#include <stdlib.h>
#include <string.h>

#define RCVBUFSIZE 32   /* Size of receive buffer */

#define NAME_SIZE 21 /*Includes room for null */


struct menu{
  unsigned char line1[300];
  unsigned char line2[50];
  unsigned char line3[50];
  unsigned char line4[50];
  unsigned char line5[50];
} men;


typedef struct
{
  unsigned char name[NAME_SIZE];
  int number;
  char fullName[20];
}USERDATA;

struct HOMEINFO
{
   unsigned char line1[50];
   unsigned char line2[50];
   unsigned char line3[50];
   unsigned char line4[50];
   unsigned char line5[50];
   unsigned char line6[50];
};

typedef struct 
{
   unsigned char nameOfProject[100];
   unsigned char description[1000];
   unsigned char data[8];
   unsigned char dueData[8];
   unsigned int numOfPeopleOnTeam;
   
   //something with a linkedlist
}PROJECTDATA;

typedef struct
{	
   unsigned int block;
   USERDATA * dataPTR;
   PROJECTDATA * projDataPTR;
   struct node * next;
}NodeType;

struct EDITINFO
{
   unsigned char line1[50];
   unsigned char line2[50];
   unsigned char line3[50];
   unsigned char line4[50];
   unsigned char line5[50];
   unsigned char line6[50];
};






void DieWithError(char *errorMessage);  /* Error handling function */
void get(int, void *, unsigned int);
void put(int, void *, unsigned int);
int sendMenuAndWaitForResponse(int);
void askForName(int sock, char *, unsigned int);
void doSomethingWithName(char *);
void askForNumber(int sock, int *, unsigned int);
void doSomethingWithNumber(int);
void doSomethingWithFullName(char * fullName);	
void askForFullName(int sock, char * fullName, unsigned int size);
void writeDataToFile(USERDATA * data, char fullName[]);
void startList(NodeType ** headPTR, USERDATA * newInfoPTR);
void traverseUsers(NodeType * head);
int checkIfAlreadyUser(NodeType * head,char userChoice[]);
int sendHomePage(int clntSocket);
void readDataFromFile(struct PROJECTDATA * data, FILE * file, char name[]);
void traverseProjects(NodeType * head);
void sendEditInformation(int clntSocket);	




void HandleTCPClient(int clntSocket)
{
    int recvMsgSize;                    /* Size of received message */
    unsigned int response;
    unsigned int secondResponse;
    unsigned char name[NAME_SIZE]; //max length 20
    int number = 0;
    USERDATA peopleData;
    
    
    USERDATA linkedListStart;


    PROJECTDATA projData[10];
    char fullName[20];
    unsigned char errorMsg[] = "Invalid Choice";
    unsigned char bye[] = "Bye!";
    int returnValueForComparing;

    /*
     * Linked List bullshit
     *
     */

    FILE * readDataIntoList;

    readDataIntoList = fopen("Information.txt", "r");

    fscanf(readDataIntoList, "%s", linkedListStart.name);

    NodeType * head = 0;

    startList(&head, &linkedListStart);

    traverseUsers(head);



    NodeType * projectHead = 0;

    startList(&projectHead, &projData);

    





    /*
     *
     * Sign up and sign in bullshit
     *
     */

    response = sendMenuAndWaitForResponse(clntSocket);
    printf("%d\n", response);

    while(response != 3)
    {
        switch(response)
        {
            case 1: printf("Client selected to sign in.\n");
		    
		    askForName(clntSocket, peopleData.name, NAME_SIZE);
		    printf("%s\n", peopleData.name);
		    askForNumber(clntSocket, &peopleData.number, sizeof(int));

		    /*
		     * After authentication, start list.
		     */

		    
		    
		    /*FILE * projectFile;

		    NodeType * projectsHead = 0;

			char nameOfFile[75];

			strcpy(nameOfFile, ("%s", name));
			strcpy(nameOfFile, "@erau.edu.myproj.txt");

	


			projectFile = fopen("projFile.txt", "r");


		     while(!feof(projectFile))
		     {
			if(fgets(projData.nameOfProject, 100, projectFile) != NULL)
			{
				//puts(projData.nameOfProject);
			}
			if(fgets(projData.description, 1000, projectFile) != NULL)
			{
				//puts(projData.description);
			}
			if(fgets(projData.data, 10, projectFile)!=NULL)
			{
				//puts(projData.data);
			}
			if(fgets(projData.dueData, 10, projectFile)!=NULL)
			{
				//puts(projData.dueData);
			}
			if(fgets(projData.dueData, 2, projectFile) != NULL)
			{
				//printf("%d", projData.numOfPeopleOnTeam);
			}

		     }
		     
				//fscanf(projectFile, "%s\n %s\n %s\n %s\n %d\n", projData.nameOfProject, projData.description, projData.data, projData.dueData, projData.numOfPeopleOnTeam);
			//printf("%s\n", projData.description);


			
			


		    fclose(projectFile);*/




		    //startList(&projectsHead, &projData);

		    //traverseProjects(projectsHead);





		    secondResponse = sendHomePage(clntSocket);
		    printf("%d\n", secondResponse);

		    while(secondResponse != 0)
		    {
			switch(secondResponse)
			{
				case 1:
					printf("User wanted to create a new entry.\n");
					secondResponse = 0;
					break;
				case 2:
					printf("User wanted to edit an entry.\n");
					sendEditInformation(clntSocket);
					break;
				case 3:
					printf("User wanted to delete an entry.\n");
					break;
				case 4: 
					printf("User wanted to save an entry.\n");
					break;
				case 5: 
					printf("User wanted to display the information.\n");
					break;
				default:
					printf("User press wrong key idoit\n");
					break;
			}
		    }
		    
		    // * This needs to be signing in function
		     
		     
                    		    //askForPassword
		    
                    break;
            case 2: printf("Client selected to sign up.\n");
		    
		     //This needs to be signing up function
		     
		     
		    
		    askForName(clntSocket, peopleData.name, NAME_SIZE);
		    printf("%s\n", peopleData.name);
		    doSomethingWithName(peopleData.name);


		    returnValueForComparing = checkIfAlreadyUser(head, peopleData.name);

		    if(returnValueForComparing == 1)
		    {
			    /*
			     * Need to send this to client if have time to build
			     */
			 printf("you're already a user! Try again by rebooting.\n");
			    /*
			     * login screen
			     */
			 response = 3;
			 break;
		    }
		    else
		    {

			askForNumber(clntSocket, &peopleData.number, sizeof(int));
                    	doSomethingWithNumber(peopleData.number);

		    
		    	askForFullName(clntSocket, fullName, 20);
		    
		    	doSomethingWithFullName(fullName);
			


		    	writeDataToFile(&peopleData, fullName);
			break;

	 	    }



                    break;
 	    case 3: printf("Bye!");
		    break;
            default: printf("Client selected junk.\n"); 
		     put(clntSocket, errorMsg, sizeof(errorMsg)); 
		     break;
        }

    
        //response = sendMenuAndWaitForResponse(clntSocket);
    }

    put(clntSocket, bye, sizeof(bye));
    close(clntSocket);    /* Close client socket */
    printf("Connection with client %d closed.\n", clntSocket);
}


void startList(NodeType ** headPTR, USERDATA * newInfoPTR)
{
	NodeType * newNodePTR;
	NodeType * ptr = *headPTR;
	NodeType * prevPTR = 0;
	
	if(newInfoPTR == 0) return;

	newNodePTR = (NodeType *) malloc(sizeof(NodeType));

	newNodePTR -> dataPTR = newInfoPTR;

	newNodePTR -> next = 0;
	
		
  	if(ptr == 0) 
 	{
    		*headPTR = newNodePTR;
    		return;
  	}
	else
	{
		while(ptr -> next != 0)
		{
			ptr = ptr -> next;
		}
	}
  	
	ptr -> next = newNodePTR;
  	


}




int sendMenuAndWaitForResponse(int clntSocket)
{
    struct menu mainMenu;
    unsigned int response = 0;


    
    
    memset(&mainMenu, 0, sizeof(struct menu));   /* Zero out structure */
    strcpy(mainMenu.line1,"Hello! Welcome to your automated application to keep track of recent work projects.\n");
    strcpy(mainMenu.line2, "Would you like to sign up or sign in?\n");
    strcpy(mainMenu.line3, "If you would like to sign in, enter 1.\n");
    strcpy(mainMenu.line4, "If you would like to sign up, enter 2.\n");
    strcpy(mainMenu.line5, "If you would like to quit, enter q.\n");

    

    printf("Sending menu\n");
    put(clntSocket, &mainMenu, sizeof(struct menu));

    get(clntSocket, &response, sizeof(unsigned int));
    return ntohl(response);
}

int sendHomePage(int clntSocket)
{
	struct HOMEINFO homeMenu;
	unsigned int response = 0;

	memset(&homeMenu, 0, sizeof(struct HOMEINFO));
	strcpy(homeMenu.line1, "Welcome to your home.\n");
	strcpy(homeMenu.line2, "Press 1 to create a new entry.\n");
	strcpy(homeMenu.line3, "Press 2 to edit an entry.\n");
	strcpy(homeMenu.line4, "Press 3 to delete an entry.\n");
	strcpy(homeMenu.line5, "Press 4 to save an entry.\n");
	strcpy(homeMenu.line6, "Press 5 to display information.\n");

	printf("Taking client to home page...\n");
	put(clntSocket, &homeMenu, sizeof(struct HOMEINFO));

	get(clntSocket, &response, sizeof(unsigned int));
	
	return ntohl(response);

}

void sendEditInformation(int clntSocket)
{
	struct EDITINFO editing;

	PROJECTDATA pj;

	
	
	memset(&editing, 0, sizeof(struct EDITINFO));
	strcpy(editing.line1, "Enter new name of project on first line\n");
	strcpy(editing.line2, "Enter new description on second line\n");
        strcpy(editing.line3, "Enter new date created on third line\n");
	strcpy(editing.line4, "Enter new due date on fourth line\n");
 	strcpy(editing.line4, "Enter new amount of people on fifth line\n");

	put(clntSocket, &editing, sizeof(struct EDITINFO));
	
	get(clntSocket, &pj.nameOfProject, sizeof(pj.nameOfProject));	
	get(clntSocket, &pj.description, sizeof(pj.description));
	get(clntSocket, pj.data, sizeof(pj.data));
	get(clntSocket, &pj.dueData, sizeof(pj.dueData));
	
}



void askForName(int sock, char * name, unsigned int size)
{
    unsigned char msg[21];
    memset(msg, 0, sizeof(msg));
    strcpy(msg, "Enter e-mail:\n");
    put(sock, msg, sizeof(msg));
    memset(name, 0, NAME_SIZE);
    get(sock, name, NAME_SIZE);
}
void doSomethingWithName(char * name)
{
    printf("Received name from the client: %s\n", name);
}

void askForNumber(int sock, int * numPtr, unsigned int size)
{
    unsigned char msg[21];
    int numIn = 0;

    memset(msg, 0, sizeof(msg));
    strcpy(msg, "Enter number:\n");
    put(sock, msg, sizeof(msg));
    get(sock, &numIn, sizeof(int));
    *numPtr = ntohl(numIn);
}

void doSomethingWithNumber(int number)
{
    printf("Received number from the client: %d\n", number);
}


void askForFullName(int sock, char * fullName, unsigned int size)
{

	unsigned char msg[21];
	memset(msg, 0, sizeof(msg));
	strcpy(msg, "Enter full name:\n");
	put(sock, msg, sizeof(msg));
	memset(fullName, 0, 21);
	get(sock, fullName, 21);

}



void doSomethingWithFullName(char * fullName)
{
	printf("Receiverd full name from the client: %s\n", fullName);
}



	

void writeDataToFile(USERDATA * data, char fullName[])
{
	FILE * fileData = fopen("Information.txt", "a");

	if(fileData != NULL)
	{
		
		fprintf(fileData, "\n%s %d %s", data->name, data->number, fullName);
		//fwrite(data->number, 1, sizeof(data->number), fileData);
		
		fclose(fileData);
	}
	
	


}




int checkIfAlreadyUser(NodeType * head, char userChoice[])
{
	USERDATA * dataPtr;
	char newChoice[50];
	int result;

	while(head != 0)
	{
		dataPtr = head -> dataPTR;
		head = head -> next;

		if(strcmp(dataPtr->name, userChoice) == 0)
		{
			result = 1;
		}
	}

	return result;


}


void traverseUsers(NodeType * head)
{
	USERDATA * dataPtr;

	/*
	 * could do File I/O with this?
	 *
	 */

	while(head != 0)
	{
		dataPtr = head -> dataPTR;    
		printf("Username: %s\n", (dataPtr -> name));
		head = head -> next;
	}
}

/*void traverseProjects(NodeType * head)
{
	
	struct PROJECTDATA * projectDataPTR; 

	while(head != 0)
	{
		projectDataPTR = head -> projDataPTR;
		printf("Name of File: %s\n", projectDataPTR->nameOfProject);
		printf("Description: %s\n", projectDataPTR->description);
		printf("Data: %s\n", projectDataPTR->data);
		printf("Due data: %s\n", projectDataPTR->dueData);
		printf("Number of people on team: %d\n", projectDataPTR->numOfPeopleOnTeam);
		head = head->next;
	}
	
}*/

void editProjectList(NodeType * head, char userChoice[])
{

	PROJECTDATA * dataPtr;

	char newName[100];
	char newDesc[1000];
	char newData[8];
	char newDueData[8];
	int newNumberOfPeople;
	char newChoice[50];

	while(head != 0)
	{
		dataPtr = head -> dataPTR;
		head = head -> next;

		if(strcmp(dataPtr->nameOfProject, userChoice) == 0)
		{
			printf("Your choice has been found!!!\n");
			printf("Your searched for username: %s\n", dataPtr->nameOfProject);
			printf("Enter New name of project: \n");
			//scanf("%s", &newName);
			//strcpy(dataPtr->nameOfProject, newName);

			printf("Enter new description: \n");
			//scanf("%s", &newDesc);
			//strcpy(dataPtr->desc, newDesc);


			printf("Enter new date created: \n");
			//scanf("%s", &newData);
			//strcpy(dataPtr->data);

			printf("Enter new due data: \n");
			//scanf("%s", &newDueData);
			//strcpy(dataPtr->dueData);
	
			printf("Enter new number of people: \n");
			//scanf("%d", &newNumberOfPeople);
			//dataPtr->numOfPeopleOnTeam = newNumberOfPeople;

		}

		/*
		 * These extra if elses handle what happens when the head reaches
		 * a node that does not match our choice
		 */
		else if(strcmp(dataPtr->nameOfProject, userChoice) > 0)
		{

			printf("Username too short.\n");
		}

		else if(strcmp(dataPtr->nameOfProject, userChoice) < 0)
		{
			printf("Username too long.\n");
		}
		

		
	}
}


