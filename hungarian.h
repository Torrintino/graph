#ifndef HUNGARIAN_H
#define HUNGARIAN_H

#include "adjacency_matrix.h"

#define MIN 0
#define MAX 1

// Pass either MIN or MAX for finding the assignment with minimum/maximum sum
int* hungarian(Graph* g, int mode);

void print_assignment(int* result, int size);

int compute_sum(Graph* g, int* result);

#endif
