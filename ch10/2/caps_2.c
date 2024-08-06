/*
  Recursively find cap and bottle pairs in smaller batches of caps
  and bottles
*/
#include <stdio.h>
#include <stdlib.h>
#define MAX_N 10000
void solve(int caps[], int bottles[], int n);
int main(void) {
  int n, i;
  int cap_nums[MAX_N], bottle_nums[MAX_N];
  scanf("%d", &n);
  // initialize cap and bottle num arrays
  for (i = 0; i < n; i++) {
    cap_nums[i] = i + 1;
    bottle_nums[i] = i + 1;
  }
  solve(cap_nums, bottle_nums, n);
  return 0;
}

void *malloc_safe(int size) {
  char *mem = malloc(size);
  if (mem == NULL) {
    fprintf(stderr, "malloc error\n");
    exit(1);
  }
  return mem;
}

void solve(int cap_nums[], int bottle_nums[], int n) {
  int small_count, big_count, cap_num, i, result, matching_bottle;
  int *small_caps = malloc_safe(n * sizeof(int));
  int *small_bottles = malloc_safe(n * sizeof(int));
  int *big_caps = malloc_safe(n * sizeof(int));
  int *big_bottles = malloc_safe(n * sizeof(int));
  if (n == 0)
    return;

  small_count = 0;
  big_count = 0;

  cap_num = cap_nums[0]; // selecting the first cap

  // find the matching bottle for cap and sort
  // all other matches into smaller and larger arrays
  for (i = 0; i < n; i++) {
    printf("0 %d %d\n", cap_num, bottle_nums[i]);
    scanf("%d", &result);
    if (result == 0) {
      printf("1 %d %d\n", cap_num, bottle_nums[i]);
      matching_bottle = bottle_nums[i];
    } else if (result == -1) {
      big_bottles[big_count] = bottle_nums[i];
      big_count++;
    } else {
      small_bottles[small_count] = bottle_nums[i];
      small_count++;
    }
  }

  small_count = 0;
  big_count = 0;
  // sort the caps into smaller and larger arrays compared to
  // the matching bottle
  for (i = 0; i < n; i++) {
    printf("0 %d %d\n", cap_nums[i], matching_bottle);
    scanf("%d", &result);
    if (result == -1) {
      small_caps[small_count] = cap_nums[i];
      small_count++;
    } else if (result == 1) {
      big_caps[big_count] = cap_nums[i];
      big_count++;
    }
  }
  // recursively solve for small and big caps/bottles
  solve(small_caps, small_bottles, small_count);
  solve(big_caps, big_bottles, big_count);
}