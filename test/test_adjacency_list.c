#include "../adjacency_list.h"
#include "test.h"

#include <stdio.h>

int test_add_edge() {
  Graph* g = init_graph(5);
  for(int i=0;i<50;i++) {
    g = add_edge(g, i, i%16);
    _assert(is_edge(g, i, i%16));
  }
  destroy_graph(g);
  return 1;
}

int test_add_edge_extend_size() {
  Graph* g = init_graph(5);
  g = add_edge(g, 5, 5);
  _assert(is_edge(g, 5, 5));
  g = add_edge(g, 5, 6);
  _assert(is_edge(g, 5, 6));
  g = add_edge(g, 7, 6);
  _assert(is_edge(g, 7, 6));
  destroy_graph(g);
  return 1;
}

int test_remove_edge() {
  Graph* g = init_graph(5);
  g = add_edge(g, 1, 1);
  g = add_edge(g, 2, 2);
  g = add_edge(g, 3, 3);
  g = remove_edge(g, 2, 2); 
  _assert(!is_edge(g, 2, 2));
  
  destroy_graph(g);
  return 1;
}


int test_remove_all_and_search() {
  Graph* g = init_graph(5);
  g = add_edge(g, 1, 1);
  g = add_edge(g, 2, 2);
  g = remove_edge(g, 2, 2);
  g = remove_edge(g, 1, 1);
  _assert(!is_edge(g, 2, 2));
  _assert(!is_edge(g, 1, 1));
  
  destroy_graph(g);
  return 1;
}

int test_print_graph() {
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
  return 1;
}

int test_init_graph_malloc_fails_graph() {
  turn_malloc_off(0);
  Graph* g = init_graph(5);
  _assert(g == NULL);

  return 1;
}


int test_init_graph_malloc_fails_nodes() {
  turn_malloc_off(1);

  Graph* g = init_graph(5);
  _assert(g == NULL);
  return 1;
}

int test_init_graph_realloc_fails_edge() {
  turn_malloc_off(2);
  Graph* g = init_graph(1);
  g = add_edge(g, 2, 2);
  _assert(g == NULL);

  return 1;
}

int main() {
  test_init();
  
  _verify(test_add_edge);
  _verify(test_add_edge_extend_size);
  _verify(test_remove_edge);
  _verify(test_remove_all_and_search);
  _verify(test_print_graph);
  _verify(test_init_graph_malloc_fails_graph);
  _verify(test_init_graph_malloc_fails_nodes);
  _verify(test_init_graph_realloc_fails_edge);

  
  if(!test_finish()) {
    return 1;
  }
  return 0;
}
