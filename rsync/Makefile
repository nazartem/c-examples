all : delta signature patch

delta : create_delta.c
	gcc -o delta create_delta.c -Wall -g -lrsync

signature : create_signature.c
	gcc -o signature create_signature.c -Wall -g -lrsync

patch : patch.c
	gcc -o patch patch.c -Wall -g -lrsync

clean:
	rm -f signature delta patch
