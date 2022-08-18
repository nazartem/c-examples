/* пример обрабатки сигналов SIGUSR1 ,SIGUSR2, SIGTERM */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

/* функция-обработчик сигналов */
void my_handler(int signo) {
  if (signo == SIGUSR1) {
    printf("signal SIGUSR1 caught\n");
  }
  else if (signo == SIGUSR2) {
    printf("signal SIGUSR2 caught\n");
  }
  else if (signo == SIGTERM) {
    printf("signal SIGTERM caught\n");
    exit(EXIT_SUCCESS);
  }
  else {
    printf("Неожиданный сигнал!\n");
    exit (EXIT_FAILURE);
  }
}

int main() {
  struct sigaction act; // структура sigaction

  memset(&act, 0, sizeof(act)); // обнуление структуры
  act.sa_handler = my_handler; // установка своего обработчика сигналов

  /* блокировка сигналов */
  sigset_t set; // набор сигналов
  sigemptyset(&set); // инициализация набора сигналов пустыми значениями
  sigaddset(&set, SIGUSR1); // добавление значения сигнала в набор
  sigaddset(&set, SIGUSR2);
  sigaddset(&set, SIGTERM);
  act.sa_mask = set; // маска сигналов, блокируемых на время вызова обработчика

  /* устанавка обработчика сигналов */
  sigaction(SIGUSR1, &act, 0);
  if (sigaction(SIGUSR1, &act, 0) < 0) {
    printf("sigaction on SIGUSR1 failed");
    return 1;
  }
  sigaction(SIGUSR2, &act, 0);
  if (sigaction(SIGUSR2, &act, 0) < 0) {
    printf("sigaction on SIGUSR1 failed");
    return 1;
  }
  sigaction(SIGTERM, &act, 0);
  if (sigaction(SIGTERM, &act, 0) < 0) {
    printf("sigaction on SIGUSR1 failed");
    return 1;
  }

  /* отправка сигналов самому себе */
  while (1) {
    raise(SIGUSR1);
    raise(SIGUSR1);
    raise(SIGUSR1);
    raise(SIGUSR2);
    raise(SIGTERM);
  }

  /* for (;;)
      pause(); ожидание сигналов*/

  return 0;
}
