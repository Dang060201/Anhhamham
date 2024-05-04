#include <wiringPi.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <DHT22Lib.h>
#define Port 80
#define URL_OF_THINGSPEAK "api.thingspeak.com"
#define DHT_PIN 2
unsigned long myChannelNumber=2525555;
//
// This function connects to Thingspeak Cloud Service and then reads
// and sends the aambient temperature and humidity to the Cloud where
// it is plotted in real time
//
void Send()
{
int sock,Temp,Hum;
struct sockaddr_in serveraddr;
struct hostent *ServerDetail;
char msg1[] = "GET /update?key=7BIEJKJ3PAN84T7M&field1=";
char msg2[3];
char msg3[] = "&field2=";
char msg4[3];
char msg5[] = " HTTP/1.0\r\nHost: api.thingspeak.com\r\n\r\n";
wiringPiSetupGpio();
delay(1000);
sock = socket(AF_INET, SOCK_STREAM, 0);
ServerDetail=gethostbyname(URL_OF_THINGSPEAK);
bzero((char *)&serveraddr, sizeof(serveraddr));
serveraddr.sin_family = AF_INET;
bcopy((char *)ServerDetail->h_addr_list[0],
      (char *)&serveraddr.sin_addr.s_addr,
      ServerDetail->h_length);
serveraddr.sin_port = htons(Port);
//
// Connect to Thingspeak Cloud Service, read the temperature and
// humidity into msg2 and msg4
//
connect(sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
Read_DHT22(&Temp, &Hum, DHT_PIN);
// Temp = 30;
// Hum = 60;
printf("T = %d, H = %d /n",Temp,Hum);
sprintf(msg2, "%d", Temp);
sprintf(msg4, "%d", Hum);
//
// Send the data to Thingspeak Cloud Service
//
write(sock, msg1, strlen(msg1));
write(sock, msg2, strlen(msg2));
write(sock, msg3, strlen(msg3));
write(sock, msg4, strlen(msg4));
write(sock, msg5, strlen(msg5));
delay(2000); 
close(sock);
}
//
// Main program. Call function Send to send the readings to Cloud
// every minute
//
int main(void)
{
while(1)
{
 Send();
 delay(60000);
}
}