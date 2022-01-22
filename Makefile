build:
	g++ cmatrix.c -lncurses -o cmatrixRadek

run: cmatrixRadek
	./cmatrixRadek