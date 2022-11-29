#include <stdlib.h>
#include <stdio.h>
#include <librsync.h>


int main() {
  FILE *sig_file = NULL;
  FILE *new_file = NULL;
  FILE *delta_file = NULL;
  rs_stats_t stats;
  rs_result result;
  rs_signature_t *sumset;
  int file_force = 1;

  sig_file = rs_file_open("sig.sig", "rb", file_force);
  new_file = rs_file_open("new_file.txt", "rb", file_force);
  delta_file = rs_file_open("delta.delt", "wb", file_force);

  result = rs_loadsig_file(sig_file, &sumset, &stats);

  if ((result = rs_build_hash_table(sumset)) != RS_DONE)
        printf("Ошибка: %d", result);

  result = rs_delta_file(sumset, new_file, delta_file, &stats);

  rs_file_close(delta_file);
  rs_file_close(new_file);
  rs_file_close(sig_file);

  rs_free_sumset(sumset);

  printf("Result: %d\n", result);

  return 0;
}
