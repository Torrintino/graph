#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct LinkedList {
  unsigned long id;
  struct LinkedList* next;
} LinkedList;

LinkedList* ll_init();
LinkedList* ll_add(LinkedList* l, unsigned long id);
LinkedList* ll_remove(LinkedList* l, unsigned long id);
int ll_search(LinkedList* l, unsigned long id);
void ll_print(LinkedList* l);
void ll_destroy(LinkedList* l);


#endif
