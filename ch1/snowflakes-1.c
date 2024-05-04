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

int main(void) {
  int sample[] = {1, 2, 3, 1, 5};
  identify_identical(sample, 5);
  return 0;
}