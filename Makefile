CC = g++
CFLAGS= -g -Wall -std=c++0x

default: compile

compile: Main.o Perceptron.o Node.o readFile.o
	$(CC) $? -o nn

Main.o: Main.cpp
	$(CC) $(CFLAGS) -c $< -o $@

Perceptron.o: Perceptron.cpp Perceptron.h
	$(CC) $(CFLAGS) -c $< -o $@

Node.o: Node.cpp Node.h
	$(CC) $(CFLAGS) -c $< -o $@

readFile.o: readFile.cpp readFile.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) *.o *~ aco
