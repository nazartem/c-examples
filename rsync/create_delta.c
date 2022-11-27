#include <stdlib.h>
#include <stdio.h>
#include "librsync.h"


int main(){
  FILE *sig_file, *new_file, *delta_file;
    char const *sig_name;
    rs_result result;
    rs_signature_t *sumset;

    FILE *fpb = NULL;
    fpb = fopen("fileb.txt", "r");

    FILE *fpd = NULL;
    fpd = fopen("delta.delt","w+");

    FILE *sigFile = NULL;
    sigFile = fopen("sig.sig","r");

    rs_signature_t *signature;

    rs_loadsig_file(sigFile, &signature, NULL);

    rs_result res = rs_build_hash_table(signature);

    res = rs_delta_file(signature, fpb, fpd, NULL);

    printf("Result: %d", res);

    fclose(fpb); fclose(fpd); fclose(sigFile);

    return 0;
}
