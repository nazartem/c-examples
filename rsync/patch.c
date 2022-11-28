#include <stdlib.h>
#include <stdio.h>
#include <librsync.h>

int main() {
  /* patch BASIS [DELTA [NEWFILE]] */
  FILE *basis_file, *delta_file, *new_file;
  rs_stats_t stats;
  rs_result result;
  int file_force = 1;

  basis_file = rs_file_open("basis_file.txt", "rb", file_force);
  delta_file = rs_file_open("delta.delt", "rb", file_force);
  new_file = rs_file_open("new_file.txt", "wb", file_force);

  result = rs_patch_file(basis_file, delta_file, new_file, &stats);

  rs_file_close(new_file);
  rs_file_close(delta_file);
  rs_file_close(basis_file);

  printf("Result code: %d\n", result);

  return result;
}
