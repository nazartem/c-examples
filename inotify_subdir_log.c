/* программа слежки за созданием, изменением и удалением файлов и директорий
внутри заданной директории и её поддиректориях, запись событий осуществляется
в log файл*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <dirent.h>
#include <limits.h>
#include <unistd.h>


#define MAX_LEN 1024 /*длина пути для директории*/
#define MAX_EVENTS 1024 /*максимальное количество событий для обработки за один раз*/
#define LEN_NAME 16 /*предположим, что длина имени файла не превышает 16 байт*/
#define EVENT_SIZE  ( sizeof (struct inotify_event) ) /*размер структуры события*/
#define BUF_LEN     ( MAX_EVENTS * ( EVENT_SIZE + LEN_NAME )) /*буфер для хранения данных события*/


/* файл журнала*/
FILE *fp_log;


/* добавим наблюдения inotify для поддиректорий сразу после добавления корневой директории */

void add_watches(int fd, char *root) {
 int wd;
 char *abs_dir;
 struct dirent *entry;
 DIR *dp;

 dp = opendir(root);
 if (dp == NULL) {
   perror("Error opening the starting directory");
   exit(0);
 }

 /* добавление наблюдения для корневой директории */
 wd = inotify_add_watch(fd, root, IN_CREATE | IN_MODIFY | IN_DELETE);
 if (wd == -1) {
   fprintf(fp_log,"Couldn't add watch to %s\n",root);
 }
 else {
   printf("Watching:: %s\n",root);
 }

 /* добавление наблюдений для поддиректорий первого уровня*/
 abs_dir = (char *)malloc(MAX_LEN);
 while((entry = readdir(dp))) {
   /* if its a directory, add a watch*/
   if (entry->d_type == DT_DIR) {
     strcpy(abs_dir,root);
     strcat(abs_dir,entry->d_name);

     wd = inotify_add_watch(fd, abs_dir, IN_CREATE | IN_MODIFY | IN_DELETE);
     if (wd == -1)
       printf("Couldn't add watch to the directory %s\n",abs_dir);
     else
       printf("Watching:: %s\n",abs_dir);
   }
 }

 closedir(dp);
 free(abs_dir);
}

/* функция main*/
int main( int argc, char **argv ) {
 int length, i = 0;
 int fd;
 char buffer[BUF_LEN], root[MAX_LEN];


 /*проверка наличия параметра командной строки*/
 switch(argc) {
   case 1: printf("No directory specified. Will monitor the entire filesystem...\n\n");
     strcpy(root,"/");
     break;

   case 2: strcpy(root,argv[1]);
     if(root[strlen(root)-1]!='/')
       strcat(root,"/");
     puts(root);

     break;

   default: printf("Ignoring all other arguments after the first\n");
 }

 /* инициализация Inotify*/
 fd = inotify_init();
 if ( fd < 0 ) {
   perror( "Couldn't initialize inotify");
 }

 /* обход поддиректорий первого уровня и добавление наблюдений */
 add_watches(fd,root);

 /* бесконечный цикл*/
 while(1) {
   i = 0;
   length = read( fd, buffer, BUF_LEN );

   /* открытие файла журнала*/
   fp_log = fopen("/home/nazaryap/Dev/inotify_logger.log","a");
   if (fp_log == NULL) {
     printf("Error opening logger. All output will be redirected to the stdout\n");
     fp_log = stdout;
   }

   if ( length < 0 ) {
     perror( "read" );
   }
   /* чтентие событий*/
   while ( i < length ) {

     struct inotify_event *event = ( struct inotify_event * ) &buffer[ i ];
     if ( event->len ) {
       if ( event->mask & IN_CREATE) {
         if (event->mask & IN_ISDIR)
          fprintf(fp_log,"%d DIR::%s CREATED\n", event->wd,event->name );
         else
          fprintf(fp_log, "%d FILE::%s CREATED\n", event->wd, event->name);
       }

       if ( event->mask & IN_MODIFY) {
         if (event->mask & IN_ISDIR)
          fprintf(fp_log,"%d DIR::%s MODIFIED\n", event->wd,event->name );
         else
          fprintf(fp_log,"%d FILE::%s MODIFIED\n", event->wd,event->name );
       }

       if ( event->mask & IN_DELETE) {
         if (event->mask & IN_ISDIR)
          fprintf(fp_log,"%d DIR::%s DELETED\n", event->wd,event->name );
         else
          fprintf(fp_log,"%d FILE::%s DELETED\n", event->wd,event->name );
       }

       i += EVENT_SIZE + event->len;
     }
   }
   /* закрытие файла журнала*/
   fclose(fp_log);
 }

 /* освобождение ресурсов*/
 ( void ) close( fd );

 return 0;
}
