#include <stdio.h>

// Aka highest integer with lowest remainder

int ingest_burgers(int m, int n, int t) { return -1; }

int max(int v1, int v2) {
  if (v1 > v2)
    return v1;
  else
    return v2;
}

int solve_t(int m, int n, int t) {
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

int main(void) {
  int m, n, t;
  while (scanf("%d %d %d", &m, &n, &t) != 0)
    printf("%d", ingest_burgers(m, n, t));
}