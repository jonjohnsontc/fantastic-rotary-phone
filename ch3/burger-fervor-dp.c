// onlinejudge.org #10465 - Homer Simpson
// Aka highest integer with lowest remainder
// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=16&page=show_problem&problem=1406
#include <stdio.h>
#define MAX_TIME 10000

/* tracks solve_t calls */
unsigned long long total_calls;

/* return highest integer*/
int max(int v1, int v2) {
  if (v1 > v2)
    return v1;
  else
    return v2;
}

#define UNKNOWN -2

void solve(int m, int n, int t) {
  int result, i, m_traverse, n_traverse;
  int dp[MAX_TIME];
  dp[0] = 0; /* solution at zero mins will be zero */
  for (i = 1; i <= t; i++) {
    if (i >= m)
      m_traverse = dp[i - m];
    else
      m_traverse = -1;
    if (i >= n)
      n_traverse = dp[i - n];
    else
      n_traverse = -1;
    if (m_traverse == -1 && n_traverse == -1)
        dp[i] = -1;
    else
     dp[i] = max(m_traverse, n_traverse) + 1;
  }

  result = dp[t];
  if (result >= 0) 
    printf("%d\n", result);
  else {
    i = t - 1;
    result = dp[i];
    while (result == -1) {
        i--;
        result = dp[i];
    }
    printf("%d %d\n", result, t - i);
  };
}

int main(void) {
  int m, n, t;
  while (scanf("%d %d %d", &m, &n, &t) != EOF)
    solve(m, n, t);
  return 0;
}