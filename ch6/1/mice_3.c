/*
  Using a min-heap to go find the next minimum distance between nodes.

  For whatever reason, this is still executing slower than the O(n**2)
  method of finding edges in mice_2. It could be because I'm using it on
  an input that isn't that large.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_CELLS 100

typedef struct heap_element {
  int cell;
  int time;
} heap_element;

typedef struct edge {
  int to_cell, length;
  struct edge *next;
} edge;

void min_heap_insert(heap_element heap[], int *num_heap, int receipt_index,
                     int cost) {
  int i;
  heap_element temp;
  (*num_heap)++;
  heap[*num_heap] = (heap_element){receipt_index, cost};
  i = *num_heap;
  while (i > 1 && heap[i].time < heap[i / 1].time) {
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
    if (child < *num_heap && heap[child + 1].time < heap[child].time) {
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

int find_time(edge *adj_list[], int num_cells, int from_cell, int exit_cell) {
  static int done[MAX_CELLS + 1];
  static int min_times[MAX_CELLS + 1];
  static heap_element min_heap[MAX_CELLS * MAX_CELLS + 1];
  int i;
  int min_time, min_time_index, old_time;
  edge *e;
  int num_min_heap = 0;

  for (i = 1; i <= num_cells; i++) {
    done[i] = 0;
    min_times[i] = -1;
  }
  min_times[from_cell] = 0;
  min_heap_insert(min_heap, &num_min_heap, from_cell, 0);

  while (num_min_heap > 0) {
    min_time_index = min_heap_extract(min_heap, &num_min_heap).cell;
    if (done[min_time_index])
      continue;
    min_time = min_times[min_time_index];
    done[min_time_index] = 1;

    if (min_time_index == exit_cell)
      return min_times[exit_cell];

    e = adj_list[min_time_index];
    while (e) {
      old_time = min_times[e->to_cell];
      if (old_time == -1 || old_time > min_time + e->length) {
        min_times[e->to_cell] = min_time + e->length;
        min_heap_insert(min_heap, &num_min_heap, e->to_cell,
                        min_time + e->length);
      }
      e = e->next;
    }
  }
  return min_times[exit_cell];
}

int main(void) {
  struct timespec start, end;
  double elapsed;

  static edge *adj_list[MAX_CELLS + 1];
  int num_cases, case_num, i;
  int num_cells, exit_cell, time_limit, num_edges;
  int from_cell, to_cell, length;
  int total, min_time;
  edge *e;

  clock_gettime(CLOCK_MONOTONIC, &start);
  scanf("%d", &num_cases);
  for (case_num = 1; case_num <= num_cases; case_num++) {
    scanf("%d%d%d", &num_cells, &exit_cell, &time_limit);
    scanf("%d", &num_edges);
    for (i = 1; i <= num_cells; i++)
      adj_list[i] = NULL;
    for (i = 0; i < num_edges; i++) {
      scanf("%d%d%d", &from_cell, &to_cell, &length);
      e = malloc(sizeof(edge));
      if (e == NULL) {
        fprintf(stderr, "malloc error");
        exit(1);
      }
      e->to_cell = from_cell;
      e->length = length;
      e->next = adj_list[to_cell];
      adj_list[to_cell] = e;
    }

    total = 0;
    for (i = 1; i <= num_cells; i++) {
      min_time = find_time(adj_list, num_cells, i, exit_cell);
      if (min_time >= 0 && min_time <= time_limit)
        total++;
    }
    printf("%d\n", total);
    if (case_num < num_cases)
      printf("\n");
  }
  clock_gettime(CLOCK_MONOTONIC, &end);
  elapsed = (end.tv_sec - start.tv_sec) +
            (end.tv_nsec - start.tv_nsec) / 1000000000.0;
  printf("Elapsed time: %.9f seconds\n", elapsed);
  return 0;
}
