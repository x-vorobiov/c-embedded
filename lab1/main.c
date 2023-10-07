#include <stdio.h>
#include <math.h>

/**
 * Воробйов Антон, ІО-12, варіант 4
 *
 * z_1 = ((m - 1) * sqrt(m) - (n - 1) * sqrt(n)) / (sqrt(m^3 * n) + n * m + m^2 - m)
 * z_2 = (sqrt(m) - sqrt(n)) / m
 */

int main(void)
{
  double m, n, z1, z2;
  printf("m = ");
  scanf("%lf", &m);
  // Програма обчислює `sqrt(m)` та виконує ділення на `m`
  if (m <= 0)
  {
    printf("`m` must be greater than 0.");
    return 0;
  }
  printf("n = ");
  scanf("%lf", &n);
  // Програма обчислює `sqrt(n)`
  if (n < 0)
  {
    printf("`n` must be greater than or equal to 0.");
    return 0;
  }
  z1 = ((m - 1) * sqrt(m) - (n - 1) * sqrt(n)) / (sqrt(pow(m, 3) * n) + m * n + pow(m, 2) - m);
  z2 = (sqrt(m) - sqrt(n)) / m;
  printf("z1 = %lf\n", z1);
  printf("z2 = %lf\n", z2);
  return 0;
}
