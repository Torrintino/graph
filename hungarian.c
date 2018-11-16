#include "hungarian.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int x, y;
} Pair;

Graph* init(Graph* g, Graph** prime, Pair** sequence, int** row_cover, int** col_cover,
	    int** row_starred, int** col_starred, int mode);
void maxToMin(Graph* g);
Pair step_1(Graph* g, Graph* prime, int* row_cover, int* col_cover,
	    int* row_starred);
int step_2(Graph* prime, Pair* sequence, int* row_cover, int* col_cover,
	   int* row_starred, int* col_starred, Pair p);
void step_3(Graph* copy, int* row_cover, int* col_cover);
void finish(Graph* copy, Graph* prime, Pair* sequence,
	    int* row_cover, int* col_cover, int* col_starred);

/*** Compute the optimal assignment for n agents and n jobs.

  Params:
      Graph* g: An adjacency matrix representation of a graph of size n.
          All values must be non-negative. n must be at least 1.
  Returns: An array of integers with n elements. The value j in position i
      of the array means, that the job i is assigned to agent j.
      In case of an allocation error, the function will return a NULL pointer.

  This function will copy the given graph, because it needs to perform
  arithmetic operations on it, but shall not override its values, so that
  the caller can compute the optimal assignment sum with the original graph.

 ***/
int* hungarian(Graph* g, int mode) {
  if(g->size == 0)
    return NULL;

  if(mode != MIN && mode != MAX)
    return NULL;
  
  Graph* prime;
  int* row_cover;
  int* col_cover;
  int* row_starred;
  int* col_starred;
  int assignments = 0;
  Pair p;
  Pair* sequence;
  int i;

  Graph* copy = init(g, &prime, &sequence, &row_cover, &col_cover, &row_starred, &col_starred,
		     mode);
  if(copy == NULL)
    return NULL;
  
  for(i = 0; i < g->size; i++)
    assignments += col_cover[i];
  
  while(assignments != g->size) {
    p = step_1(copy, prime, row_cover, col_cover, row_starred);
    if(p.x == 0 && p.y == 0) {
      step_3(copy, row_cover, col_cover);
    } else {
      assignments = step_2(prime, sequence,
			   row_cover, col_cover,
			   row_starred, col_starred,
			   p);
    }
  }

  for(i = 0; i < g->size; i++)
    row_starred[i]--;
  finish(copy, prime, sequence, row_cover, col_cover, col_starred);
  return row_starred;
}

Graph* init(Graph* g, Graph** prime, Pair** sequence, int** row_cover, int** col_cover,
	    int** row_starred, int** col_starred, int mode) {
  
  // Allocation
  Graph* copy = copyGraph(g);
  if(copy == NULL) goto COPY_ERROR;

  *prime = initGraph(copy->size);
  if(*prime == NULL) goto PRIME_ERROR;

  *sequence = malloc(sizeof(Pair) * copy->size * copy->size);
  if(*sequence == NULL) goto SEQUENCE_ERROR;

  *row_cover = malloc(sizeof(int) * copy->size);
  if(*row_cover == NULL) goto ROW_COVER_ERROR;
  
  *col_cover = malloc(sizeof(int) * copy->size);
  if(*col_cover == NULL) goto COL_COVER_ERROR;

  *row_starred = malloc(sizeof(int) * copy->size);
  if(*row_starred == NULL) goto ROW_STARRED_ERROR;
  
  *col_starred = malloc(sizeof(int) * copy->size);
  if(*col_starred == NULL) goto COL_STARRED_ERROR;

  if(mode == MAX)
    maxToMin(copy);
  
  int min, i, j;
  // Initial Cover
  for(i=0; i<copy->size; i++) {
    (*row_cover)[i] = 0;
    (*col_cover)[i] = 0;
    (*row_starred)[i] = 0;
    (*col_starred)[i] = 0;

    // Subtract each row with its minimum
    min = copy->matrix[i][0];
    for(j=0; j<copy->size; j++) {
      if(copy->matrix[i][j] < min)
	min = copy->matrix[i][j];
    }
    
    for(j=0; j<copy->size; j++)
      copy->matrix[i][j] -= min;
  }

  // Subtract each column with its minimum
  for(j=0; j<copy->size; j++) {
    min = copy->matrix[0][j];
    for(i=0; i<copy->size; i++) {
      if(copy->matrix[i][j] < min)
	min = copy->matrix[i][j];
    }

    for(i=0; i<copy->size; i++) {
      copy->matrix[i][j] -= min;

      // Star zero
      if(copy->matrix[i][j] == 0 &&
	 (*row_starred)[i] == 0 &&
	 (*col_starred)[j] == 0) {
	(*row_starred)[i] = j + 1;
	(*col_starred)[j] = i + 1;
	(*col_cover)[j] = 1;
      }
    }
  }

  return copy;

 COL_STARRED_ERROR:
  free(*row_starred);
 ROW_STARRED_ERROR:
  free(*col_cover);
 COL_COVER_ERROR:
  free(*row_cover);
 ROW_COVER_ERROR:
  free(sequence);
 SEQUENCE_ERROR:
  destroyGraph(*prime);
 PRIME_ERROR:
  destroyGraph(copy);
 COPY_ERROR:
  return NULL;
}


void maxToMin(Graph* g) {
  int max = 0;
  for(int i=0; i<g->size; i++) {
    for(int j=0; j<g->size; j++) {
      if(g->matrix[i][j] > max)
	max = g->matrix[i][j];
    }
  }

  for(int i=0; i<g->size; i++) {
    for(int j=0; j<g->size; j++) {
      g->matrix[i][j] = max - g->matrix[i][j];
    }
  }
}


Pair step_1(Graph* g, Graph* prime, int* row_cover, int* col_cover,
	    int* row_starred) {
  Pair p;
  int i, j;

 DO:do {
    p.x = 0; // Row index
    p.y = 0; // Column index
    
    for(j=0; j<g->size; j++) { // Search for an uncovered zero
      if(col_cover[j])
	continue;
      
      for(i=0; i<g->size; i++) {
	
	if(g->matrix[i][j] == 0 && !row_cover[i]) { // We found an uncovered zero
	  
	  prime->matrix[i][j] = 1;
	  p.x = i;
	  p.y = j;
	  if(!row_starred[i]) {
	    return p;
	  } else {
	    row_cover[i] = 1;
	    col_cover[row_starred[i] - 1] = 0;
	    goto DO;
	  }
	}
      }
    }
  } while(!(p.x == 0 && p.y == 0)); // ri and ci are zero, if no further uncovered zero is found

  return p;
}


int step_2(Graph* prime, Pair* sequence, int* row_cover, int* col_cover,
	   int* row_starred, int* col_starred, Pair p) {
  int size = 1;
  int i, j;
  
  sequence[0] = p;
  while(col_starred[p.y]) {
    i = col_starred[p.y] - 1;
    sequence[size] = (Pair) { .x = i, .y = p.y };
    for(j = (p.y + 1) % prime->size;
	!(prime->matrix[i][j]);
	j = (j+1) % prime->size);
    sequence[size + 1] = (Pair) { .x = i, .y = j };
    p = sequence[size + 1];
    size += 2;
  }

  row_starred[sequence[0].x] = sequence[0].y + 1;
  col_starred[sequence[0].y] = sequence[0].x + 1;
  
  for(i = 1; i < size; i += 2) {
    row_starred[sequence[i+1].x] = sequence[i+1].y + 1;
    col_starred[sequence[i+1].y] = sequence[i+1].x + 1;
  }

  size = 0;
  for(i=0; i<prime->size; i++) {
    row_cover[i] = 0;
    if(col_starred[i]) {
      col_cover[i] = 1;
      size++;
    } else {
      col_cover[i] = 0;
    }
    
    for(j=0; j<prime->size; j++) {
      prime->matrix[i][j] = 0;
    }
  }
  
  return size;
}


void step_3(Graph* copy, int* row_cover, int* col_cover) {
  int i, j, h = 0;

  for(i=0; i<copy->size; i++) {
    if(row_cover[i])
      continue;
    
    for(j=0; j<copy->size; j++) {
      if(!col_cover[j]) {
	if(h == 0) {
	  h = copy->matrix[i][j];
	} else if (copy->matrix[i][j] < h) {
	  h = copy->matrix[i][j];
	}
      }
    }	
  }

  for(i=0; i<copy->size; i++) {
    for(j=0; j<copy->size; j++) {
      if(row_cover[i] && col_cover[j])
	copy->matrix[i][j] += h;
      if(!row_cover[i] && !col_cover[j])
	copy->matrix[i][j] -= h;
    }
  }
}


void finish(Graph* copy, Graph* prime, Pair* sequence,
	    int* row_cover, int* col_cover, int* col_starred) {
  destroyGraph(copy);
  destroyGraph(prime);
  free(sequence);
  free(row_cover);
  free(col_cover);
  free(col_starred);
}


void print_assignment(int* result, int size) {
  for(int i=0; i<size; i++)
    printf("%d -> %d\n", i, result[i]);
}

int compute_sum(Graph* g, int* result) {
  int sum = 0;
  for(int i=0; i<g->size; i++)
    sum += g->matrix[i][result[i]];
  return sum;
}
