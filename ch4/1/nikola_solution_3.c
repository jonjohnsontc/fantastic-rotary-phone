// DP solution to nikola problem
#include <stdio.h>
#define SIZE 1000
#define UNSET -2
#define IMPOSSIBLE -1
int min(int v1, int v2) {
  if (v1 < v2)
    return v1;
  else
    return v2;
}

int solve(int cost[], int n, int i, int j, int dp[SIZE + 1][SIZE + 1]) {
  if (dp[i][j] != UNSET)
    return dp[i][j];
  int first, second;
  int result;
  first = 0;
  second = 0;
  for (j = n; j >= 1; j--)
    for (i = 1; i < n; i++) {
      dp[i][j] = solve(cost, n, i, j, dp);
    }
  if (first == -1 && second == -1) {
    dp[i][j] = IMPOSSIBLE;
    return dp[i][j];
  } else if (second == -1) {
    dp[i][j] = first + cost[i];
    return dp[i][j];
  } else if (first == -1) {
    dp[i][j] = second + cost[i];
  } else {
    dp[i][j] = min(first, second) + cost[i];
  }

  return -1;
}

int main(void) {
  static int dp[SIZE + 1][SIZE + 1];
  int cost[SIZE + 1];
  int n, i, j, result;
  scanf("%d ", &n);
  for (i = 0; i < n; i++)
    scanf("%d", &cost[i]);

  for (i = 1; i < SIZE + 1; i++)
    for (j = 1; j < SIZE + 1; j++)
      dp[i][j] = UNSET;

  result = solve(cost, n, i, j, dp);
  printf("%d\n", result);
}