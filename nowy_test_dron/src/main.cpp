
#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

RF24 radio(7, 8);


Servo esc6;
Servo esc3;
Servo esc5;
Servo esc9;

const byte rxAddr[6] = "00001";

struct DataPacket
{
 int pot1Value;
 int pot2Value;
};
DataPacket packet;

void resetData()
{
  packet.pot1Value=0;
  packet.pot2Value=0;

}
void setup()
{


esc6.attach(6);
esc3.attach(3);
esc5.attach(5);
esc9.attach(9);
delay(2000);
radio.begin();
  radio.openReadingPipe(1, rxAddr);
  radio.startListening();

     pinMode(6,OUTPUT);
      pinMode(3,OUTPUT);
       pinMode(5,OUTPUT);
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
int led2Value = map(packet.pot2Value,0, 1023, 1000, 2000);

if(packet.pot1Value>523 && packet.pot2Value>523)
{
      esc6.writeMicroseconds(led1Value);
       esc9.writeMicroseconds(led1Value);
        esc5.writeMicroseconds(led2Value);
         esc3.writeMicroseconds(led2Value);
}else{
    esc6.writeMicroseconds(led1Value);
       esc9.writeMicroseconds(led1Value);
        esc5.writeMicroseconds(led1Value);
         esc3.writeMicroseconds(led1Value);
}
      
}

/*

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8);

const byte rxAddr[6] = "00001";

struct DataPacket {
  int pot1Value;
  int pot2Value;

 
  

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
  int pot3,pot4;
  
  packet.pot1Value = analogRead(A2);
  packet.pot2Value=analogRead(A1);
  pot3=analogRead(A3);
  pot4=analogRead(A4);
   if(pot3-pot4>30)
   {
    packet.pot1Value=packet.pot1Value+pot3;
    if(packet.pot1Value>1023)
    {
      packet.pot1Value=1023;
    }
   }
   else if(pot4-pot3>30)
   {
    packet.pot2Value=packet.pot2Value+pot4;
    if(packet.pot2Value>1023)
    {
      packet.pot2Value=1023;
    }
   }else 
   {
    packet.pot1Value=analogRead(A2);
    packet.pot2Value=analogRead(A1);

   }
  //packet.button=digitalRead(2);

  
  radio.write(&packet, sizeof(DataPacket));
  
  Serial.print("Pot1: ");
  Serial.print(packet.pot1Value);
  Serial.print(packet.pot2Value);

  
  delay(100);
}

*/
