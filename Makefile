CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic

all: RandWriter lint test

lint:
	cpplint --recursive --quiet src/

RandWriter: RandWriter.o main.o
	$(CC) $(CFLAGS) -o RandWriter RandWriter.o main.o

RandWriter.o: RandWriter.cpp RandWriter.hpp
	$(CC) $(CFLAGS) -c RandWriter.cpp

main.o: main.cpp RandWriter.hpp
	$(CC) $(CFLAGS) -c main.cpp

test: test.o RandWriter.o
	$(CC) $(CFLAGS) -o test test.o RandWriter.o -lboost_unit_test_framework

test.o: test.cpp RandWriter.hpp
	$(CC) $(CFLAGS) -c test.cpp

clean:
	rm *.o RandWriter test
