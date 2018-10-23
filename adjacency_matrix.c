#include "adjacency_matrix.h"
#include "helpers.h"

#include <stdio.h>
#include <stdlib.h>


Graph* initGraph(unsigned int size) {
  Graph* g = malloc(sizeof(Graph));
  if(g == NULL)
    return NULL;
  g->size = size;
  
  if(size == 0) {
    g->matrix = NULL;
  } else {
    g->matrix = malloc(sizeof(int*) * size);
    if(g->matrix == NULL) {
      free(g);
      return NULL;
    }
    
    for(int i=0; i<size; i++) {
      g->matrix[i] = malloc(sizeof(int) * size);
      if(g->matrix[i] == NULL) {
	for(int j=i-1; j >= 0; j--)
	  free(g->matrix[j]);
        free(g->matrix);
	free(g);
	return NULL;
      }
      for(int j=0; j<g->size; j++)
	g->matrix[i][j] = 0;
    }
  }
  
  return g;
}

Graph* addEdgeValue(Graph* g, int src, int dest, int v) {
  if(src >= g->size || dest >= g->size) {
    int old_size = g->size;
    g->size = src > dest ? (src + 1) : (dest + 1);
    
    if(g->matrix == NULL) {
      g->matrix = malloc(g->size * sizeof(int*));
      if(g->matrix == NULL) {
	free(g);
	return NULL;
      }
    } else {
      int** new = realloc(g->matrix, g->size * sizeof(int*));
      if(new == NULL) {
	for(int i=0; i<old_size; i++)
	  free(g->matrix[i]);
	free(g->matrix);
	free(g);
	return NULL;
      }
      g->matrix = new;
    }
    
    // Add new cols to existing rows
    for(int i=0; i<old_size; i++) {
      int* new = realloc(g->matrix[i], g->size * sizeof(int*));
      if(new == NULL) {
	for(int j=old_size-1; j>=0; j--)
	  free(g->matrix[j]);
	free(g->matrix);
	free(g);
	return NULL;
      }
      g->matrix[i] = new;

      // Initialize new cols
      for(int j = old_size; j < g->size; j++)
	g->matrix[i][j] = 0;
    }

    // Create new rows
    for(int i=old_size; i<g->size; i++) {
      g->matrix[i] = malloc(g->size * sizeof(int*));
      if(g->matrix[i] == NULL) {
	for(int j=0; j<i; j++)
	  free(g->matrix[j]);
	free(g->matrix);
	free(g);
	return NULL;
      }
      
      for(int j=0; j<g->size; j++)
	g->matrix[i][j] = 0;
    }
  }

  g->matrix[src][dest] = v;
  return g;
}

Graph* addEdge(Graph* g, int src, int dest) {
  return addEdgeValue(g, src, dest, 1);
}

Graph* removeEdge(Graph* g, int src, int dest) {
  if(src < g->size && dest < g->size)
    g->matrix[src][dest] = 0;
  return g;
}

int isEdge(Graph* g, int src, int dest) {
  return g->matrix[src][dest];
}

void printGraph(Graph* g) {
  for(int i=0; i<g->size; i++) {
    for(int j=0; j<g->size; j++) {
      printf("%d ", g->matrix[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

void destroyGraph(Graph* g) {
  for(int i=0; i<g->size; i++)
    free(g->matrix[i]);
  free(g->matrix);
  free(g);
}
