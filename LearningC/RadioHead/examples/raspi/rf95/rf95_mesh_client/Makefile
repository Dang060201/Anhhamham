# Makefile
# Example for RH_RF95 on Raspberry Pi
# Requires pigpio to be installed: http://abyz.me.uk/rpi/pigpio/

CC            = g++
CFLAGS        = -DRASPBERRY_PI -pthread
LIBS          = -lpigpio -lrt
RADIOHEADBASE = /home/dangph/Anhhamham/LearningC/RadioHead
HPATH		  = /home/dangph/Anhhamham/LearningC/RadioHead/RHutil_pigpio
INCLUDE       = -I$(RADIOHEADBASE) -I$(HPATH)

all: rf95_mesh_client

RasPi.o: $(RADIOHEADBASE)/RHutil_pigpio/RasPi.cpp
	$(CC) $(CFLAGS) -c $(RADIOHEADBASE)/RHutil_pigpio/RasPi.cpp $(INCLUDE)

rf95_mesh_client.o: rf95_mesh_client.cpp
	$(CC) $(CFLAGS) -c $(INCLUDE) $<

RH_RF95.o: $(RADIOHEADBASE)/RH_RF95.cpp
	$(CC) $(CFLAGS) -c $(INCLUDE) $<

RHMesh.o: $(RADIOHEADBASE)/RHMesh.cpp
	$(CC) $(CFLAGS) -c $(INCLUDE) $<

RHRouter.o: $(RADIOHEADBASE)/RHRouter.cpp
	$(CC) $(CFLAGS) -c $(INCLUDE) $<

RHReliableDatagram.o: $(RADIOHEADBASE)/RHReliableDatagram.cpp
	$(CC) $(CFLAGS) -c $(INCLUDE) $<

RHDatagram.o: $(RADIOHEADBASE)/RHDatagram.cpp
	$(CC) $(CFLAGS) -c $(INCLUDE) $<

RHHardwareSPI.o: $(RADIOHEADBASE)/RHHardwareSPI.cpp
	$(CC) $(CFLAGS) -c $(INCLUDE) $<

RHSPIDriver.o: $(RADIOHEADBASE)/RHSPIDriver.cpp
	$(CC) $(CFLAGS) -c $(INCLUDE) $<

RHGenericDriver.o: $(RADIOHEADBASE)/RHGenericDriver.cpp
	$(CC) $(CFLAGS) -c $(INCLUDE) $<

RHGenericSPI.o: $(RADIOHEADBASE)/RHGenericSPI.cpp
	$(CC) $(CFLAGS) -c $(INCLUDE) $<

rf95_mesh_client: rf95_mesh_client.o RH_RF95.o RHMesh.o RHRouter.o RHReliableDatagram.o RHDatagram.o RasPi.o RHHardwareSPI.o RHSPIDriver.o RHGenericDriver.o RHGenericSPI.o
	$(CC) $^ $(LIBS) -o rf95_mesh_client

.PHONY = clean
clean:
	rm -rf *.o rf95_mesh_client

.PHONY = run
run:
	sudo ./rf95_mesh_client