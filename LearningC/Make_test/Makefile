CFLAGS = -Wall -Wextra
CC = gcc
VPATH = src:build


build/bin/make_tutorial : test.o calculator.o greeter.o
		mkdir build/bin
		$(CC) $(CFLAGS) $? -o $@  -lwiringPi
build/test.o : test.c
		mkdir build
		$(CC) $(CFLAGS) -c $? -o $@

build/calculator.o : calculator.c
		$(CC) $(CFLAGS) -c $? -o $@

build/greeter.o : greeter.c
		$(CC) $(CFLAGS) -c $? -o $@


.PHONY = clean
clean :
		rm -rvf build


.PHONY = run
run: 
		./build/bin/make_tutorial