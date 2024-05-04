CFLAGS = -Wall -Wextra
CC = gcc
VPATH = src:build:include
HBASE = /home/dangph/ProgrammingC/LearningC/DHT/include
INCLUDE       = -I$(HBASE)
build/bin/main : Cloud.o 
# DHT22Lib.o
		mkdir build/bin
		$(CC) $(CFLAGS) $? -o $@  -lwiringPi
build/Cloud.o : Cloud.c
		mkdir build
		$(CC) $(CFLAGS) -c $? -o $@ $(INCLUDE)
# build/DHT22Lib.o : DHT22Lib.c
# 		$(CC) $(CFLAGS) -c $? -o $@ $(INCLUDE)

.PHONY = clean
clean :
		rm -rvf build


.PHONY = run
run: 
		./build/bin/main