r:
	gcc subsetsum.c
	./a.out

debug:
	gcc -g subsetsum.c
	gdb ./a.out