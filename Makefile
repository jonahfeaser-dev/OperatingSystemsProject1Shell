CC=gcc
CFLAGS=-Wall -Werror

all: wish

wish: main.o wish.o
	$(CC) $(CFLAGS) -o wish main.o wish.o

main.o: main.c wish.h
	$(CC) $(CFLAGS) -c main.c

wish.o: wish.c wish.h
	$(CC) $(CFLAGS) -c wish.c

clean:
	rm -f *.o wish

