CFLAGS = -Wall -Wextra
CC = gcc
VPATH = src:build:include
HBASE = /home/dangph/ProgrammingC/LearningC/DHT_Thingsboard_HTTP/include
HBASE1 = /usr/include
INCLUDE       = -I$(HBASE) -I$(HBASE1)
build/bin/main : DHT_Thingsboard_HTTP.o DHT22Lib.o
		mkdir build/bin
		$(CC) $(CFLAGS) $? -o $@  -lwiringPi -lcurl
build/DHT_Thingsboard_HTTP.o : DHT_Thingsboard_HTTP.c
		mkdir build
		$(CC) $(CFLAGS) -c $? -o $@ $(INCLUDE)
build/DHT22Lib.o : DHT22Lib.c
		$(CC) $(CFLAGS) -c $? -o $@ $(INCLUDE)

.PHONY = clean
clean :
		rm -rvf build


.PHONY = run
run: 
		./build/bin/main