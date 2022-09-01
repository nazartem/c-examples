#include <stdio.h>
#include "my_lib.h"

int main(int argc, char* argv[]) {
  int num;

  printf("Введите целое число\n");
  scanf("%d", &num);
  printf("Квадрат %d = %d\n", num, sqr(num));

  return 0;
};
