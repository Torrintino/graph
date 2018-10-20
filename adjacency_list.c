#include "adjacency_list.h"

#include <stdio.h>
#include <stdlib.h>

Graph* init_graph(unsigned long size) {
  Graph* g = malloc(sizeof(Graph));
  if(g == NULL)
    return NULL;
  
  g->size = size;
  g->nodes = malloc(sizeof(LinkedList*) * size);
  if(g->nodes == NULL) {
    free(g);
    return NULL;
  }
  for(unsigned long i=0; i<g->size; i++)
    g->nodes[i] = ll_init();
  return g;
}

Graph* add_edge(Graph* g, unsigned long src, unsigned long dest) {
  if(src >= g->size || dest >= g->size) {
    unsigned long old_size = g->size;
    g->size = src > dest ? (src + 1) : (dest + 1);
    LinkedList** new = realloc(g->nodes, sizeof(LinkedList*) * g->size);
    if(new == NULL) {
      g->size = old_size;
      destroy_graph(g);
      return NULL;
    }
    g->nodes = new;

    for(int i=old_size; i<g->size; i++)
      g->nodes[i] = ll_init();
  }
  
  g->nodes[src] = ll_add(g->nodes[src], dest);
  if(g->nodes[src] == NULL) {
    for(int i=0; i<g->size; i++) {
      if(i != src)
	free(g->nodes[i]);
    }
    free(g->nodes);
    free(g);
    return NULL;
  }

  return g;
}

Graph* remove_edge(Graph* g, unsigned long src, unsigned long dest) {
  if(src >= g->size || dest >= g->size)
    return g;

  g->nodes[src] = ll_remove(g->nodes[src], dest);
  return g;
}

int is_edge(Graph* g, unsigned long src, unsigned long dest) {
  if(src >= g->size || dest >= g->size)
    return 0;
  return ll_search(g->nodes[src], dest);
}

void print_graph(Graph* g) {
  for(unsigned long i=0; i<g->size; i++) {
    printf("%lu", i);
    if(g->nodes[i] != NULL) {
      printf("-> ");
      ll_print(g->nodes[i]);
    }
    else {
      printf("\n");
    }
  }
}

void destroy_graph(Graph* g) {
  for(unsigned long i=0; i<g->size; i++) {
    ll_destroy(g->nodes[i]);
  }
  free(g->nodes);
  free(g);
}
