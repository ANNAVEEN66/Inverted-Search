#include "main.h"

int display_hashtable(HT *hash,Slist *head)
{
    int i;
    //creating the main node and subnode with NULL address
    sub * snode = NULL;
    main_node *main = NULL;
    printf("index\tword\tfile_count\tfile_name\tword_count\n\n");
    //run the loop upto hash table size times
    for(i=0;i<28;i++)
    {
        //check the hash table index link part is null or not
        if(hash[i].link!=NULL)
        {
            //update the main node with hash table index link part
            main = hash[i].link;
            //traverse through the main node
            while(main!=NULL)
            {
                //print the main node data part
                printf("[%d]\t%s\t  %d\t",i,main->word,main->file_count);
                //update the sub node part
                snode = main->sub_node_link; 
                //Traverse through the subnode
                while(snode!=NULL)
                {
                    //printing the subnode data
                    printf("\t%s\t\t  %d\t",snode->f_name,snode->word_count);
                    snode = snode->sub_nodelink;
                }
                main = main->main_nodelink;
                printf("\n");
            }
        }
    }
    return SUCCESS;
}
