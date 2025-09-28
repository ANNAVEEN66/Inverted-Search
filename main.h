#ifndef MAIN_H
#define MAIN_H
#define SUCCESS 0
#define FAILURE -1
#include<stdio.h>
#include<stdlib.h>
typedef struct node
{
	struct node *link;
	char data[50];
	
}Slist;
typedef struct hash_table
{
	int key;
	struct main_node *link;
}HT;
typedef struct main_node
{
	int file_count;
	char word[50];
	struct main_node *main_nodelink;
	struct sub_node *sub_node_link;
}main_node;
typedef struct sub_node
{
	int word_count;
	char f_name[50];
	struct sub_node *sub_nodelink;
}sub;
typedef struct Node
{
	char file_name[50];
	struct node *link;
}node;
//sub *create_subnode(char *filename);
void create_hashtable(Slist *head,HT * hash,int size);
int create_database(Slist *head, HT *hash);
int display_hashtable(HT *hash,Slist *head);
int search_Database(HT * hash,Slist *head);
int save_database(HT *hash,Slist *head);
int update_database(HT *hash, char *fname);
void RemoveDuplicate(HT *hash, Slist **head);
int insert_last(Slist **head,char *data);
int Validation(Slist **head,char *argv[]);
void print_list(Slist *head);
//int insert_first(Dlist **head, Dlist **tail, int data);
/* Include the prototypes here */

#endif

