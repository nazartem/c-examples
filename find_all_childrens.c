/* по заданному pid, осуществляет поиск всех потомков процесса с этим
идентификатором и выводит их количество (включая процесс с заданным pid) */

#include <stdio.h>
#include <stdlib.h>

int check_child(int id, int *c_point) {
	int var_id = id;
	char buf[256] = {0};

	sprintf(buf, "/proc/%d/task/%d/children", var_id, var_id);
	FILE* fd = fopen(buf, "r");

	if (fd != NULL) {
		while ( fscanf(fd, "%d", &var_id) != EOF ) {
			(*c_point)++;
			check_child(var_id, c_point);
		}
		fclose(fd);
	}
	else {
		printf("Не удалось открыть файл\n");
		return 0;
	}

}

int main(int argc, char* argv[]) {
	int count = 1;
	int *c_point = &count;

	if ( argc < 2 )
		return -1;

	int id = atoi(argv[1]);

	check_child(id, c_point);

	printf("%d\n", count);

	return 0;
}
