#include "../helpers.h"
#include "../adjacency_list.h"

#include <stdio.h>

int main() {
  unsigned long test_cases, graph_size, edge_count, node1, node2;
  Graph* g;
  
  test_cases = get_ul(1, &test_cases);
  for(int i=0; i<test_cases; i++) {
    if(!get_ul(2, &graph_size, &edge_count))
      return 1;
    g = init_graph(graph_size);
    
    for(int j=0; j<edge_count; j++) {
      if(!get_ul(2, &node1, &node2)) {
	destroy_graph(g);
	return 1;
      }
	
      if(add_edge(g, node1, node2) == NULL ||
	 add_edge(g, node2, node1) == NULL) {
	fprintf(stderr, "Allocation error\n");
	return 1;
      }
    }
    print_graph(g);
    destroy_graph(g);
  }

  return 0;
}
