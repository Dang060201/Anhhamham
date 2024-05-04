/*------------------------------------------------------------------
 RASPBERRY PI - WEB SERVER APPLICATION
 =====================================
This is a web server application. Two LEDs are connected to Raspberry Pi
and they are controlled remotely from a PC or a smartphone using web
server application.
Author: Dogan Ibrahim
File : WEBSERVER.c
Date : January 2021
--------------------------------------------------------------------*/
#include <wiringPi.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#define Port 80
#define BUFFSIZE 1024
//
// LED connections
//
#define LED0 21
#define LED1 20
//
// The HTML code. This code will display two buttons on user’s
// device which can be clicked to control the LEDs
//
char html[] ="<!DOCTYPE html>\n \
<html>\n \
<body>\n \
<center><h1>Raspberry Pi LED ON/OFF</h1></center>\n \
<center><h2>Web Server Example with 2 LEDs</h2></center>\n \
<form>\n \
<button name=\"LED0\" button style=\"color:green\" value=\"ON\" type=\"submit\">LED0 
ON</button>\n \
<button name=\"LED0\" button style=\"color=red\" value=\"OFF\" type=\"submit\">LED0 
OFF</button><br><br>\n \
<button name=\"LED1\" button style=\"color:green\" value=\"ON\" type=\"submit\">LED1 
ON</button>\n \
<button name=\"LED1\" button style=\"color:red\" value=\"OFF\" type=\"submit\">LED1 
OFF</button>\n \
</form></body></html>\n";
//
// COnfigure LED0 and LED1 as outputs and turn them OFF
//
void Configure()
{
pinMode(LED0, OUTPUT);
pinMode(LED1, OUTPUT);
digitalWrite(LED0, LOW);
digitalWrite(LED1, LOW); 
}
//
// Start of MAIN program. Inside the main program we send the
// HTML file so that it is displayed on user’s device. The user
// clicks the buttons to control the LEDs. We control the LEDs
// depending upon the key click. Variabl request holds the request
// and we search this string to see which LED should be turned
// ON/OFF. The contents of request is of the form (for example, to
// turn OFF LED0): "/?LED0=OFF", or similarly, to turn LED1 ON:
// "/?LED1=ON"
//
int main(void)
{
int sock, len, num, cli,flag = 1;
char buffer[BUFFSIZE];
struct sockaddr_in serveraddr, clientaddr;
wiringPiSetupGpio();
Configure();
sock = socket(AF_INET, SOCK_STREAM, 0);
len = sizeof(clientaddr);
bzero(&serveraddr, sizeof(serveraddr));
serveraddr.sin_family = AF_INET;
serveraddr.sin_addr.s_addr = INADDR_ANY;
serveraddr.sin_port = htons(Port);
bind(sock,(struct sockaddr *)&serveraddr, sizeof(serveraddr));
listen(sock, 5);
cli = accept(sock, NULL,NULL);
//
// Get reply from the HTTP and process it, send the html page
//
 while(1)
 {
 num = recv(cli, buffer, sizeof(buffer),0);
 buffer[num] = '\0';
 if(strstr(buffer,"LED0=ON"))digitalWrite(LED0, HIGH);
 if(strstr(buffer,"LED0=OFF"))digitalWrite(LED0, LOW);
 if(strstr(buffer,"LED1=ON"))digitalWrite(LED1, HIGH);
 if(strstr(buffer,"LED1=OFF"))digitalWrite(LED1, LOW);
 cli = accept(sock,NULL,NULL);
 send(cli,html,sizeof(html),0);
 }
}