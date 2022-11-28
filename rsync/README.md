How to use librsync

1) call rs_sig_file to generate the signature of the original file (basis file);
2) use rs_loadsig_file to load the signature in memory;
3) use rs_build_hash_table on the signature;
4) use rs_delta_file to generate the delta file of a new modified file;
5) use rs_patch_file to generate the new file from the basis file and the delta file.
