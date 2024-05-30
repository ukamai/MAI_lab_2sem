CC = gcc
CFLAGS = -std=c99 --pedantic -Wall -g

all: main clean
        rm -f *.o

main: list.o main.o iterator.o
        $(CC) $^ -o $@

clean:
        rm -f *.o

cleanall:
        rm -f main *.o
