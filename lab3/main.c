#include <stdio.h>
#include <string.h>

/**
 * ІО-12, Воробйов Антон, номер у списку групи - 4
 *
 * Варіант: привести строку до малих символів.
 */

int main(void)
{
  printf("Уведіть строку: ");
  char *string;
  scanf("%s", string);
  char *lowerCasedString;
  for (int i = 0; i < strlen(string); i++)
  {
    int charCode = (int)(char)string[i];
    int lowerCasedCharCode;
    // Символи з кодами 65-90 - букви у верхньому регістрі
    if (charCode < 65 || charCode > 90)
    {
      lowerCasedCharCode = charCode;
    }
    else
    {
      lowerCasedCharCode = charCode + 32;
    }
    lowerCasedString[i] = (char)lowerCasedCharCode;
  }
  printf("%s", lowerCasedString);
  return 0;
}
