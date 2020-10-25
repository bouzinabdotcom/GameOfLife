all: main.o life.o
	gcc main.o life.o -o game-of-life
	make clean

life.o: life.c
	gcc -c life.c

main.o: main.c
	gcc -c main.c

clean: 
	rm -rf *.o