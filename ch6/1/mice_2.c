/*
    version of the first solution but only running djikstras algorithm once,
    against a reversed weighted graph to find the shortest path from the
    exit cell to the starting cell
*/
#include <stdio.h>
#include <stdlib.h>
#define MAX_CELLS 100

typedef struct edge {
  int to_cell, length;
  struct edge *next;
} edge;

int find_time(edge *adj_list[], int num_cells, int from_cell, int exit_cell) {
  static int done[MAX_CELLS + 1];
  static int min_times[MAX_CELLS + 1];
  int i, j, found;
  int min_time, min_time_index, old_time;
  edge *e;
  for (i = 1; i <= num_cells; i++) {
    done[i] = 0;
    min_times[i] = -1;
  }
  min_times[from_cell] = 0;
  for (i = 0; i < num_cells;
       i++) { // outer loop | sets cell to done and updates shortest paths
    min_time = -1;
    found = 0;
    for (j = 1; j <= num_cells; j++) { // inner loop | finds min_time value for
                                       // paths that aren't finished
      if (!done[j] && min_times[j] >= 0) {
        if (min_time == -1 || min_times[j] < min_time) {
          min_time = min_times[j];
          min_time_index = j;
          found = 1;
        }
      }
    }
    if (!found)
      break;
    done[min_time_index] = 1;
    
    // Ideally I only want djikstra's algorithm to run once, so I don't think this is the
    // right way to do things. I think I should effectively run this loop twice, Once for the first cell,
    // and then once for the exit_cell

    // I believe this because:
      // The only cell with a distance of 0 from the `from_cell` is the same cell
      // In order for any routes to be found outside of the self-self route, 
        // it would have to be run for some completed cell(s)
    // Although, just because I run djikstras for the first cell and the last, is there
    // any guarantee that the second shortest route is the one for the exit cell (I don't think so!)
    // So, in that case, I feel like this is the right route, but I should time everything specifically to be sure.
    if (min_time_index == exit_cell)
      return min_times[exit_cell];

    e = adj_list[min_time_index];
    while (e) {
      old_time = min_times[e->to_cell];
      if (old_time == -1 || old_time > min_time + e->length)
        min_times[e->to_cell] = min_time + e->length;
      e = e->next;
    }
  }
  return min_times[exit_cell];
}

int main(void) {
  static edge *adj_list[MAX_CELLS + 1];
  int num_cases, case_num, i;
  int num_cells, exit_cell, time_limit, num_edges;
  int from_cell, to_cell, length;
  int total, min_time;
  edge *e;

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
  return 0;
}