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

int main() {
  int ppl, num_lines;
  char input[MAXSIZE];
  fgets(input, MAXSIZE, stdin);
  printf("After first fgets call, input is %s\n", input);
  num_lines = atoi(strtok(input, " "));
  ppl = atoi(strtok(NULL, " "));

  printf("num_lines read in is %d\n", num_lines);
  printf("ppl is %d\n", ppl);
  int *lines = malloc(num_lines);

  fgets(input, MAXSIZE, stdin);
  printf("After second fgets call, input is %s\n", input);
  for (int i = 0; i <= num_lines; i++) {
    if (i % 2 == 0) 
      lines[i] = atoi(strtok(input, " "));
    else
      lines[i] = atoi(strtok(NULL, " "));
    printf("index %d is %d\n", i, lines[i]);
  }

  printf("Initial lines is\n");
  for (int j = 0; j < num_lines; j++) {
    printf("%d ", lines[j]);
  }
  printf("\n");

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