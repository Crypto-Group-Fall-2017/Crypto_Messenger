# the compiler: gcc for C program, define as g++ for C++
CC = g++
GCC = gcc
# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CCFLAGS  = -g -Wall
CPFLAGS = -std=gnu++11
all: test

test: des_exp_perm.o p_box.o test.o
	$(CC) $(CFLAGS) $(CPFLAGS) -o test test.o des_exp_perm.o p_box.o

test.o: test.cpp
	$(CC) $(CFLAGS) $(CPFLAGS) -c test.cpp

p_box.o: p_box.cpp p_box.h
	$(CC) $(CFLAGS) $(CPFLAGS) -c p_box.cpp

des_exp_perm.o: des_exp_perm.cpp des_exp_perm.h
	$(CC) $(CFLAGS) $(CPFLAGS) -c des_exp_perm.cpp

clean:
	$(RM) test *.o *~
