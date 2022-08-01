/* поиск и подсчет числа процессов с именем needle_name в системе Linux на
которой выполняется программа */

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

int main(void) {
  struct dirent **namelist;
  int n = -1, sLen = 0, i = 0, name_count = 0;
  bool is_number;
  char needle_name[] = "bash";
  char filename[200], procname[200];

  n = scandir("/proc/", &namelist, NULL, alphasort); // сканирование дирректории
  // namelist - массив указателей на все файлы и папки
  if (n < 0) { // Функция scandir() возвращает количество выбранных записей или -1, если произошла ошибка
    perror("scandir");
  }
  else {
    while(n--) {

      namelist[n]->d_name;
      sLen = strlen(namelist[n]->d_name); //Определяем количество символов в названии
      for (i; i < sLen; i++) { //Проверка, является ли название числом, т.к. информация о всех процессах хранится в папках с названием из цифр
        if(!isdigit(namelist[n]->d_name[i])) {
          is_number = false; // если встретился символ, отличный от числа
          break;
        }
        else {
          is_number = true;
          break;
        }
      }
      if (is_number) {
        sprintf(filename, "/proc/%s/comm", namelist[n]->d_name); // получение пути до папки comm
        FILE *file = fopen(filename, "r");
        fscanf(file, "%s", &procname); // запись имени процесса из файла в переменную
        if (strstr(procname, needle_name) != NULL) { // поиск вхождения нужного названия в текущее название
          name_count++;
        }

        fclose(file);
      }
    free(namelist[n]);
    }
    free(namelist);
  }
  printf("%d\n", name_count);
  return 0;
}
