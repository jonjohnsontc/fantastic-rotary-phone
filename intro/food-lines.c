// N food lines available
// ith line as a_i people in it
// M people wanna enter the shortest line they see

// 1 <= N <= 100
// 1 <= M <= 100

// N is the first int
// M is the second int

#include <stdio.h>
#include <stdlib.h>
int main() {
  int ppl, num_lines;

  int *lines = malloc(num_lines * sizeof(int));
  for (int i = 0; i < num_lines; i++)
    lines[i] = 0;
  for (int j = 0; j < ppl; j++)
    lines[j] += 1;
  for (int ln = 0; ln < num_lines; ln++)
    printf("%d ", ln);
}