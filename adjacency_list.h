#ifndef ADJACENCY_LIST_H
#define ADJACENCY_LIST_H

#define LINKED_LIST_UNIQUE
#include "linked_list.h"

typedef struct {
  LinkedList** nodes;
  unsigned long size;
} Graph;

Graph* init_graph(unsigned long size);

/*** If either src or dest is greater than the graph size,
     the graph size will be increased and the necessary memory
     will be allocated.
     If allocating space fails, NULL will be returned.
 ***/
Graph* add_edge(Graph* g, unsigned long src, unsigned long dest);

/*** If either src or dest is greater than the graph size,
     the function will return without doing anything.
 ***/
Graph* remove_edge(Graph* g, unsigned long src, unsigned long dest);
int is_edge(Graph* g, unsigned long src, unsigned long dest);
void print_graph(Graph* g);
void destroy_graph(Graph* g);

#endif
