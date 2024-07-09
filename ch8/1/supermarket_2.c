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

// min_heap functions have been defined separately
// normally, we'd have a generic binary heap, and pass through some sort of
// comparison function, but will be separated in this example
void min_heap_insert(heap_element heap[], int *num_heap, int receipt_index,
                     int cost) {
  int i;
  heap_element temp;
  (*num_heap)++;
  heap[*num_heap] = (heap_element){receipt_index, cost};
  i = *num_heap;
  while (i > 1 && heap[i].cost < heap[i / 2].cost) {
    temp = heap[i];
    heap[i] = heap[i / 2];
    heap[i / 2] = temp;
    i = i / 2;
  }
}

heap_element min_heap_extract(heap_element heap[], int *num_heap) {
  heap_element remove, temp;
  int i, child;
  remove = heap[1];
  heap[1] = heap[*num_heap];
  (*num_heap)--;
  i = 1;
  while (i * 2 <= *num_heap) {
    child = i * 2;
    if (child < *num_heap && heap[child + 1].cost < heap[child].cost)
      child++;
    if (heap[child].cost < heap[i].cost) {
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

int main(void) {
  static int used[MAX_RECEIPTS] = {0};
  static heap_element max_heap[MAX_RECEIPTS + 1];
  static heap_element min_heap[MAX_RECEIPTS + 1];
  int num_days, receipt_index_today;
  int receipt_index = 0;
  long long total_prizes = 0;
  int i, j, cost;
  int max_num_heap = 0, min_num_heap = 0;
  heap_element max_element, min_element;
  scanf("%d", &num_days);

  for (i = 0; i < num_days; i++) {
    scanf("%d", &receipt_index_today);
    for (j = 0; j < receipt_index_today; j++) {
      scanf("%d", &cost);
      max_heap_insert(max_heap, &max_num_heap, receipt_index, cost);
      min_heap_insert(min_heap, &min_num_heap, receipt_index, cost);
      receipt_index++;
    }

    // Receipt Extraction
    // Ideally, we'd remove the min and max receipts from both the min
    // and max heaps, however, we don't know where the max in the min heap is,
    // or where the min in the max heap is. So, we keep a used
    // array and mark whenever a receipt has been removed from either heap.
    // Here we check the min and max receipts. If they've been used already,
    // we'll extract another receipt from the heap until the receipt hasn't

    max_element = max_heap_extract(max_heap, &max_num_heap);
    while (used[max_element.receipt_index])
      max_element = max_heap_extract(max_heap, &max_num_heap);
    used[max_element.receipt_index] = 1;

    min_element = min_heap_extract(min_heap, &min_num_heap);
    while (used[min_element.receipt_index])
      min_element = min_heap_extract(min_heap, &min_num_heap);
    used[min_element.receipt_index] = 1;
    total_prizes += max_element.cost - min_element.cost;
  }
  printf("%lld\n", total_prizes);
  return 0;
}