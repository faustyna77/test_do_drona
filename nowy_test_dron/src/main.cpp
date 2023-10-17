
#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

RF24 radio(7, 8);

Servo esc9;
const byte rxAddr[6] = "00001";
int pot1Value;
struct DataPacket
{
 int pot1Value;
};
DataPacket packet;

void resetData()
{
  pot1Value=0;
}
void setup()
{

esc9.attach(9);
delay(2000);
radio.begin();
  radio.openReadingPipe(1, rxAddr);
  radio.startListening();
  pinMode(9,OUTPUT);





  
}
unsigned long lastRecvTime = 0;
void recvData()
{
while ( radio.available() ) {
radio.read(&packet, sizeof(DataPacket));
lastRecvTime = millis(); //here we receive the data
}
}
void loop()
{

  recvData();
unsigned long now = millis();
//Here we check if we've lost signal, if we did we reset the values 
if ( now - lastRecvTime > 1000 ) {
// Signal lost?
resetData();


}
int led1Value = map(packet.pot1Value, 0, 1023, 1000, 2000);
    esc9.writeMicroseconds(led1Value);
}

/*

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8);

const byte rxAddr[6] = "00001";

struct DataPacket {
  int pot1Value;
 
  

};

void setup()
{
  while (!Serial);
  Serial.begin(9600);
  
  radio.begin();
  radio.openWritingPipe(rxAddr);
}

void loop()
{
  DataPacket packet;
  
  packet.pot1Value = analogRead(A2);
 
  //packet.button=digitalRead(2);
  
  radio.write(&packet, sizeof(DataPacket));
  
  Serial.print("Pot1: ");
  Serial.print(packet.pot1Value);

  
  delay(100);
}

*/
