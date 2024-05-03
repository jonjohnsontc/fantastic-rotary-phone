// N food lines available
// ith line as a_i people in it
// M people wanna enter the shortest line they see

// 1 <= N <= 100
// 1 <= M <= 100

// N is the first int
// M is the second int

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 512

int main() {
  int ppl, num_lines;
  char input[MAXSIZE];
  fgets(input, MAXSIZE, stdin);
  num_lines = atoi(strtok(input, " "));
  ppl = atoi(strtok(NULL, " "));

  printf("num_lines read in is %d\n", num_lines);
  printf("ppl is %d\n", ppl);
  int *lines = malloc(num_lines);
  
  // initialize lines to 0
  for (int i = 0; i < num_lines; i++)
    lines[i] = 0;

  // populate lines with people
  for (int ln = 0, person = 0; person < ppl; person++, ln++) {
    if (ln == num_lines)
      ln = 0;
    lines[ln] += 1;
  }

  for (int ln = 0; ln < num_lines; ln++)
    printf("%d ", lines[ln]);
  printf("\n");
}