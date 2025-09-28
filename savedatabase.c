#include "main.h"
#include<string.h>
int save_database(HT *hash,Slist *head)
{
   	char fname[20];
    printf("Enter the file name:");
   	scanf("%s",fname);
	char *extn = strstr(fname,".txt");
	//check the file name is valid or not
	if((extn!=NULL)&&(strlen(extn)==4))
	{
		//open the file in write mode
		FILE *fptr = fopen(fname,"w");
		int i;
		//run the loop upto hashtable size times
		for(i=0;i<28;i++)
		{
			//check the hash index link part is null or not
			if(hash[i].link!=NULL)
			{
				//creating the main node
				main_node *main = hash[i].link;
				//traverse through the main node
				while(main!=NULL)
				{
					//write the main node data to the file
					fprintf(fptr,"#[%d];%s;%d;",i,main->word,main->file_count);
					//creating the sub node
					sub *snode = main->sub_node_link; 
					//traverse through the sub node
					while(snode!=NULL)
					{
						//write the subnode data to the file
						fprintf(fptr,"%s;%d#",snode->f_name,snode->word_count);
						//update the subnode with subnode link
						snode = snode->sub_nodelink;
					}
					//update the mainnode with mainnode link
					main = main->main_nodelink;
					//write the new line character to the file
					fprintf(fptr,"\n");
				}
				//return FAILURE;
			}

		}
		//closing the file
		fclose(fptr);
	}
	//return SUCCESS;
	return SUCCESS;
}
