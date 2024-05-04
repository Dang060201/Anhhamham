CFLAGS = -Wall -Wextra
CC = gcc
VPATH = src:build:include:/home/dangph/ProgrammingC/LearningC/RadioHead
HBASE = /home/dangph/ProgrammingC/LearningC/DHT_MQTT/include
HBASE1 = /usr/include
INCLUDE       = -I$(HBASE) -I$(HBASE1) 
build/bin/main : DHT_MQTT.o DHT22Lib.o
		mkdir build/bin
		$(CC) $(CFLAGS) $? -o $@  -lwiringPi -lpaho-mqtt3c
build/DHT_MQTT.o : DHT_MQTT.c
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