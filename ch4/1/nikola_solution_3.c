// DP solution to nikola problem
#include <stdio.h>
#define SIZE 1000

int main(void) {
  // static int dp[SIZE + 1][SIZE + 1];
  int cost[SIZE + 1];
  int n, i, j;
  scanf("%d ", &n);
  for (i = 0; i < n; i++)
    scanf("%d", &cost[i]);
  
  for (j = n; j >= 1; j--)
    for (i = 1; i < n; i++) {
      printf("j = %d, i = %d\n", j, i);
  }
}