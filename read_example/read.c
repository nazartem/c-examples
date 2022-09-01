#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define LEN 255 // максимальная длина анализируемых строк
#define PARAMCOUNT 3 // количество параметров в файле cfg

struct Config_param { // структура для хранения параметров из файла .cfg
    int wait_timeout;
    int twait;
    int lock_wait;
} options; // с именем options

char configName[] = "myconfig.cfg";

int set_option(FILE *file) { // функция для парсинга файла .cfg
    char line[LEN]; // переменная для хранения строк
    char sep[10] = "="; // символ-разделитель
    int opt_idx = 0; // начальный индекс массива параметров
    int opt_array[PARAMCOUNT] = {0}; // массив для записи параметров
    struct Config_param *option_ptr; // указатель для записи в структуру
    option_ptr = &options; // запись адреса структуры в указатель

    if (option_ptr != NULL) { // проверка, задан ли указатель на структуру
        if (file != NULL) { // если файл удалось открыть
            printf("Файл %s открыт\n\n", configName);

            while (!feof(file)) { // пока файл не закончился
                if (fgets(line, LEN, file) != NULL) { // если строка прочитана
                    if (line[0] == '#' || line[0] == '\n') { // пропуск лишних строк
                        continue;
                    }

                    strtok(line, sep); // пропустить часть строки до разделителя
                    opt_array[opt_idx] = atoi(strtok(NULL, sep)); // запись параметра в массив
                    opt_idx++; // переход к следующей ячейке массива
                }
            }
            option_ptr->wait_timeout = opt_array[0]; // запись параметров
            option_ptr->twait = opt_array[1]; // из массива в структуру
            option_ptr->lock_wait = opt_array[2];

            return 0; // если файл открыт и произошла запись параметров
        }
        else {
            fprintf(stderr, "Не удалось открыть файл %s\n", configName);
            return 1; // если файл не найден
        }
    }


}

int main() {
    FILE *file = fopen(configName, "r"); // открыть файл для чтения
    // идентификатор файла записан в file

    int result; // переменная для хранения результата записи параметров

    result = set_option(file);

    fclose(file); // закрыть файл

    printf("Время одного цикла ожидания: %d\n"
           "Количество циклов ожидания: %d\n"
           "Время ожидания для проверки поступления новых данных: %d\n",
           options.wait_timeout, options.twait, options.lock_wait);
    if (result == 0) {
      printf("\nЧтение параметров успешно выполнено\n");
    }
    else {
      printf("\nОшибка чтения параметров\n");
    }

    return 0;
}
