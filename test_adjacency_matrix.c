#include "adjacency_matrix.h"
#include "test.h"

#include <assert.h>
#include <stdio.h>


int test_add_edges() {
  printf("test_add_edges():\n");
  Graph* g = initGraph(4);
  addEdge(g, 0, 2);
  assert(isEdge(g, 0, 2));
  
  addEdge(g, 1, 3);
  assert(isEdge(g, 1, 3));
  
  addEdge(g, 2, 2);
  assert(isEdge(g, 2, 2));
  
  assert(g->size == 4);
  destroyGraph(g);
  printf("Passed\n\n");
  return 1;
}

int test_add_edges_extend_range() {
  printf("test_add_edges_extend_range():\n");
  Graph* g = initGraph(4);
 
  g = addEdge(g, 5, 5);
  assert(isEdge(g, 5, 5));
  assert(g->size == 6);
  
  g = addEdge(g, 5, 6);
  assert(isEdge(g, 5, 6));
  assert(g->size == 7);
  
  g = addEdge(g, 7, 5);
  assert(isEdge(g, 7, 5));
  assert(g->size == 8);
  
  destroyGraph(g);
  printf("Passed\n\n");
  return 1;
}

int test_print() {
  printf("test_print():\n");
  Graph* g = initGraph(3);
  addEdge(g, 0, 0);
  addEdge(g, 2, 1);
  addEdge(g, 1, 2);
  printf("Expected output:\n");
  printf("1 0 0\n0 0 1\n0 1 0\n\n");
  
  printf("Actual output:\n");
  printGraph(g);
  destroyGraph(g);
  printf("Passed\n\n");
  return 1;
}

int test_init_malloc_fails_struct() {
  printf("test_init_malloc_fails_struct():\n");
  MALLOC_CALLS = 0;
  assert(initGraph(10) == NULL);
  printf("Passed\n\n");
  MALLOC_CALLS = -1;
  return 1;
}

int test_init_malloc_fails_matrix() {
  printf("test_init_malloc_fails_matrix():\n");
  MALLOC_CALLS = 1;
  assert(initGraph(10) == NULL);
  printf("Passed\n\n");
  MALLOC_CALLS = -1;
  return 1;
}

int test_init_malloc_fails_row_0() {
  printf("test_init_malloc_fails_row_0():\n");
  MALLOC_CALLS = 2;
  assert(initGraph(10) == NULL);
  printf("Passed\n\n");
  MALLOC_CALLS = -1;
  return 1;
}

int test_init_malloc_fails_row_5() {
  printf("test_init_malloc_fails_row_5():\n");
  MALLOC_CALLS = 7;
  assert(initGraph(10) == NULL);
  printf("Passed\n\n");
  MALLOC_CALLS = -1;
  return 1;
}

int test_add_edge_malloc_fails_matrix() {
  printf("test_add_edge_malloc_fails_matrix():\n");
  MALLOC_CALLS = 1;
  Graph* g = initGraph(0);
  assert(addEdge(g, 0, 0) == NULL);
  printf("Passed\n\n");
  MALLOC_CALLS = -1;
  return 1;
}

int test_add_edge_realloc_fails_matrix() {
  printf("test_add_edge_malloc_fails_matrix():\n");
  MALLOC_CALLS = 3;
  Graph* g = initGraph(1);
  assert(addEdge(g, 1, 1) == NULL);
  printf("Passed\n\n");
  MALLOC_CALLS = -1;
  return 1;
}

int test_add_edge_realloc_fails_cols() {
  printf("test_add_edge_malloc_fails_matrix():\n");
  MALLOC_CALLS = 4;
  Graph* g = initGraph(1);
  assert(addEdge(g, 1, 1) == NULL);
  printf("Passed\n\n");
  MALLOC_CALLS = -1;
  return 1;
}

int test_add_edge_malloc_fails_rows() {
  printf("test_add_edge_malloc_fails_matrix():\n");
  MALLOC_CALLS = 5;
  Graph* g = initGraph(1);
  assert(addEdge(g, 1, 1) == NULL);
  printf("Passed\n\n");
  MALLOC_CALLS = -1;
  return 1;
}

int main() {
  MALLOC_CALLS = -1;
  int total_tests = 11;
  int passed_tests = 0;
  passed_tests += test_add_edges();
  passed_tests += test_add_edges_extend_range();
  passed_tests += test_print();
  passed_tests += test_init_malloc_fails_struct();
  passed_tests += test_init_malloc_fails_matrix();
  passed_tests += test_init_malloc_fails_row_0();
  passed_tests += test_init_malloc_fails_row_5();
  passed_tests += test_add_edge_malloc_fails_matrix();
  passed_tests += test_add_edge_realloc_fails_matrix();
  passed_tests += test_add_edge_realloc_fails_cols();
  passed_tests += test_add_edge_malloc_fails_rows();
  printf("Number of passed tests: %d/%d\n", passed_tests, total_tests);
}
