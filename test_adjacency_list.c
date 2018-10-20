#include "adjacency_list.h"
#include "test.h"

#include <stdio.h>

int test_add_edge() {
  printf("test_add_edge():\n");
  Graph* g = init_graph(5);
  g = add_edge(g, 0, 0);
  if(!is_edge(g, 0, 0))
    return 0;
  
  g = add_edge(g, 4, 2);
  if(!is_edge(g, 4, 2))
    return 0;
  
  g = add_edge(g, 1, 3);
  if(!is_edge(g, 1,3))
    return 0;
  
  g = add_edge(g, 2, 3);
  if(!is_edge(g, 2, 3))
    return 0;
  
  g = add_edge(g, 1, 4);
  if(!is_edge(g, 1, 4))
    return 0;
  
  g = add_edge(g, 1, 1);
  if(!is_edge(g, 1, 1))
    return 0;
  
  destroy_graph(g);
  printf("Passed\n\n");
  return 1;
}

int test_add_edge_extend_size() {
  printf("test_add_edge_extend_size():\n");
  Graph* g = init_graph(5);
  g = add_edge(g, 5, 5);
  if(!is_edge(g, 5, 5))
    return 0;
  
  g = add_edge(g, 5, 6);
  if(!is_edge(g, 5, 6))
    return 0;
  
  g = add_edge(g, 7, 6);
  if(!is_edge(g, 7, 6))
    return 0;
  
  destroy_graph(g);
  printf("Passed\n\n");
  return 1;
}

int test_remove_edge() {
  printf("test_remove_edge():\n");
  Graph* g = init_graph(5);
  g = add_edge(g, 1, 1);
  g = add_edge(g, 2, 2);
  g = add_edge(g, 3, 3);
  g = remove_edge(g, 2, 2); 
  if(is_edge(g, 2, 2))
    return 0;
  
  destroy_graph(g);
  printf("Passed\n\n");
  return 1;
}


int test_remove_all_and_search() {
  printf("test_remove_all_and_search():\n");
  Graph* g = init_graph(5);
  g = add_edge(g, 1, 1);
  g = add_edge(g, 2, 2);
  g = remove_edge(g, 2, 2);
  g = remove_edge(g, 1, 1);
  if(is_edge(g, 2, 2))
    return 0;
  if(is_edge(g, 1, 1))
    return 0;
  
  destroy_graph(g);
  printf("Passed\n\n");
  return 1;
}

int test_print_graph() {
  printf("test_print_graph():\n");
  Graph* g = init_graph(5);
  g = add_edge(g, 1, 1);
  g = add_edge(g, 2, 3);
  g = add_edge(g, 3, 4);
  printf("Expected output:\n");
  printf("0\n1-> 1\n2-> 3\n3-> 4\n4\n\n");

  printf("Actual output:\n");
  print_graph(g);
  printf("\n");

  destroy_graph(g);
  printf("Passed\n\n");
  return 1;
}

int test_init_graph_malloc_fails_graph() {
  printf("test_print_graph():\n");
  MALLOC_CALLS = 0;
  Graph* g = init_graph(5);
  if(g != NULL)
    return 0;

  printf("Passed\n\n");
  MALLOC_CALLS = -1;
  return 1;
}


int test_init_graph_malloc_fails_nodes() {
  printf("test_print_graph():\n");
  MALLOC_CALLS = 1;
  Graph* g = init_graph(5);
  if(g != NULL)
    return 0;

  printf("Passed\n\n");
  MALLOC_CALLS = -1;
  return 1;
}

int test_init_graph_realloc_fails_edge() {
  printf("test_print_graph():\n");
  MALLOC_CALLS = 2;
  Graph* g = init_graph(1);
  g = add_edge(g, 2, 2);
  if(g != NULL)
    return 0;

  printf("Passed\n\n");
  MALLOC_CALLS = -1;
  return 1;
}

int main() {
  MALLOC_CALLS = -1;
  int passed_tests = 0, total_tests = 8;
  passed_tests += test_add_edge();
  passed_tests += test_add_edge_extend_size();
  passed_tests += test_remove_edge();
  passed_tests += test_remove_all_and_search();
  passed_tests += test_print_graph();
  passed_tests += test_init_graph_malloc_fails_graph();
  passed_tests += test_init_graph_malloc_fails_nodes();
  passed_tests += test_init_graph_realloc_fails_edge();

  printf("Passed tests: %d/%d\n\n", passed_tests, total_tests);
}
