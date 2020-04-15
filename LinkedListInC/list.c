/**
 * CS 2110 - Spring 2020 - Homework #9
 *
 * @author JADE LAW
 *
 * list.c: Complete the functions!
 */

/**
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!-IMPORTANT-!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * For any function that must use malloc, if malloc returns NULL, the function
 * itself should return NULL if needs to return something (or return 1 if
 * the function returns a int).
 */

// Do not add ANY additional includes!!!
#include "list.h"

/* You should NOT have any global variables. */

int my_strncmp(const char *s1, const char *s2, unsigned long n);
char *my_strncpy(char *dest, const char *src, size_t n);
unsigned int my_strlen(const char *s);

/* The create_node function is static because this is the only file that should
   have knowledge about the nodes backing the linked List. */
static inline Node *create_node(char *data);

/** create_node
  *
  * Helper function that creates a Node by allocating memory for it on the heap.
  * Be sure to set its next pointer to NULL.
  *
  * If malloc returns NULL, you should return NULL to indicate failure.
  *
  * @param data a void pointer to data the user wants to store in List
  * @return a Node
  */
static Node* create_node(char *data)
{
    Node *n;
    n = (Node *)malloc(sizeof(Node));
    if (n == NULL) {
      return NULL;
    }
    (*n).data = data;
    (*n).next = NULL;
    return n;
}

/** create_list
  *
  * Creates a struct linked_list by allocating memory for it on the heap.
  * Be sure to initialize size to zero and head and tail to NULL.
  *
  * If malloc returns NULL, you should return NULL to indicate failure.
  *
  * @return a pointer to a new struct list or NULL on failure
  */
LinkedList *create_list(void)
{
    LinkedList *l;
    l = (LinkedList *)malloc(sizeof(LinkedList));
    if (l == NULL) {
      return NULL;
    }
    (*l).head = NULL;
    (*l).size = 0;
    return l;
}

/** push_front
  *
  * Adds the element at the front of the struct linked_list.
  *
  * @param list a pointer to the struct linked_list structure.
  * @param data the data to add to the struct linked_list.
  * @return  1 if the struct linked_list is NULL, 0 if successful,
  */
int push_front(LinkedList *list, char *data)
{
    Node *node = create_node(data);
    if (node == NULL) {
      free(node);
      return 1;
    }
    if (list == NULL) {
      free(node);
      return 1;
    }
    Node *oldHead = (*list).head;
    (*list).head = node;
    (*node).next = oldHead;
    (*list).size++;
    return 0;
}

/** push_back
  *
  * Adds the element to the back of the LinkedList.
  *
  * @param list a pointer to the LinkedList structure.
  * @param data the data to add to the LinkedList.
  * @return 1 if the LinkedList is NULL, 0 if successful.
  */
int push_back(LinkedList *list, char *data)
{
    Node *node = create_node(data);
    if (node == NULL || list == NULL) {
      free(node);
      return 1;
    }
    if ((*list).size == 0) {
      free(node);
      return push_front(list, data);
    }
    Node* curr = (*list).head;
    while ((*curr).next != NULL) {
      curr = (*curr).next;
    }
    (*curr).next = node;
    (*list).size++;
    return 0;
}

/** add_at_index
  *
  * Add the element at the specified index in the LinkedList. This index must lie in
  * the inclusive range [0,size].
  * For example, if you have no elements in the LinkedList,
  * you should be able to add to index 0 but no further.
  * If you have two elements in the LinkedList,
  * you should be able to add to index 2 but no further.
  *
  * @param list a pointer to the LinkedList structure
  * @param index 0-based, starting from the head in the inclusive range
  *              [0,size]
  * @param data the data to add to the LinkedList
  * @return 1 if the index is out of bounds or the LinkedList is NULL
  *         (do not add the data in this case)
  *         otherwise (on success) return 0
  */
int add_at_index(LinkedList *list, char *data, int index)
{
    Node *node = create_node(data);
    if (node == NULL || list == NULL) {
      free(node);
      return 1;
    }
    if (index > (*list).size || index < 0) {
      free(node);
      return 1;
    }
    if (index == 0 || (*list).size == 0) {
      free(node);
      return push_front(list, data);
    } else if (index == (*list).size) {
      free(node);
      return push_back(list, data);
    }
    Node *curr = (*list).head;
    int i = 0;
    while (i + 1 < index) {
      curr = (*curr).next;
      i++;
    }
    (*node).next = (*curr).next;
    (*curr).next = node;
    (*list).size++;
    return 0;
}

/** get
  *
  * Gets the data at the specified index in the LinkedList
  *
  * @param list a pointer to the LinkedList structure
  * @param index 0-based, starting from the head.
  * @param dataOut A pointer to a pointer used to return the data from the
  *        specified index in the LinkedList or NULL on failure.
  * @return 1 if dataOut is NULL or index is out of range of the LinkedList or
  *         the LinkedList is NULL, 0 (on success) otherwise
  */
int get(LinkedList *list, int index, char **dataOut)
{
    if (list == NULL) {
      return 1;
    }
    if (index < 0 || index >= (*list).size) {
      return 1;
    }
    int i = 0;
    Node *curr = (*list).head;
    while (i < index) {
      i++;
      curr = (*curr).next;
    }
    if (dataOut == NULL) {
      return 1;
    }
    *dataOut = (*curr).data;
    return 0;
}

/** contains
  *
  * Traverses the LinkedList, trying to see if the LinkedList contains some
  * data. We say the list contains the data if the data string of the node 
  * matches the node passed in.
  *
  * You may use the string library functions to complete this comparison
  * (see what is included in list.h)
  * 
  * If there are multiple pieces of data in the LinkedList which are equal to
  * the "data" parameter, return the one at the lowest index.
  *
  *
  * @param list a pointer to the LinkedList structure
  * @param data The data, to see if it exists in the LinkedList
  * @param dataOut A pointer to a pointer used to return the data contained in
  *                the LinkedList or NULL on failure
  * @return int    0 if dataOut is NULL, the list is NULL, or the list
  *                does not contain data, else 1
  */
int contains(LinkedList *list, char *data, char **dataOut)
{
    if (list == NULL || (*list).size == 0) {
      *dataOut = NULL;
      return 0;
    }
    if (dataOut == NULL) {
      return 0;
    }
    int i = 0;
    Node *curr = (*list).head;
    while (i < (*list).size) {
      if (*((*curr).data) == *data) {
        char currData[sizeof(data)];
        my_strncpy(currData, (*curr).data, sizeof(data));
        currData[sizeof(data)] = '\0';
        int comp = my_strncmp(currData, data, sizeof(data));
        if (comp == 0) {
          *dataOut = ((*curr).data);
          return 1;
        }
      }
      curr = (*curr).next;
      i++;
    }
    *dataOut = NULL;
    return 0;
}

/** pop_front
  *
  * Removes the List_node at the front of the LinkedList, and returns its data to the user.
  *
  * @param list a pointer to the LinkedList.
  * @param dataOut A pointer to a pointer used to return the data in the first
  *                List_node or NULL if the LinkedList is NULL or empty
  * @return 1 if dataOut is NULL (the LinkedList is NULL or empty), else (on success) 0
  */
int pop_front(LinkedList *list, char **dataOut)
{
    if (list == NULL || (*list).size == 0) {
      dataOut = NULL;
      return 1;
    }
    Node *oldHead = (*list).head;
    (*list).head = (*((*list).head)).next;
    (*list).size--;
    if (dataOut == NULL) {
      return 1;
    }
    *dataOut = (*oldHead).data;
    free(oldHead);
    return 0;
}

/** pop_back
  *
  * Removes the ListNode at the back of the LinkedList, and returns its data to the user
  *
  * @param list a pointer to the LinkedList.
  * @param dataOut A pointer to a pointer used to return the data in the last
  *                ListNode or NULL if the LinkedList is NULL or empty
  * @return 1 if dataOut is NULL (the LinkedList is NULL or empty), else (on success) 0
  */
int pop_back(LinkedList *list, char **dataOut)
{
    if (list == NULL || (*list).size == 0) {
      dataOut = NULL;
      return 1;
    }
    if ((*list).size == 1) {
      return pop_front(list, dataOut);
    }
    Node *curr = (*list).head;
    Node *next = (*curr).next;
    while ((*next).next != NULL) {
      curr = next;
      next = (*next).next;
    }
    if (dataOut == NULL) {
      return 1;
    }
    *dataOut = (*next).data;
    (*curr).next = NULL;
    (*list).size--;
    free(next);
    return 0;
}


/** remove_at_index
  *
  * Remove the element at the specified index in the LinkedList.
  *
  * @param list a pointer to the LinkedList structure
  * @param index 0-based, starting from the head in the inclusive range
  *              [0,size]
  * @param data the data to remove from the LinkedList
  * @return 1 if the index is out of bounds, the LinkedList is NULL or
  *         the dataOut is NULL
  *         otherwise return 0
  */
int remove_at_index(LinkedList * list, char **dataOut, int index) 
{
    if (list == NULL || (*list).size == 0 || index < 0 || index >= (*list).size) {
      dataOut = NULL;
      return 1;
    }
    if (dataOut == NULL) {
      return 1;
    }
    if ((*list).size == 1 || index == (*list).size - 1) {
      return pop_back(list, dataOut);
    } else if (index == 0) {
      return pop_front(list, dataOut);
    }
    Node *prev = (*list).head;
    Node *removed = (*prev).next;
    int i = 1;
    while (i < index) {
      prev = removed;
      removed = (*removed).next;
      i++;
    }
    char *rem;
    rem = malloc(my_strlen((*removed).data) + 1);
    my_strncpy(rem, (*removed).data, my_strlen((*removed).data));
    rem[my_strlen((*removed).data)] = '\0';
    *dataOut = rem;
    //*dataOut = (*removed).data;
    (*prev).next = (*removed).next;
    (*list).size--;
    free((*removed).data);
    free(removed);
    return 0;
}

/** empty_list
  *
  * Empties the LinkedList. After this is called, the LinkedList should be
  * empty. This does not free the LinkedList struct itself, just all nodes and
  * data within. Make sure to check that listToEmpty is not NULL before
  * using it.
  *
  * You may call free on a char pointer as well as a node struct pointer.
  *
  * @param list a pointer to the LinkedList structure
  */
void empty_list(LinkedList *list)
{
    if (list == NULL) {
      return;
    }
    Node *curr = (*list).head;
    Node *next;
    while (curr != NULL) {
      next = (*curr).next;
      free((*curr).data);
      free(curr);
      curr = next;
    }
    (*list).head = NULL;
    (*list).size = 0;
}


/** merge_nodes
  *
  *
  * Concatenate the string data in two adjacent nodes (at index and index + 1), 
  * then remove the extra un-merged node. 
  *
  *     LinkedList *A: "CS" -> "2110" -> "Rocks" -> "!" -> NULL
  *
  *     merge_nodes(A, 0): "CS2110" -> "Rocks" -> "!" -> NULL
  *
  * @param list  LinkedList to operate on
  * @param index  Index of the first node to merge
  * @return 1 if the index is out of bounds, or the LinkedList is NULL
  *         otherwise return 0
  */
int merge_nodes(LinkedList *list, int index)
{
    if (list == NULL || index < 0 || index >= (*list).size - 1) {
      return 1;
    }
    Node *curr = (*list).head;
    int i = 0;
    while (i < index) {
      curr = (*curr).next;
      i++;
    }
    Node *next = (*curr).next;
    unsigned int totalLen = my_strlen((*curr).data) + my_strlen((*next).data);
    (*curr).data = realloc((*curr).data, totalLen + 1);
    my_strncpy(((*curr).data + my_strlen((*curr).data)), (*next).data, my_strlen((*next).data));
    (*curr).data[totalLen] = '\0';
    Node *removed = next;
    next = (*next).next;
    (*curr).next = next;
    (*list).size--;
    free((*removed).data);
    free(removed);
    return 0;
}

unsigned int my_strlen(const char *s)
{
    unsigned int count = 0;
    int i = 0;
    while (*(s + i) != '\0') {
        count = count + 1;
        i = i + 1;
    }
    return count;
}

int my_strncmp(const char *s1, const char *s2, unsigned long n)
{
    unsigned long i = 0;
    while (i <= n) {
        if (*(s1 + i) - *(s2 + i) == 0) {
            i = i + 1;
        } else {
            if (*(s1 + i) - *(s2 + i) > 0) {
                return 1;
            }
            return -1;
        }
    }
    return 0;
}

char *my_strncpy(char *dest, const char *src, size_t n)
{
    size_t i = 0;
    while ((i < n) && (*(src + i) != '\0')) {
        *(dest + i) = *(src + i);
        i++;
    }
    while (i < n) {
        *(dest + i) = '\0';
        i++;
    }
    return dest;
}
