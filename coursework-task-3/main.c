#include <stdio.h>
#include "calculator.h"

int main() 
{
  printf("5 + 3 = %d\n", add(5, 3));
  printf("5 - 3 = %d\n", subtract(5, 3));
  printf("5 * 3 = %d\n", multiply(5, 3));
  return 0;
}
