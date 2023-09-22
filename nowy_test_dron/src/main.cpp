

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8);

const byte rxAddr[6] = "00001";

struct DataPacket {
  int pot1Value;
  int pot2Value;
  int pot3Value;
  

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
  packet.pot2Value = analogRead(A3);
  packet.pot3Value=analogRead(A4);
  //packet.button=digitalRead(2);
  
  radio.write(&packet, sizeof(DataPacket));
  
  Serial.print("Pot1: ");
  Serial.print(packet.pot1Value);
  Serial.print(" | Pot2: ");
  Serial.println(packet.pot2Value);
  Serial.println(packet.pot3Value);
  
  delay(100);
}


////////

///
/*

#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

RF24 radio(7, 8);
Servo esc3;
Servo esc5;
Servo esc9;
Servo esc10;

const byte rxAddr[6] = "00001";

struct DataPacket {
  int pot1Value;
  int pot2Value;
  int pot3Value;
 // int button;
};




void setup()
{

  esc3.attach(3,  1000, 2000);
    esc5.attach(5,  1000, 2000);
    esc9.attach(9,  1000, 2000);
    esc10.attach(10,  1000, 2000);

  esc3.write(0);
   esc5.write(0);
  esc9.write(0);
  esc10.write(0);
  delay(2000);
  radio.begin();
  radio.openReadingPipe(1, rxAddr);
  radio.startListening();
  pinMode(3,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(6,OUTPUT);
  //pinMode(2,INPUT_PULLUP);

  
  
  
}

void loop()
{
  if (radio.available())
  {
    DataPacket packet;
    radio.read(&packet, sizeof(DataPacket));
    
    int led1Value = map(packet.pot1Value, 0, 1023, 0, 255);
    int led2Value = map(packet.pot2Value, 0, 1023, 0, 255);
    int led3Value=map(packet.pot3Value,0,1023,0,255);
    if(packet.pot3Value>=0 && packet.pot3Value<523 )
    {
        esc3.write(led3Value);
      esc5.write(led3Value);
       esc9.write(led3Value);
        esc10.write(led3Value);
        analogWrite(6,led3Value);
    }
     else if(packet.pot3Value>=523 ){

     
     esc3.write(led1Value);
      esc5.write(led2Value);
       esc9.write(led2Value);
        esc10.write(led1Value);
        analogWrite(6,led1Value);
     }
    
   
  }
}

*/