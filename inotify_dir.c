/* программа слежки за созданием, изменением и удалением файлов и директорий
внутри заданной директории */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <limits.h>
#include <unistd.h>

#define MAX_EVENTS 1024 /*Максимальное кличество событий для обработки за один раз*/
#define LEN_NAME 16 /*Будем считать, что длина имени файла не превышает 16 символов*/
#define EVENT_SIZE  ( sizeof (struct inotify_event) ) /*размер структуры события*/
#define BUF_LEN     ( MAX_EVENTS * ( EVENT_SIZE + LEN_NAME )) /*буфер для хранения данных о событиях*/

int main( int argc, char **argv )
{
	int length, i = 0, wd;
	int fd;
	char buffer[BUF_LEN];

	 /* Инициализация Inotify*/
	fd = inotify_init();
	if ( fd < 0 ) {
		perror( "Couldn't initialize inotify");
	}

	 /* добавим наблюдение для директории, заданной первым параметром командной строки */
	wd = inotify_add_watch(fd, argv[1], IN_CREATE | IN_MODIFY | IN_DELETE);

	if (wd == -1)
	{
		printf("Couldn't add watch to %s\n",argv[1]);
	}
	else
	{
		printf("Watching:: %s\n",argv[1]);
	}

	/* бесконечный цикл*/
	while(1)
	{
		i = 0;
		length = read( fd, buffer, BUF_LEN );

		if ( length < 0 ) {
			perror( "read" );
		}

		while ( i < length ) {
			struct inotify_event *event = ( struct inotify_event * ) &buffer[ i ];
			if ( event->len ) {
				if ( event->mask & IN_CREATE) {
					if (event->mask & IN_ISDIR)
						printf( "The directory %s was Created.\n", event->name );
					else
						printf( "The file %s was Created with WD %d\n", event->name, event->wd );
				}

				if ( event->mask & IN_MODIFY) {
					if (event->mask & IN_ISDIR)
						printf( "The directory %s was modified.\n", event->name );
					else
						printf( "The file %s was modified with WD %d\n", event->name, event->wd );
				}

				if ( event->mask & IN_DELETE) {
					if (event->mask & IN_ISDIR)
						printf( "The directory %s was deleted.\n", event->name );
					else
						printf( "The file %s was deleted with WD %d\n", event->name, event->wd );
				}


					i += EVENT_SIZE + event->len;
			}
		}
	}

 /* Освобождение ресурсов*/
inotify_rm_watch( fd, wd );
close( fd );

return 0;
}
