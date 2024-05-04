CFLAGS = -Wall -Wextra
CC = gcc
VPATH = src:build:include: 
HPATH = /home/dangph/ProgrammingC/LearningC/OledPro/include
build/bin/main : demo.o ssd1306.o
		mkdir build/bin
		$(CC) $(CFLAGS) $? -o $@  -lwiringPi
build/demo.o : demo.c
		mkdir build
		$(CC) $(CFLAGS) -c $? -o $@ -I$(HPATH)
build/ssd1306.o : ssd1306_i2c.c
		$(CC) $(CFLAGS) -c $? -o $@ -I$(HPATH)



.PHONY = clean
clean :
		rm -rvf build


.PHONY = run
run: 
		./build/bin/main