#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
  int i = 1;
  char buf[512] = "\0";
  char tty[128] = "\0";
  FILE *cmd_pipe = popen("who | awk '{print $2}'", "r");

  while (!feof(cmd_pipe)) {
    if (fgets(buf, 512, cmd_pipe) != NULL) {
      buf[strcspn(buf, "\n")] = 0;
      strcat(tty, buf);
    }
  }

  pclose(cmd_pipe);

  for (i; i < 8; i++) {
    sprintf(buf, "tty%d", i);
    if (strstr(tty, buf) == NULL) {
      printf("Обработка %s\n", buf);
    }
  }

  return 0;
}
