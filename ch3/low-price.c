// > 100 test cases
// 1st line is unit price of item + M (# of pricing schemes)
// M lines have n and p (n is number, p is total price)
// Last line is list of integers with desired quantities to buy
#include <stdio.h>
#define M_MAX 20
#define N_MAX 100
#define K_MAX 100

double min(double v1, double v2) {
  if (v1 < v2)
    return v1;
  else
    return v2;
}

double solve_k(int num[], double price[], int num_schemes, double unit_price,
               int num_apples, double memo[]) {
  double best, result;
  int i;
  if (memo[num_apples] != -1)
    return memo[num_apples];
  if (num_apples == 0) {
    memo[num_apples] = 0;
    return 0;
  } else {
    result = solve_k(num, price, num_schemes, unit_price, num_apples - 1, memo);
    best = result + unit_price;
    for (i = 0; i < num_schemes; i++)
      if (num_apples - num[i] >= 0) {
        result =
            solve_k(num, price, num_schemes, unit_price, num_apples - num[i], memo);
        best = min(best, result + price[i]);
      }
    memo[num_apples] = best;
    return memo[num_apples];
  }
}

#define SIZE 200

double solve(int num[], double price[], int num_schemes, double unit_price,
             int num_apples, double memo[]) {
  double best;
  int i;
  best = solve_k(num, price, num_schemes, unit_price, num_apples, memo);
  for (i = num_apples + 1; i < SIZE; i++)
    best = min(best, solve_k(num, price, num_schemes, unit_price, i, memo));
  return best;
}

#define MAX_SCHEMES 20

int get_number(int *num) {
  int ch;
  int ret = 0;
  ch = getchar();
  while (ch != ' ' && ch != '\n') {
    ret = ret * 10 + ch - '0';
    ch = getchar();
  }
  *num = ret;
  return ch == ' ';
}

// buy at least K apples for each k
int main(void) {
  int test_case, num_schemes, num_apples, more, i;
  double unit_price, result;
  int num[MAX_SCHEMES];
  double price[MAX_SCHEMES];
  double memo[SIZE];
  test_case = 0;
  while (scanf("%lf%d ", &unit_price, &num_schemes) != -1) {
    test_case++;
    for (i = 0; i < num_schemes; i++)
      scanf("%d%lf ", &num[i], &price[i]);
    printf("Case %d:\n", test_case);
    for (i = 0; i < SIZE; i++) 
      memo[i] = -1;
    more = get_number(&num_apples);
    while (more) {
      result = solve(num, price, num_schemes, unit_price, num_apples, memo);
      printf("Buy %d for $%.2f\n", num_apples, result);
      more = get_number(&num_apples);
    }
    result = solve(num, price, num_schemes, unit_price, num_apples, memo);
    printf("Buy %d for $%.2f\n", num_apples, result);
  }
  return 0;
}
