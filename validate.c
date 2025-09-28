#include<string.h>
#include<stdlib.h>
#include"main.h"

int Validation(Slist **head,char *argv[])
{
    
    int i=0;
    FILE *fptr;
    for(i=1;argv[i]!=NULL;i++)
    {
        char *extn = strstr(argv[i],".txt");
        if(extn==NULL||strlen(extn)>4)
        {
            printf("Error: Enter the command line arguments with .txt file extension %s\n",argv[i]);
            continue;
        }
        fptr=fopen(argv[i],"r");
        if(fptr==NULL)
        {
            printf("Error:This file is not present in the directory %s\n",argv[i]);
            continue;
        }
        int j;
        char ch=getc(fptr);
        if(ch==EOF)
        {
            printf("Error:contents are not available in this file %s\n",argv[i]);
            continue;
        }
        int flag=0;
        for(j=1;j<i;j++)
        {
            if(strcmp(argv[j],argv[i])==0)
            {
                printf("Duplicate File is present\n");
                flag=1;
                continue;
            }
        }
        if(!flag)
            insert_last(head,argv[j]);   
    }
    print_list(*head);
}
void print_list(Slist *head)
{
	if (head == NULL)
	{
		printf("INFO : List is empty\n");
	}
    else
    {
	    while (head)		
	    {
		    printf("%s -> ", head -> data);
		    head = head -> link;
	    }

	    printf("NULL\n");
    }
}

