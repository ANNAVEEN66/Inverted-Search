#include "main.h"
#include <string.h>
int update_database(HT *hash, char *fname) 
{
    //create a file pointer for fname in read mode
    FILE *fptr = fopen(fname, "r");
    //check the file pointer contain null or not
    if (fptr == NULL) 
    {
        //if NULL file pointer doesnt created for file fname
        printf("unable to open the file!please try again\n");
        return FAILURE;
    }
    //create a char variable for storing first character of the pointer
    char ch = getc(fptr);
    //check char ch=='#' or not
    if (ch != '#') 
    {
        printf("Enter the valid file name\n");
        fclose(fptr);
        return FAILURE;
    }

    char str[100];
    while (fscanf(fptr, "%s", str) != EOF) {
        // Use strtok to to get filename,filecount,word
        char *temp = strtok(str, "#;");
         // Extract index from the brackets
        int index = atoi(temp + 1); 
        //check for index out of bound or not
        if (index < 0 || index >= 27) 
        { 
            printf("The hash table index is from 0 to 27 only");
            fclose(fptr);
            return FAILURE;
        }
       //create a pointer to traverse through hash link
        main_node *main = hash[index].link;
        //create a new main node 
        main_node *new = malloc(sizeof(main_node));
        //if new_main==NULL
        if (new == NULL) 
        {
            printf("Memory allocation failed\n");
            fclose(fptr);
            return FAILURE;
        }
        temp = strtok(NULL, ";");
        strcpy(new->word, temp);
        temp = strtok(NULL, ";");
        new->file_count = atoi(temp);
        new->sub_node_link = NULL;
        new->main_nodelink = NULL;

        // create a pointer last_sub intially NULL ,to traverse through subnodes
        sub *last_sub = NULL;
        for (int i = 0; i < new->file_count; i++) 
        {
            sub *new_sub = malloc(sizeof(sub));
            if (new_sub == NULL) 
            {
                printf("Memory allocation failed for subnodes \n");
                free(new);
                fclose(fptr);
                return FAILURE;
            }
            temp = strtok(NULL, ";#");
            strcpy(new_sub->f_name, temp);
            temp = strtok(NULL, ";#");
            new_sub->word_count = atoi(temp);
            new_sub->sub_nodelink = NULL;
            // Link the subnodes
            if (last_sub == NULL) 
            {
                new->sub_node_link = new_sub;
            } 
            else 
            {
                last_sub->sub_nodelink = new_sub;
            }
            last_sub = new_sub;
        }

        // Link the main nodes
        if (main == NULL) 
        {
            hash[index].link = new;
        } 
        else 
        {
            while (main->main_nodelink != NULL) 
            {
                main = main->main_nodelink;
            }
            main->main_nodelink = new;
        }
    }

    fclose(fptr);
    return SUCCESS;
}
void RemoveDuplicate(HT *hash, Slist **head) 
{
    //Iterate through each index in hash table
    for (int i = 0; i < 27; i++) 
    { 
        main_node *current_main = hash[i].link;

        while (current_main != NULL) 
        {
            //for each mainnode iterate through all subnodes
            sub *current_sub = current_main->sub_node_link;
            
            //create temporary pointer to hold the address of the head
            Slist *temp_list = *head;
            Slist *prev = NULL;

           //iterate through linked list 
            while (temp_list != NULL) 
            {
                //initially found=0 for track the file name is present in hash table
                int found = 0;
                // Reset current_sub for each file in the linked list
                current_sub = current_main->sub_node_link; 

                while (current_sub != NULL) 
                {
                  if (strcmp(temp_list->data, current_sub->f_name) == 0) 
                    {
                        found = 1; 
                        break; 
                    }
                    // Move to the next sub_node
                    current_sub = current_sub->sub_nodelink; 
                }

                if (found) 
                {
                    // Remove temp_list from the linked list
                    if (prev == NULL) 
                    {
                        //update the linked list
                        *head = temp_list->link; 
                    } 
                    else
                    {
                        prev->link = temp_list->link; 
                    }
                    Slist *to_delete = temp_list; 
                    temp_list = temp_list->link; 
                    // Free memory of the removed node
                    free(to_delete); 
                }
                else 
                {
                    // Move to the next node
                    prev = temp_list; 
                    // Move to the next node
                    temp_list = temp_list->link; 
                }
            }
            // Move to the next main_node
            current_main = current_main->main_nodelink; 
        }
    }
    print_list(*head);
}
