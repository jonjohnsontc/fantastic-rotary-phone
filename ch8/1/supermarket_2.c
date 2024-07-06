/*
  Max-Heap (as array) solve for supermarket promotion
*/
#include <stdio.h>
#define MAX_RECEIPTS 1000000
#define MAX_COST 1000000

typedef struct heap_element {
  int receipt_index;
  int cost;
} heap_element;

void max_heap_insert(heap_element heap[], int *num_heap, int receipt_index,
                     int cost) {
  int i;
  heap_element temp;
  (*num_heap)++;
  heap[*num_heap] = (heap_element){receipt_index, cost};
  i = *num_heap;
  while (i > 1 && heap[i].cost > heap[i / 2].cost) {
    temp = heap[i];
    heap[i] = heap[i / 2];
    heap[i / 2] = temp;
    i = i / 2;
  }
}

heap_element max_heap_extract(heap_element heap[], int *num_heap) {
  heap_element remove, temp;
  int i, child;
  remove = heap[1];
  heap[1] = heap[*num_heap];
  (*num_heap)--;
  i = 1;
  while (i * 2 <= *num_heap) {
    child = i * 2;
    if (child < *num_heap && heap[child + 1].cost > heap[child].cost) {
      temp = heap[i];
      heap[i] = heap[child];
      heap[child] = temp;
      i = child;
    } else {
      break;
    }
  }
  return remove;
}