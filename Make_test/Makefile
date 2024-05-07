CFLAGS = -Wall -Wextra
CC = gcc
VPATH = src:build


build/bin/make_tutorial : main.o calculator.o greeter.o
		mkdir build/bin
		$(CC) $(CFLAGS) $? -o $@  -lwiringPi -pthread
build/main.o : main.c
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