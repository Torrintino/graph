#include "../adjacency_matrix.h"
#include "test.h"

#include <stdio.h>


int test_add_edges() {
  Graph* g = initGraph(4);
  addEdge(g, 0, 2);
  _assert(isEdge(g, 0, 2));
  
  addEdge(g, 1, 3);
  _assert(isEdge(g, 1, 3));
  
  addEdge(g, 2, 2);
  _assert(isEdge(g, 2, 2));
  
  _assert(g->size == 4);
  destroyGraph(g);
  return 1;
}

int test_add_edges_extend_range() {
  Graph* g = initGraph(4);
 
  g = addEdge(g, 5, 5);
  _assert(isEdge(g, 5, 5));
  _assert(g->size == 6);
  
  g = addEdge(g, 5, 6);
  _assert(isEdge(g, 5, 6));
  _assert(g->size == 7);
  
  g = addEdge(g, 7, 5);
  _assert(isEdge(g, 7, 5));
  _assert(g->size == 8);
  
  destroyGraph(g);
  return 1;
}

int test_print() {
  Graph* g = initGraph(3);
  addEdge(g, 0, 0);
  addEdge(g, 2, 1);
  addEdge(g, 1, 2);
  printf("Expected output:\n");
  printf("1 0 0\n0 0 1\n0 1 0\n\n");
  
  printf("Actual output:\n");
  printGraph(g);
  destroyGraph(g);
  return 1;
}

int test_init_malloc_fails_struct() {
  turn_malloc_off(0);
  _assert(initGraph(10) == NULL);
  return 1;
}

int test_init_malloc_fails_matrix() {
  turn_malloc_off(1);
  _assert(initGraph(10) == NULL);
  
  return 1;
}

int test_init_malloc_fails_row_0() {
  turn_malloc_off(2);
  _assert(initGraph(10) == NULL);
  
  return 1;
}

int test_init_malloc_fails_row_5() {
  turn_malloc_off(7);
  _assert(initGraph(10) == NULL);
  
  return 1;
}

int test_add_edge_malloc_fails_matrix() {
  turn_malloc_off(1);
  Graph* g = initGraph(0);
  _assert(addEdge(g, 0, 0) == NULL);
  
  return 1;
}

int test_add_edge_realloc_fails_matrix() {
  turn_malloc_off(3);
  Graph* g = initGraph(1);
  _assert(addEdge(g, 1, 1) == NULL);
  
  return 1;
}

int test_add_edge_realloc_fails_cols() {
  turn_malloc_off(4);
  Graph* g = initGraph(1);
  _assert(addEdge(g, 1, 1) == NULL);
  
  return 1;
}

int test_add_edge_malloc_fails_rows() {
  turn_malloc_off(5);
  Graph* g = initGraph(1);
  _assert(addEdge(g, 1, 1) == NULL);
  
  return 1;
}

int main() {
  test_init();
  
  _verify(test_add_edges);
  _verify(test_add_edges_extend_range);
  _verify(test_print);
  _verify(test_init_malloc_fails_struct);
  _verify(test_init_malloc_fails_matrix);
  _verify(test_init_malloc_fails_row_0);
  _verify(test_init_malloc_fails_row_5);
  _verify(test_add_edge_malloc_fails_matrix);
  _verify(test_add_edge_realloc_fails_matrix);
  _verify(test_add_edge_realloc_fails_cols);
  _verify(test_add_edge_malloc_fails_rows);

  
  if(!test_finish()) {
    return 1;
  }
  return 0;
}
