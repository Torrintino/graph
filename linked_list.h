#ifndef LINKED_LIST_H
#define LINKED_LIST_H

/*** Per default a linked list can contain two elements with the same ID.
     You can define LINKED_LIST_UNIQUE to ensure, that only elements will
     be added, that are not in the list already.
 ***/

typedef struct LinkedList {
  unsigned long id;
  struct LinkedList* next;
} LinkedList;

/*** An empty linked list will be represented by a NULL pointer 
     Therefore ll_init will return NULL;
***/
LinkedList* ll_init();

/*** Returns NULL, when an allocation fails.
     If that happens all all allocated memory will be free'd.
     Otherwise returns a pointer to the head of the list.
     The value of l will only change, if the list was empty before.
 ***/
LinkedList* ll_add(LinkedList* l, unsigned long id);

/*** Returns NULL, when the last element was removed.
     Otherwise returns a pointer to the head of the list.
     The value of l will only change, if the head was removed.
 ***/
LinkedList* ll_remove(LinkedList* l, unsigned long id);

/*** Returns 1 if the search was successfull, otherwise 0.
     The complexity is O(n).
 ***/
int ll_search(LinkedList* l, unsigned long id);

/*** Print the list in the format "0-> 1-> 2\n"
     For a list with three elements with the corresponding ID's.
 ***/
void ll_print(LinkedList* l);

/*** Always call this after the list is not needed anymore, to
     free up allocated space.
 ***/
void ll_destroy(LinkedList* l);

#endif
