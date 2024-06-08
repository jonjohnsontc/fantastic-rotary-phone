#include <stdio.h>
#define MAX_A 1000
#define MAX_B 200
#define MAX_K 200
#define MOD 1000000007

typedef struct pair {
  int end_at_i;
  int total;
} pair;

/*
The new subproblem with parameters i, j, and k is going to tell us the number
of ways that we can choose exactly k substrings from a[0..i] to build exactly
b[0..j].
*/
pair solve(char a[], char b[], int i, int j, int k,
           pair memo[MAX_A][MAX_B][MAX_K + 1]) {
  int total, end_at_i;
  if (memo[i][j][k].total != -1)
    return memo[i][j][k];
  if (j == 0 && k == 1) {
    if (a[i] != b[j]) {
      if (i == 0)
        total = 0;
      else
        total = solve(a, b, i - 1, j, k, memo).total;
      memo[i][j][k] = (pair){0, total};
    } else {
      if (i == 0)
        total = 1;
      else
        total = 1 + solve(a, b, i - 1, j, k, memo).total;
      memo[i][j][k] = (pair){1, total};
    }
    return memo[i][j][k];
  }
  if (i == 0 || j == 0 || k == 0) {
    memo[i][j][k] = (pair){0, 0};
    return memo[i][j][k];
  }
  if (a[i] != b[j])
    end_at_i = 0;
  else {
    end_at_i = (solve(a, b, i - 1, j - 1, k - 1, memo).total +
                solve(a, b, i - 1, j - 1, k, memo).end_at_i);
    end_at_i = end_at_i % MOD;
  }
  total = (end_at_i + solve(a, b, i - 1, j, k, memo).total) % MOD;
  memo[i][j][k] = (pair){end_at_i, total};
  return memo[i][j][k];
}

int main(void) {
  int a_length, b_length, num_substrings, i, j, k, result;
  char a[MAX_A + 1];
  char b[MAX_B + 1];
  static pair memo[MAX_A][MAX_B][MAX_K + 1];
  scanf("%d%d%d", &a_length, &b_length, &num_substrings);
  scanf("%s", a);
  scanf("%s", b);
  for (i = 0; i < a_length; i++)
    for (j = 0; j < b_length; j++)
      for (k = 0; k <= num_substrings; k++)
        memo[i][j][k] = (pair){-1, -1};
  result = solve(a, b, a_length - 1, b_length - 1, num_substrings, memo).total;
  printf("%d\n", result);
  return 0;
}