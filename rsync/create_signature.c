#include <stdlib.h>
#include <stdio.h>
#include "librsync.h"

int main() {
    FILE *basis_file = NULL;
    FILE *sig_file  = NULL;
    rs_stats_t stats;
    rs_result result;
    rs_magic_number sig_magic;

    basis_file = rs_file_open("basis_file.txt", "rb", 1);
    sig_file = rs_file_open("sig.sig", "wb", 1);

    result = rs_sig_file(basis_file, sig_file, 1, 6, 0, &stats);

    rs_file_close(sig_file);
    rs_file_close(basis_file);

    // if (show_stats)
    //     rs_log_stats(&stats);

    printf("Result code: %d\n", result);

    return 0;
}
