CC=gcc
TARGET=wc
CFLAGS=-Wall -std=gnu99 -pedantic -Werror -Wextra
SRC=$(wildcard *.c)
OBJ=$(SRC:%.c=%.o)

mainmake: $(OBJ)
	$(CC) -o $(TARGET) $(OBJ) 

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -rf *.o wc
