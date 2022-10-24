#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <stdlib.h>
#include <ftw.h>

int rmFiles(const char *pathname, const struct stat *sbuf, int type, struct FTW *ftwb) {
  if (remove(pathname) < 0) {
    perror("ERROR: remove");
    return -1;
    }

    return 0;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr,"usage: %s path\n",argv[0]);
    exit(1);
  }

  // Delete the directory and its contents by traversing the tree in reverse order, without crossing mount boundaries and symbolic links
  if (nftw(argv[1], rmFiles, 10, FTW_DEPTH | FTW_MOUNT | FTW_PHYS) < 0) {
    perror("ERROR: ntfw");
    exit(1);
  }

  return 0;
}
