/**
 * CS 2110 - Spring 2020 - Timed Lab #4
 *
 * @author Jade Law
 * 
 * tl4.c: Complete the functions!
 */

// Do not add ANY additional includes!!!
#include "tl4.h"

#include "string.h"

///* You should NOT have any global variables. */

/// HINT: C doesn't initialize values for you, so make sure you initialize all
/// variables yourself!

/** deep_copy
 *
 * Creates a new deep-copied list of the original list.
 *
 * If listToCopy is NULL return NULL. For any memory allocations
 * failures your code must not leak memory. This means that if any
 * memory allocation failures occur, before you return NULL, you must destroy
 * the list
 *
 * @param listToCopy A pointer to the struct list structure to make a copy of
 * @return The struct list structure created by copying the old one, or NULL on
 *         failure (includes any of the parameters being null)
 */
struct list *deep_copy(struct list *listToCopy) {
  if (listToCopy == NULL) {
    return NULL;
  }
  struct list *newList;
  struct node *newNode;
  newList = (struct list *)calloc(sizeof(struct list), 1);
  if (newList == NULL) {
    return NULL;
  }
  newNode = (struct node *)calloc(sizeof(struct node), 1);
  if (newNode == NULL) {
    free(newList);
    return NULL;
  }

  struct node *curr = (*listToCopy).head;
  if (curr == NULL) {
    (*newList).head = NULL;
    free(newNode);
    return newList;
  }
  (*newNode).id = (*curr).id;
  char *name;
  name = malloc(sizeof((*curr).data));
  if (name == NULL) {
    free(newList);
    free(newNode);
    return NULL;
  }
  strcpy(name, (*curr).data);
  (*newNode).data = name;
  (*newList).head = newNode;

  struct node *prevNode = newNode;
  curr = (*curr).next;

  while (curr != NULL) {
    struct node *new;
    new = (struct node *)calloc(sizeof(struct node), 1);
    if (new == NULL) {
      destroy(newList);
      return NULL;
    }
    char *n;
    n = (char *)malloc(sizeof((*curr).data));
    if (n == NULL) {
      destroy(newList);
      free(new);
      return NULL;
    }
    strcpy(n, (*curr).data);
    (*new).data = n;
    (*new).id = (*curr).id;
    (*prevNode).next = new;
    prevNode = new;
    curr = (*curr).next;
  }

  return newList;
}

/** Destroy
 *
 * Destroys the entire struct list. This function removes every list node
 * and finally remove the list itself.
 *
 * HINT: remember every malloc needs a respective free
 *
 * @param listToDestroy a pointer to the struct list
 */
void destroy(struct list *listToDestroy) {
  if (listToDestroy == NULL) {
    free(listToDestroy);
    return;
  }
  struct node *curr = (*listToDestroy).head;
  struct node *next;
  while (curr != NULL) {
    next = (*curr).next;
    if ((*curr).data != NULL) {
      free((*curr).data);
    }
    free(curr);
    curr = next;
  }
  free(listToDestroy);
}
