#include <stdio.h>
#define MAX_FLAKES 100000 /* max number of snowflakes to be read from input */

int identical_right(int cmp1[], int cmp2[], int start_i);
int identical_left(int cmp1[], int cmp2[], int start_i);

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
    if (cmp1[offset] != cmp2[start_i + offset % 6]) {
      return 0; /* return false */
    }
  }
  return 1; /* return true */
}

int main(void) {
  int sample[] = {1, 2, 3, 1, 5};
  identify_identical(sample, 5);
  return 0;
}