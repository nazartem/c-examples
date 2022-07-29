// по заданному pid, осуществляет поиск пути в дереве процессов до процесса с идентификатором 1 (init)
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	if ( argc < 2 )
		return -1;

	int pid = atoi(argv[1]);
	printf("%d\n", pid);

	while ( pid != 1 ) {
		char buf[256] = {0};
		sprintf(buf, "/proc/%d/stat", pid);

		FILE* fd = fopen(buf, "r");

		fscanf(fd, "%*d %*s %*c %d", &pid);

		printf("%d\n", pid);
	}

	return 0;
}
