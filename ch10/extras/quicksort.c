#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 10

void *malloc_safe(int size) {
  char *mem = malloc(size);
  if (mem == NULL) {
    fprintf(stderr, "malloc error\n");
    exit(1);
  }
  return mem;
}

void swap(int *x, int *y) {
  int temp = *x;
  *x = *y;
  *y = temp;
}

void quicksort(int values[], int n) {
  int i, small_count, big_count, pivot_index, pivot;
  int *small_values = malloc_safe(n * sizeof(int));
  int *big_values = malloc_safe(n * sizeof(int));
  if (n == 0)
    return;
  small_count = 0;
  big_count = 0;

  // locate pivot value and move to start of array
  // the start of the array will remain out of the way
  // of the rest of the algorithm
  pivot_index = rand() % n;
  swap(&values[0], &values[pivot_index]);
  pivot = values[0];

  for (i = 1; i < n; i++) {
    if (values[i] > pivot) {
      big_values[big_count] = values[i];
      big_count++;
    } else {
      small_values[small_count] = values[i];
      small_count++;
    }
  }
  quicksort(small_values, small_count);
  quicksort(big_values, big_count);

  // put values back into single array inclusive of pivot value
  for (i = 0; i < small_count; i++)
    values[i] = small_values[i];
  values[small_count] = pivot;
  for (i = 0; i < big_count; i++)
    values[small_count + 1 + i] = big_values[i];
}

int main(void) {
  static int values[N] = {96, 61, 36, 74, 45, 60, 47, 6, 95, 93};
  int i;
  srand((unsigned)time(NULL));
  quicksort(values, N);
  for (i = 0; i < N; i++)
    printf("%d ", values[i]);
  printf("\n");
  return 0;
}