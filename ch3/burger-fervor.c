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

/* If homer can spend exactly t minutes eating burgers, then return the maximum
number of burgers he can eat. If he can't spend exactly t minutes eating burgers
meaning he must spend at least one minute drinking beer, then return -1 */
int solve_t(int m, int n, int t, int memo[]) {
  total_calls++;
  if (memo[t] != UNKNOWN)
    return memo[t];
  if (t == 0) {
    memo[t] = 0;
    return memo[t];
  }
  int m_traverse, n_traverse;
  if (t >= m)
    m_traverse = solve_t(m, n, t - m, memo);
  else
    m_traverse = -1;

  if (t >= n)
    n_traverse = solve_t(m, n, t - n, memo);
  else
    n_traverse = -1;
  if (m_traverse == -1 && n_traverse == -1) {
    memo[t] = -1;
    return memo[t];
  } else {
    memo[t] = max(m_traverse, n_traverse) + 1;
    return memo[t];
  }
}
 
/* Iteratively run solve_t for t - 1 until we find a solution for m n and t*/
void solve(int m, int n, int t) {
  int result, i;
  int memo[MAX_TIME];
  total_calls = 0;
  /* initialize memo to unknown value */ 
  for (i = 0; i <= t; i++)
    memo[i] = UNKNOWN;
  result = solve_t(m, n, t, memo);
  if (result >= 0) {
    printf("%d\n", result);
  } else {
    i = t - 1;
    result = solve_t(m, n, i, memo);
    while (result == -1) {
      i--;
      result = solve_t(m, n, i, memo);
    }
    printf("%d %d\n", result, t - i);
  }
  printf("Total calls to solve_t: %llu\n", total_calls);
}

int main(void) {
  int m, n, t;
  while (scanf("%d %d %d", &m, &n, &t) != EOF)
    solve(m, n, t);
  return 0;
}