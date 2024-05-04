// Author: Dogan Ibrahim
// File : MyServer.c
// Date : December 2020
// --------------------------------------------------------------------*/
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
int sock, len, num, count = 1;
char buffer[BUFFSIZE];
struct sockaddr_in serveraddr, clientaddr;
char msg[26] = "Hello from Raspberry Pi ";
sock = socket(AF_INET, SOCK_DGRAM, 0);
len = sizeof(clientaddr);
serveraddr.sin_family = AF_INET;
serveraddr.sin_addr.s_addr = INADDR_ANY;
serveraddr.sin_port = htons(Port);
bind(sock,(struct sockaddr *)&serveraddr, sizeof(serveraddr));
 while(1)
 {
 num = recvfrom(sock, buffer, BUFFSIZE,MSG_WAITALL,
 ( struct sockaddr *)&clientaddr, &len);
 if(buffer[0] == 'x')break;
 buffer[num] = '\0';
 printf("%s\n",buffer);
 sprintf(&msg[24], "%d",count);
 count++;
 sendto(sock, &msg, strlen(msg), MSG_CONFIRM,
 (struct sockaddr *)&clientaddr, len);
 }
close(sock);
}