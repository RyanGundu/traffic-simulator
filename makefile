CC=gcc
CFLAGS=-std=c99 -pedantic -Wall -c -Iinclude

all: bin/main bin/testMain

bin/LinkedListAPI.o: src/LinkedListAPI.c
	$(CC) $(CFLAGS) src/LinkedListAPI.c -o bin/LinkedListAPI.o

bin/car.o: src/car.c
	$(CC) $(CFLAGS) src/car.c -o bin/car.o

bin/simulation.o: src/simulation.c
	$(CC) $(CFLAGS) src/simulation.c -o bin/simulation.o

bin/main.o: src/main.c
	$(CC) $(CFLAGS) src/main.c -o bin/main.o

bin/main: bin/main.o bin/LinkedListAPI.o bin/simulation.o bin/car.o
	$(CC) bin/main.o bin/LinkedListAPI.o bin/simulation.o bin/car.o -o bin/runMe 

bin/testMain.o: src/testMain.c
	$(CC) $(CFLAGS) src/testMain.c -o bin/testMain.o 

bin/testMain: bin/testMain.o bin/car.o bin/LinkedListAPI.o bin/simulation.o
	$(CC) bin/testMain.o bin/car.o bin/LinkedListAPI.o bin/simulation.o -o bin/runTest

run:
	./bin/runMe test.txt

runTest:
	./bin/runTest

clean:
	rm bin/*.o
	rm bin/runMe
	rm bin/runTest
	
