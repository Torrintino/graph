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

Graph* addEdge(Graph* g, int src, int dest) {
  if(src >= g->size || dest >= g->size) {
    int old_size = g->size;
    g->size = src > dest ? (src + 1) : (dest + 1);

    int* matrix_copy = g->matrix[0];
    g->matrix = realloc(g->matrix, g->size * sizeof(int*));
    if(g->matrix == NULL) {
      for(int i=0; i<old_size; i++) {
	free(matrix_copy);
	matrix_copy++;
      }
      free(g);
      return NULL;
    }

    // Add new cols to existing rows
    for(int i=0; i<old_size; i++) {
      g->matrix[i] = realloc(g->matrix[i], g->size * sizeof(int*));
      if(g->matrix[i] == NULL) {
	for(int j=old_size-1; j>=0; j--)
	  free(g->matrix[j]);
	free(g->matrix);
	free(g);
	return NULL;
      }

      // Initialize new cols
      for(int j = old_size; j < g->size; j++)
	g->matrix[i][j] = 0;
    }

    // Create new rows
    for(int i=old_size; i<g->size; i++) {
      g->matrix[i] = malloc(g->size * sizeof(int*));
      if(g->matrix[i] == NULL) {
	for(int j=g->size-1; j>=old_size; j--)
	  free(g->matrix[j]);
	free(g->matrix);
	free(g);
	return NULL;
      }
      
      for(int j=0; j<g->size; j++)
	g->matrix[i][j] = 0;
    }
  }

  g->matrix[src][dest] = 1;
  return g;
}

Graph* removeEdge(Graph* g, int src, int dest) {
  if(src < g->size && dest < g->size)
    g->matrix[src][dest] = 0;
  return g;
}

int isEdge(Graph* g, int src, int dest) {
  return g->matrix[src][dest] == 1;
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
