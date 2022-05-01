
CC=gcc

CFLAGS=-g -Wall

all: mngstd

mngstd: main.o functions.o studentlist.o hashing.o yearnode.o
	$(CC) main.o functions.o studentlist.o hashing.o yearnode.o -o mngstd

main.o: main.c functions.h yearnode.h
	$(CC) $(CFLAGS) -c main.c 

function.o: functions.c
	$(CC) $(CFLAGS) -c functions.c

studentlist.o: studentlist.c
	$(CC) $(CFLAGS) -c studentlist.c

hashing.o: hashing.c
	$(CC) $(CFLAGS) -c hashing.c

yearnode.o: yearnode.c
	$(CC) $(CFLAGS) -c yearnode.c

clean:
	rm -f *.o mngstd





