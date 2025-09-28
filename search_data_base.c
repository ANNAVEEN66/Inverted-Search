#include "main.h"
#include<string.h>
int search_Database(HT * hash,Slist *head)
{
    char str[50]; 
    // Read the user input into str
    printf("Enter the word to be search: "); 
    scanf("%s",str);
    // Variablei,j declarations and initializing the index with 0
    int i,j,index=0; 
    // Calculate the hash index based on the first character
    index = str[0]%97;
    // store the hash index address in temp pointer variable 
    HT *temp = &hash[index]; 
    //creating the main node with link part of hash table index
    main_node *main = temp->link;
     // Traverse through the linked list 
    while(main!=NULL)
    {
        // Check if the current word matches the search string
        if(strcmp(main->word,str)==0) 
        {
            //create and linking the sub node
            sub *snode = main->sub_node_link; 
            // Traverse through the sub-nodes
            while(snode!=NULL) 
            {
                // Print the word count and file name for each occurrence
                printf("%s found %d times in %s file.\n",main->word,snode->word_count,snode->f_name);
                snode = snode->sub_nodelink;
            }
            // Return success if the word is found
            return SUCCESS; 
        }
        // Move to the next main node
        main = main->main_nodelink; 
    }
    // Return failure if the word is not found
    return FAILURE; 
}

