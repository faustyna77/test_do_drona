
#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

RF24 radio(7, 8);

Servo esc9;
int current = 0; 

const unsigned long responseTime = 50;

const byte rxAddr[6] = "00001";

struct DataPacket {
  int pot1Value;

 // int button;
};


float lerp(float , float, float);

void setup()
{

 
    esc9.attach(9,  1000, 2000);
    

 
  

  delay(2000);
  radio.begin();
  radio.openReadingPipe(1, rxAddr);
  radio.startListening();
  pinMode(9,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(2,INPUT_PULLUP);
  esc9.writeMicroseconds(current);
  //pinMode(2,INPUT_PULLUP);

  
  
  
}

void loop()
{
  if (radio.available())
  {
    DataPacket packet;
    radio.read(&packet, sizeof(DataPacket));
    
    int led1Value = map(packet.pot1Value, 0, 1023, 1000, 2000);
    esc9.writeMicroseconds(led1Value);
    for (unsigned long startTime = millis(); millis() - startTime < responseTime;)
    {
      float progress = static_cast<float>(millis() - startTime) / responseTime;
      current = static_cast<int>(lerp(current, led1Value, progress));
    
    

      
      //analogWrite(6, currentLed3Value);
    }
   
    
   
  }
}
float lerp(float start, float end, float progress)
{
  return start + (end - start) * progress;
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
