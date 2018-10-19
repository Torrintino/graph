#include "../helpers.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  long id;
  struct Node* next;
} Node;

typedef struct {
  Node* nodes;
  unsigned long size;
} Graph;

Node* appendEdge(Node* n, unsigned long edge_id) {
  if(n->id == edge_id)
    return n;
  
  while(n->next != NULL) {
    if(n->id == edge_id)
      return n;
    n = n->next;
  }
    
  n->next = malloc(sizeof(Node));
  if(n->next == NULL) return NULL;

  n = n->next;
  n->id = edge_id;
  n->next = NULL;
  return n;
}

void printGraph(Graph g) {
  for(unsigned long i=0; i<g.size; i++) {
    Node* n = &g.nodes[i];
    printf("%lu", i);
    while(n->next != NULL) {
      n = n->next;
      printf("-> %lu", n->id);
    }
    printf("\n");
  }
}

void destroyNodeList(Node* n) {
  if(n->next == NULL) return;

  n = n->next; // First pointer was not malloced
  Node* next;
  while(n != NULL) {
    next = n->next;
    free(n);
    n = next;
  }
}

void destroyGraph(Graph g) {
  for(int j=0; j<g.size; j++) {
    destroyNodeList(&g.nodes[j]);
  }
  free(g.nodes);
}

int main() {
  unsigned long test_cases, edge_count, node_id, edge_id;
  Graph g;
  
  test_cases = get_ul(1, &test_cases);
  for(int i=0; i<test_cases; i++) {
    if(!get_ul(2, &g.size, &edge_count))
      return 1;
    g.nodes = malloc(g.size * sizeof(Node));
    if(g.nodes == NULL) {
      fprintf(stderr, "Allocation error\n");
      return 1;
    }
    
    for(int j=0; j<g.size; j++) {
      g.nodes[j].id = j;
      g.nodes[j].next = NULL;
    }

    for(int j=0; j<edge_count; j++) {
      if(!get_ul(2, &node_id, &edge_id)) {
	destroyGraph(g);
	return 1;
      }
	
      if(appendEdge(&g.nodes[node_id], edge_id) == NULL ||
	 appendEdge(&g.nodes[edge_id], node_id) == NULL) {
	destroyGraph(g);
	fprintf(stderr, "Allocation error\n");
	return 1;
      }
    }

    printGraph(g);
    destroyGraph(g);
  }

  return 0;
}
