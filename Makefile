build:
	g++ cmatrix.c -lncurses -o cmatrix

run: cmatrix
	./cmatrix