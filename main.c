#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

int main(int argc, char *argv[]) {
	Slist *head = NULL;

	if (argc < 2) {
		printf("No sufficient arguments\n");
		return FAILURE;
	}

	if (Validation(&head, argv) == FAILURE) {
		return FAILURE;
	}
	printf("Validation successfully done.\n");
	char word[50];
	HT arr[28];
	create_hashtable(head, arr, 28);
	int flag=0;
	// Flag to check if database update is done
	int update=0;
	// Menu loop for user interaction
	int choice;
	while (1) {
		// Display menu options
		printf("\nMenu:\n");
		//if(flag==0)
		//{
		printf("1. Create database\n");
		//}
		printf("2. Display database\n");
		printf("3. Search database\n");
		printf("4. Save database\n");
		if(update==0)
		{
			printf("5. Update database\n");
		}
		printf("6. Exit\n");
		printf("Enter your choice: ");
		scanf("%d", &choice); // Read user's choice

		switch (choice) {
			case 1: 
				// Create the database from the linked list
				if(flag==0)
				{
					if (create_database(head, arr) == SUCCESS) 
					{
						printf("Created database successfully:\n");
						flag=1;
					}
					else
					{
						printf("Failed to create database.\n");
					}


				}
				else
				{
					printf("Already Database was created");
				}
				break;
		     case 2:
				// Display the database
				printf("Displaying the Database:\n");
				display_hashtable(arr, head);
				break;

			case 3: 
				// Search within the database
				if (search_Database(arr,head) == FAILURE) { 
					printf("Word NOT Found\n");
				}
				break;
			case 4:
				// Save the database to a file
				if (save_database(arr, head) == SUCCESS) {
					printf("SaveDatabase successfully\n");
				} else {
					printf("SaveDatabase not successful\n");
				}
				break;

			case 5:
				// Update entries in the database
				if(flag==0)
				{
					char fname[50];
					printf("Enter the backup file name:");
					scanf( "%s",fname);
					char *str=strstr(fname,".txt");
					int len=strlen(str);
					if(len==4 &&update==0)
					{
						if (update_database(arr,fname) == SUCCESS) 
						{
							printf("Update database successfully:\n");
							RemoveDuplicate(arr,&head);
							update=1;
						} 
						else 
						{
							printf("Update database not successful:\n");
						}
					}
					else
					{
						printf("File name is not in .txt");
					}
				}
				else
				{
					printf("database created previously is done,can't update the database");
				}
				break;
			

			case 6:
				// Exit the program
				printf("Exiting the program.\n");
				exit(0);

			default:
				// Handle invalid choices
				printf("Invalid choice. Please try again.\n");
		}
	}


	return 0;
}



int insert_last(Slist **head, char *data)
{
	Slist *new = malloc(sizeof(Slist));
	if(new==NULL)
		return FAILURE;
	strcpy(new->data,data); 
	new->link = NULL;
	if(*head==NULL)
	{
		*head = new;
		return SUCCESS;
	}
	Slist *temp = *head;
	while(temp->link!=NULL)
	{
		temp = temp->link;
	}
	temp->link = new;
	return SUCCESS;
}
