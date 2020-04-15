/**
 * CS 2110 - Spring 2020 - Timed Lab 4
 *
 * Do not modify this file!
 *
 * struct tl4.h
 */

#ifndef tl4_H
#define tl4_H

#include <stdlib.h>

// This is just to remove compiler warnings associated with unused variables.
// Delete calls to this as you implement functions.
#define UNUSED_PARAMETER(x) (void)(x)

/**************************
 ** Datatype definitions **
 **************************/

/*
 * The following structs define the list and nodes for use in tl4.c. DO NOT
 * MODIFY THESE STRUCT DEFINITIONS
 */

struct node {
  struct node *next;
  int id;
  char *data;
};

struct list {
  // Head pointer either points to a node with data or if the struct list is
  // empty NULL
  struct node *head;
};

/***************************************************
** Prototypes for struct list library functions.  **
**                                                **
** For more details on their functionality,       **
** check tl4.c.                                   **
***************************************************/

/* Copy List */
struct list *deep_copy(struct list *listToCopy);

/* Destroy List */
void destroy(struct list *listToDestroy);
#endif