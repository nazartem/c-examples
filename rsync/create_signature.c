#include <stdlib.h>
#include <stdio.h>
#include <librsync.h>

int main() {
    FILE *basis_file = NULL;
    FILE *sig_file  = NULL;
    rs_stats_t stats;
    rs_result result;
    int block_len = 0;
    int strong_len = 0;
    int file_force = 1;
    rs_magic_number sig_magic = RS_BLAKE2_SIG_MAGIC;

    basis_file = rs_file_open("basis_file.txt", "rb", file_force);
    sig_file = rs_file_open("sig.sig", "wb", file_force);

    result = rs_sig_file(basis_file, sig_file, block_len, strong_len, sig_magic, &stats);

    rs_file_close(sig_file);
    rs_file_close(basis_file);

    printf("Result code: %d\n", result);

    return 0;
}
