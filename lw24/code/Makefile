main: main.o tools.o tree.o deque.o str.o
	gcc -o main main.o tools.o

main.o:
	gcc --std=c99 --pedantic -Wall -c main.c

tools.o:
	gcc --std=c99 --pedantic -Wall -c tools.c

tree.o:
	gcc --std=c99 --pedantic -Wall -c tree.c

deque.o:
	gcc --std=c99 --pedantic -Wall -c deque.c

str.o:
	gcc --std=c99 --pedantic -Wall -c str.c

clean:
	rm main main.o tools.o tree.o deque.o str.o
