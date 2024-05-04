// N food lines available
// ith line as a_i people in it
// M people wanna enter the shortest line they see

// 1 <= N <= 100
// 1 <= M <= 100

// N is the first int
// M is the second int
// we get a second line with N number of positive
// integers with current lengths of lines

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 512

void smallest_int(const int *arr, int len, int *min_val, int *min_idx);

int main() {
  int ppl, num_lines;
  char input[MAXSIZE];
  fgets(input, MAXSIZE, stdin);
  num_lines = atoi(strtok(input, " "));
  ppl = atoi(strtok(NULL, " "));
  
  int *lines = malloc(num_lines);

  fgets(input, MAXSIZE, stdin);
  lines[0] = atoi(strtok(input, " "));
  for (int i = 1; i < num_lines; i++) {
    lines[i] = atoi(strtok(NULL, " "));
  }

  int min_idx = 0;
  int min_val = 0;
  for (; ppl > 0; ppl--) {
    smallest_int(lines, num_lines, &min_val, &min_idx);
    printf("%d\n", min_val);
    lines[min_idx]++;
  }
}

void smallest_int(const int *arr, int len, int *min_val, int *min_idx) {
  if (len <= 0) {
    *min_val = 0;
    *min_idx = -1;
    return;
  }

  // set to initial values
  *min_val = arr[0];
  *min_idx = 0;

  for (int i = 1; i < len; i++) {
    if (arr[i] < *min_val) {
      *min_val = arr[i];
      *min_idx = i;
    }
  }
}
