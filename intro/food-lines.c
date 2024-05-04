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

int shortest_ln(int *arr, int len);
int min(int a, int b);

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
  printf("Initial lines:\n");
  for (int j = 0; j < num_lines; j++) {
    printf("%d ", lines[j]);
  }
  printf("\n");

  for (; ppl > 0; ppl--) {
    int idx = shortest_ln(lines, num_lines);
    printf("%d\n", lines[idx]);
    lines[idx]++;
  }
}

int shortest_ln(int *arr, int len) {
  int shorty = 101;
  int i;
  for (i = 0; i < len; i++) {
    printf("Comparing %d and %d\n", shorty, arr[i]);
    shorty = min(shorty, arr[i]);
    printf("Min is %d\n", shorty);
  }
  return i;
}

int min(int a, int b) {return a < b ? a : b;}