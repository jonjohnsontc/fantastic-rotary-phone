// Dynamic Programming solution from Book
#include <stdio.h>
int max(int v1, int v2) {
  if (v1 > v2)
    return v1;
  else
    return v2;
}

#define SIZE 1000

int solve(char outcome1[], char outcome2[], int goals1[], int goals2[], int n) {
  int i, j, k;
  int first, second, third, fourth;
  static int previous[SIZE + 1], current[SIZE + 1];
  for (i = 0; i <= n; i++)
    previous[i] = 0;
  for (i = 1; i <= n; i++) {
    for (j = 1; j <= n; j++) {
      if ((outcome1[i] == 'W' && outcome2[j] == 'L' && goals1[i] > goals2[j]) ||
          (outcome1[i] == 'L' && outcome2[j] == 'W' && goals1[i] < goals2[j]))
        first = previous[j - 1] + goals1[i] + goals2[j];
      else
        first = 0;
      second = previous[j - 1];
      third = previous[j];
      fourth = current[j - 1];
      current[j] = max(first, max(second, max(third, fourth)));
    }
    for (k = 0; k <= SIZE; k++)
      previous[k] = current[k];
  }
  return current[n];
}

int main(void) {
  int i, n, result;
  char outcome1[SIZE + 1], outcome2[SIZE + 1];
  int goals1[SIZE + 1], goals2[SIZE + 1];
  scanf("%d ", &n);
  for (i = 1; i <= n; i++)
    scanf("%c", &outcome1[i]);
  for (i = 1; i <= n; i++)
    scanf("%d ", &goals1[i]);
  for (i = 1; i <= n; i++)
    scanf("%c", &outcome2[i]);
  for (i = 1; i <= n; i++)
    scanf("%d", &goals2[i]);
  result = solve(outcome1, outcome2, goals1, goals2, n);
  printf("%d\n", result);
  return 0;
}