#include <stdio.h>
#include <string.h>
#include <dirent.h>

int main(int argc, char **argv) {
  char str1[] = ".biorobot";
  char buf[255];
  DIR *dir;
  struct dirent *entry;

  if (argc < 2) {
    fprintf(stderr, "Too few arguments\n");
    return 1;
  }

  dir = opendir(argv[1]);
  if (dir == NULL) {
    fprintf(stderr, "opendir() error\n");
    return 1;
  }

  while ((entry = readdir(dir)) != NULL) {
    strcpy(buf, entry->d_name);
    if (strstr(buf, str1) != NULL) {
      printf("%s\n", entry->d_name);
    }
    // printf("%s\n", entry->d_name);

  }

  closedir(dir);
  return 0;
}
