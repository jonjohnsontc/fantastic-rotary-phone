#define MAX_A 1000
#define MAX_B 200
#define MAX_K 200
#define MOD 1000000007

// The number of ways that we can choose exactly k
// substrings from a[0..i] to build b[0..j] exactly.
// Rightmost substring always ends with a[i]
int solve_ijk(char a[], char b[], int i, int j, int k,
              int memo[MAX_A][MAX_B][MAX_K + 1]) {
  int total, q;
//   memoized check
  if (memo[i][j][k] != -1)
    return memo[i][j][k];
// if we only need one substring and it's length is 1
// and the indices are equal, we've got a singular match
  if (j == 0 && k == 1 && a[i] == b[j]) {
    memo[i][j][k] = 1;
    return memo[i][j][k];
  }
//  all impossible states to get a substring that matches
  if (i == 0 || j == 0 || k == 0) {
    memo[i][j][k] = 0;
    return memo[i][j][k];
  }
// if final chars don't match, we can't solve in this manner  
  if (a[i] != b[j]) {
    memo[i][j][k] = 0;
    return memo[i][j][k];
  }
  total = 0;
  for (q = 0; q < i; q++)
    total = (total + solve_ijk(a, b, q, j - 1, k - 1, memo)) % MOD;
  total = (total + solve_ijk(a, b, i - 1, j - 1, k, memo)) % MOD;
  memo[i][j][k] = total;
  return memo[i][j][k];
}