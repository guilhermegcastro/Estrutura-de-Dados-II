
CC = gcc


CFLAGS = -I include -Wall

all:
	$(CC) src/*.c $(CFLAGS) -o programa

clean:
	rm -f programa
