#include <stdio.h>
#include <stdlib.h>
#define MAX_FLAKES 100000 /* max number of snowflakes to be read from input */

typedef struct node {
  int snowflake[6];
  struct node *next;
} node;

int are_identical(int cmp1[], int cmp2[]);

void identify_identical(node *nodes[]) {
  node *n1, *n2;
  int i;
  for (i = 0; i < MAX_FLAKES; i++) {
    n1 = nodes[i];
    while (n1 != NULL) {
      n2 = n1->next;
      while (n2 != NULL) {
        if (are_identical(n1->snowflake, n2->snowflake)) {
          printf("Twin snowflakes found.\n");
          return;
        }
        n2 = n2->next;
      }
      n1 = n1->next;
    }
  }
  printf("No two snowflakes are alike.\n");
}

int identical_right(int cmp1[], int cmp2[], int start_i) {
  int offset;
  for (offset = 0; offset < 6; offset++) {
    // leveraging the modulo allows us to mimic array wraparound
    // behavior for indices >= 6
    if (cmp1[offset] != cmp2[(start_i + offset) % 6]) {
      return 0; /* return false */
    }
  }
  return 1; /* return true */
}

int identical_left(int cmp1[], int cmp2[], int start_i) {
  int offset, cmp2_i;
  for (offset = 0; offset < 6; offset++) {
    cmp2_i = start_i - offset; /* we're moving left*/
    if (cmp2_i <= -1) {
      cmp2_i = cmp2_i + 6;
    }
    if (cmp1[offset] != cmp2[cmp2_i]) {
      return 0;
    }
  }
  return 1;
}

int are_identical(int cmp1[], int cmp2[]) {
  int start;
  for (start = 0; start < 6; start++) {
    if (identical_right(cmp1, cmp2, start))
      return 1;
    if (identical_left(cmp1, cmp2, start))
      return 1;
  }
  return 0;
}

int hash(int nums[7]) {
  return (nums[0] + nums[1] + nums[2] + nums[3] + nums[4] + nums[5] + nums[6]) %
         MAX_FLAKES;
}

int main(void) {
  static node *snowflakes[MAX_FLAKES] = {NULL};
  node *snow;
  int n, i, j, hashname;
  scanf("%d", &n);
  for (i = 0; i < n; i++) {
    snow = malloc(sizeof(node));
    if (snow == NULL) {
      fprintf(stderr, "malloc error\n");
      exit(1);
    }
    for (j = 0; j < 6; j++)
      scanf("%d", &snow->snowflake[j]);
    hashname = hash(snow->snowflake);
    snow->next = snowflakes[hashname];
    snowflakes[hashname] = snow;
  }
  identify_identical(snowflakes);
  return 0;
}