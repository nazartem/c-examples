/* демон завершает свою работу с приходом сигнала SIGURG*/

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int main() {
  pid_t pid;

  /* создание нового процесса */
	pid = fork(); /* развилка на два процесса */
	if (pid == -1) /* если произошла ошибка */
		return -1;
	else if (pid != 0)
		exit(EXIT_SUCCESS); /* завершение работы родительского процесса */

  /* сигнал выхода */
  signal(SIGURG, exit);

  /* создание нового сеанса и группы процессов */
	if (setsid() == -1)
		return -1;

	/* установка в качестве рабочего каталога корневого каталога */
	if (chdir("/") == -1)
		return -1; /* если произошла ошибка */

	/* вывод PID процесса потомка (демона)*/
	printf("%d\n", getpid());

	/* перенаправление дескрипторов файла 0,1,2 в /dev/null */
	open("/dev/null", O_RDWR); /* stdin */
	dup(0); /* stdout */
	dup(0); /* stderror */

  /* всякие действия демона... */
	for(;;)
    pause();
}
