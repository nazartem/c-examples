/* поиск родительского PID текущего процесса в файловой системе proc и вывод
найденного значения на консоль */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int ppid = 0;

  FILE *stat_file = fopen("/proc/self/stat", "r");

  fscanf(stat_file, "%*d %*s %*c %d", &ppid);
  fclose(stat_file);
  printf("%d\n", ppid);

  return 0;
}
