/* программа при запуске себя "демонизирует" и остается в  памяти */

#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/fs.h>

int main(void) {
	pid_t pid;
	// int i;

	/* создание нового процесса */
	pid = fork(); /* развилка на два процесса */
	if (pid == -1) /* если произошла ошибка */
		return -1;
	else if (pid != 0)
		exit(EXIT_SUCCESS); /* завершение работы родительского процесса */

	/* создание нового сеанса и группы процессов */
	if (setsid() == -1)
		return -1;

	/* установка в качестве рабочего каталога корневого каталога */
	if (chdir("/") == -1)
		return -1; /* если произошла ошибка */

	/* закрытие всех открытых файлов */
	/* NR_OPEN это слишком, но это работает */
	// for (i = 0; i < NR_OPEN; i++)
	// 	close(i);

	/* вывод PID процесса потомка (демона)*/
	printf("%d\n", getpid());

	/* перенаправление дескрипторов файла 0,1,2 в /dev/null */
	open("/dev/null", O_RDWR); /* stdin */
	dup(0); /* stdout */
	dup(0); /* stderror */

	// либо
	// fclose(stdin);
	// fclose(stdout);
	// fclose(stderr);

	/* всякие действия демона... */
	pause();
	return 0;
}
