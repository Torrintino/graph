#ifndef ADJACENCY_MATRIX_H
#define ADJACENCY_MATRIX_H

typedef struct Graph {
  int** matrix;
  unsigned int size;
} Graph;

Graph* initGraph(unsigned int size);
Graph* addEdge(Graph* g, int src, int dest);
Graph* removeEdge(Graph* g, int src, int dest);
int isEdge(Graph* g, int src, int dest);
void printGraph(Graph* g);
void destroyGraph(Graph* g);

#endif
