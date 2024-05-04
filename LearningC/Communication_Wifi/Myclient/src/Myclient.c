/*------------------------------------------------------------------
RASPBERRY PI - ANDROID SMARTPHONE COMMUNICATION
===============================================
This is UDP program. The program receives and then sends messages to
a smartphone over the UDP socket. Program terminates when character x
is sent from the smartphone
This is the UDP client program, communicating over port 5000
Author: Dogan Ibrahim
File : MyClient.c
Date : December 2020
--------------------------------------------------------------------*/
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define Port 5000
#define BUFFSIZE 1024
//
// Start of MAIN program
//
int main(void)
{
int sock, len, num;
char buffer[BUFFSIZE];
struct sockaddr_in serveraddr;
char msg[] = "Hello from Raspberry Pi";
sock = socket(AF_INET, SOCK_DGRAM, 0);
serveraddr.sin_family = AF_INET;
serveraddr.sin_addr.s_addr = INADDR_ANY;
serveraddr.sin_port = htons(Port);
 while(1)
 {
 sendto(sock, &msg, strlen(msg), MSG_CONFIRM,
 (struct sockaddr *)&serveraddr, sizeof(serveraddr));
 num = recvfrom(sock, buffer, BUFFSIZE, MSG_WAITALL,
 (struct sockaddr *)&serveraddr, &len);
 if(buffer[0] == 'x')break;
 buffer[num] = '\0';
 printf("%s\n", buffer);
 }
close(sock);
}