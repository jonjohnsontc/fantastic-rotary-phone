#include <stdio.h>
#define MAX_FLAKES 100000 /* max number of snowflakes to be read from input */

void identify_identical(int nums[], int len) {
  int i, j;
  for (i = 0; i < len; i++) {
    for (j = i + 1; j < len; j++) {
      if (nums[i] == nums[j]) {
        printf("Twin snowflakes found.\n");
        return;
      }
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

int main(void) {
  int sample1[] = {213, 491, 12, 67, 962, 521};
  int sample2[] = {12, 67, 962, 521, 213, 491};
  if (are_identical(sample1, sample2))
    printf("Twin snowflakes found.\n");
  else
    printf("No two snowflakes are alike.\n");
  return 0;
}