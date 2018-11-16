#include "../adjacency_matrix.h"
#include "../helpers.h"
#include "../hungarian.h"

#include <stdio.h>
#include <stdlib.h>

int main() {

  unsigned long test_cases, graph_size, agent, task, index;
  unsigned long* input;
  Graph* g;
  
  if(!get_ul(1, &test_cases))
    return 1;

  for(unsigned long runs = 0; runs < test_cases; runs++) {
    if(!get_ul(1, &graph_size))
      return 1;
    g = initGraph(graph_size);

    input = malloc((graph_size * graph_size) * sizeof(unsigned long));
    if(!get_ul_array((graph_size * graph_size), input)) {
      destroyGraph(g);
      free(input);
      return 1;
    }
    for(agent = 0; agent < graph_size; agent++) {
      for(task = 0; task < graph_size; task++) {
	index = (agent * graph_size) + task;
	addEdgeValue(g, agent, task, input[index]);
      }
    }

    free(input);
    int* result = hungarian(g, MIN);
    if(result == NULL) {
      destroyGraph(g);
      return 1;
    }
    printf("%d\n", compute_sum(g, result));
    free(result);
    destroyGraph(g);
  }
  
  return 0;
}
