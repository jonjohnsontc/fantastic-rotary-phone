#include <stdio.h>

// Aka highest integer with lowest remainder

/* tracks solve_t calls */
unsigned long long total_calls;

/* return highest integer*/
int max(int v1, int v2) {
  if (v1 > v2)
    return v1;
  else
    return v2;
}

/* If homer can spend exactly t minutes eating burgers, then return the maximum
number of burgers he can eat. If he can't spend exactly t minutes eating burgers
meaning he must spend at least one minute drinking beer, then return -1 */
int solve_t(int m, int n, int t) {
  total_calls++;
  if (t == 0)
    return 0;
  int m_traverse;
  if (t >= m)
    m_traverse = solve_t(m, n, t - m);
  else
    m_traverse = -1;

  int n_traverse;
  if (t >= n)
    n_traverse = solve_t(m, n, t - n);
  else
    n_traverse = -1;
  if (m_traverse == -1 && n_traverse == -1)
    return -1;
  return max(m_traverse, n_traverse) + 1;
}

/* Iteratively run solve_t for t - 1 until we find a solution for m n and t*/
void solve(int m, int n, int t) {
  int result, i;
  total_calls = 0;
  result = solve_t(m, n, t);
  if (result >= 0) {
    printf("%d\n", result);
  } else {
    i = t - 1;
    result = solve_t(m, n, i);
    while (result == -1) {
      i--;
      result = solve_t(m, n, i);
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