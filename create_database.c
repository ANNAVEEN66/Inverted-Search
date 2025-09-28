#include "main.h"
#include<string.h>

void create_hashtable(Slist *head,HT * hash,int size)
{
    //creating the hashtable
    for(int i=0;i<size;i++)
    {
        //initializing key value and link value with index and NULL
        hash[i].key = i;
        hash[i].link = NULL;
    }
}
//create database function definition
int create_database(Slist *head, HT *hash)
{
    FILE *fptr;
    Slist *temp = head;
    //traversing through the linked list
    while (temp != NULL)
    {
        fptr = fopen(temp->data, "r");
        // File could not be opened
        if (fptr == NULL)
        {
            return FAILURE; 
        }

        char word1[20];
        int index;
        //reading the string from the file and checking that string is EOF or not
        while (fscanf(fptr, "%s", word1) != EOF)
        {
            //finding index of hashtable
            if(word1[0]>='a'&&word1[0]<='z')
            {
               index = word1[0] % 97;
            }
            else if(word1[0]>='A'&&word1[0]<='Z')
            {
               index = (word1[0]+32) % 97;
            }
            main_node *temp1 = hash[index].link;
            main_node *prev = NULL;
            int flag = 0;

            // Traverse main node list to find if word already exists
            while (temp1 != NULL)
            {
                if (strcmp(temp1->word, word1) == 0)
                {
                    // Word found
                    flag = 1;
                    break; 
                }
                prev = temp1;
                temp1 = temp1->main_nodelink;
            }

            if (flag)
            {
                // Word exists, check for file in sub-node list
                sub *temp2 = temp1->sub_node_link;
                sub *prev_sub = NULL;
                int flag2 = 0;

                while (temp2 != NULL)
                {
                    if (strcmp(temp2->f_name, temp->data) == 0)
                    {
                        // Increment word count for this file
                        temp2->word_count++; 
                        flag2 = 1;
                        break;
                    }
                    prev_sub = temp2;
                    temp2 = temp2->sub_nodelink;
                }

                if (!flag2)
                {
                    // File not found in sub-nodes, add a new sub-node
                    sub *new_subnode = malloc(sizeof(sub));
                    if (new_subnode == NULL)
                    {
                        // Memory allocation failed
                        fclose(fptr);
                        return FAILURE; 
                    }
                    strcpy(new_subnode->f_name, temp->data);
                    temp1->file_count++;
                    new_subnode->word_count= 1;
                    new_subnode->sub_nodelink = NULL;

                    // Attach new sub-node to the list
                    if (prev_sub != NULL)
                    {
                        prev_sub->sub_nodelink = new_subnode;
                    }
                    else
                    {
                        temp1->sub_node_link = new_subnode;
                    }
                }
            }
            else
            {
                // Word not found, create a new main node and sub-node
                main_node *new_mainnode = malloc(sizeof(main_node));
                sub *new_subnode = malloc(sizeof(sub));
                if (new_mainnode == NULL || new_subnode == NULL)
                {
                     // Memory allocation failed
                    fclose(fptr);
                    return FAILURE;
                }

                // Initialize the new main node
                strcpy(new_mainnode->word, word1);
                new_mainnode->file_count = 1;
                new_mainnode->main_nodelink = NULL;
                new_mainnode->sub_node_link = new_subnode;

                // Initialize the new sub-node
                strcpy(new_subnode->f_name, temp->data);
                new_subnode->word_count = 1;
                new_subnode->sub_nodelink = NULL;

                // Attach the new main node to the hash table
                if (hash[index].link == NULL)
                {
                    // First entry in this index
                    hash[index].link = new_mainnode; 
                }
                else
                {
                     // Append to existing list
                    prev->main_nodelink = new_mainnode;
                }
            }
        }
        
        fclose(fptr); // Close file after reading
        temp = temp->link; // Move to the next file in the list
    }

    return SUCCESS;
}


