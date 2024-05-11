/* The first version of this problem I tried doing on my own,
based on how I thought best to solve it. This is the version
recommended in the book */

int prefix_length(char s1[], char s2[]) {
  int i = 1;
  while (s1[i] == s2[i])
    i++;
  return i - 1;
}

int suffix_length(char s1[], char s2[], int len) {
  int i = len;
  while (i >= 2 && s1[i] == s2[i - 1])
    i--;
  return len - i;
}

#define SIZE 10000000
#include <stdio.h>
#include <string.h>
int main(void) {
  static char s1[SIZE + 2], s2[SIZE + 2];
  int len, prefix, suffix, total;
  /* 
  - storing the words starting at index 1 to match the requirements for the
  index in the problem description
  - also using gets with c89
  */
  gets(&s1[1]);
  gets(&s2[1]);

  printf("s1: %s\n", s1);
  printf("s2: %s\n", s2);
  len = strlen(&s1[1]);
  prefix = prefix_length(s1, s2);
  suffix = suffix_length(s1, s2, len);
  total = (prefix + 1) - (len - suffix) + 1;
  if (total < 0)
    total = 0;
  
  int i;
  printf("%d\n", total);
  for (i = 0; i < total; i++) {
    printf("%d", i + len - suffix);
    if (i < total - 1)
      printf(" ");
    else
      printf("\n");
  }
  return 0;
}