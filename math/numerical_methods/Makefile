integrate: integrate.o vector.o
	gcc vector.o integrate.o -o integrate -Wall

integrate.o: integrate.c
	gcc -c integrate.c

vector.o: ../vector/vector.c ../vector/vector.h
	gcc -c ../vector/vector.c