// This is my first attempt before reading the book entry
// for https://dmoj.ca/problem/crci07p2
#include "stdio.h"
#include <stdlib.h>
typedef struct Node {
  int cost;
  struct Node *next;
} Node;

void traverse(Node *node, int jump, int cost, int *costs, size_t *size) {
  if (!node->next) {
    costs = realloc(costs, *size++);
    costs++;
    *costs = cost;
  } else {

  }
}

// The ending node will have a null pointer for next
int findLowestCost(Node *node) {
  int *costs = NULL;
  int jump = 1;
  int cost = 0;
  size_t cost_arr_sz = 0;
  traverse(node, jump, cost, costs, &cost_arr_sz);
  return min(costs);
}

int main(void) {}