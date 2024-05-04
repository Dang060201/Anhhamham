CFLAGS = -Wall -Wextra
CC = gcc
VPATH = src:build:include: 
build/bin/main : mcp23s27.o
		mkdir build/bin
		$(CC) $(CFLAGS) $? -o $@  -lwiringPi
build/mcp23s27.o : mcp23s27.c
		mkdir build
		$(CC) $(CFLAGS) -c $? -o $@
# build/ssd1306.o : ssd1306_i2c.c
# 		$(CC) $(CFLAGS) -c $? -o $@



.PHONY = clean
clean :
		rm -rvf build


.PHONY = run
run: 
		./build/bin/main