CC = gcc
CFLAGS=-Wall -Werror

all: wish

wish: main.o wish.o commands.o
	$(CC) $(CFLAGS) -o wish main.o wish.o commands.o

main.o: main.c wish.h
	$(CC) $(CFLAGS) -c main.c

wish.o: wish.c wish.h
	$(CC) $(CFLAGS) -c wish.c

commands.o: commands.c commands.h
	$(CC) $(CFLAGS) -c commands.c

clean:
	rm -f *.o wish
