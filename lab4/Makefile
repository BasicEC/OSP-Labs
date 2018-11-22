CC=gcc
TARGET=wc
CFLAGS=-Wall -std=c99
SRC=$(wildcard *.c)
OBJ=$(SRC:%.c=%.o)

mainmake: $(OBJ)
	$(CC) -o $(TARGET) $(OBJ) 

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -rf *.o wc
