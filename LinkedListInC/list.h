/**
 * CS 2110 - Spring 2020 - Homework #9
 *
 * Do not modify this file!
 *
 * struct list.h
 */

#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <string.h>

// This is just to remove compiler warnings associated with unused variables.
// Delete calls to this as you implement functions.
#define UNUSED_PARAMETER(x) (void)(x)

/**************************
 ** Datatype definitions **
 **************************/

/*
 * The following structs define the LinkedList and Node for use in list.c. DO NOT MODIFY THESE STRUCT DEFINITIONS
 */

typedef struct node
{
    struct node *next;  //pointer to the next node
    char *data;         //pointer to the node's string data
} Node;


typedef struct linked_list
{
    Node *head; // Head pointer either points to a node with data or if the struct list is empty NULL
    int size;   // Size of the struct list
} LinkedList;

/***************************************************
** Prototypes for struct list library functions.  **
**                                                **
** For more details on their functionality,       **
** check struct list.c.                           **
***************************************************/

/* Creating */
LinkedList *create_list(void);

/* Adding */
int push_front(LinkedList *, char *);
int push_back(LinkedList *, char *);
int add_at_index(LinkedList *, char *, int index);

/* Querying */
int get(LinkedList *, int, char **);
int contains(LinkedList *, char *, char **);

int my_strncmp(const char *s1, const char *s2, unsigned long n);
char *my_strncpy(char *dest, const char *src, size_t n);

/* Removing */
int pop_front(struct linked_list *, char **);
int pop_back(struct linked_list *, char **);
int remove_at_index(LinkedList *, char **, int index);
void empty_list(LinkedList *);

/* Mutating */
int merge_nodes(LinkedList *, int index);


#endif
