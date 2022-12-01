  Use patterns:

  A typical application of the rsync algorithm is to transfer a file A2 from a machine A to a machine B which has a similar file A1. This can be done as follows:

  1) B generates the rdiff signature of A1. Call this S1. B sends the signature to A. (The signature is usually much smaller than the file it describes.)
  2) A computes the rdiff delta between S1 and A2. Call this delta D. A sends the delta to B.
  3) B applies the delta to recreate A2.

  In cases where A1 and A2 contain runs of identical bytes, rdiff should give a significant space saving.


  How to use librsync:

  1) call rs_sig_file to generate the signature of the original file (basis file);
  2) use rs_loadsig_file to load the signature in memory;
  3) use rs_build_hash_table on the signature;
  4) use rs_delta_file to generate the delta file of a new modified file;
  5) use rs_patch_file to recreate the new file from the basis file and the delta file.
