#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

/*
RF24 radio(7, 8);

const byte rxAddr[6] = "00001";

struct DataPacket {
  int pot1Value;
  //int pot2Value;

 
  

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
  
  packet.pot1Value = map(analogRead(A4),0,1023,0,180);
 // packet.pot2Value=map(analogRead(A4),0,1023,0,180);;

 
  //packet.button=digitalRead(2);
  
  radio.write(&packet, sizeof(DataPacket));
  Serial.println(packet.pot1Value);
 
}


*/
/*
#include <Servo.h>

Servo ESC;     // create servo object to control the ESC

int potValue;  // value from the analog pin

void setup() {
  // Attach the ESC on pin 9
  ESC.attach(9,1000,2000); // (pin, min pulse width, max pulse width in microseconds) 
}

void loop() {
  potValue = analogRead(A2);   // reads the value of the potentiometer (value between 0 and 1023)
  potValue = map(potValue, 0, 1023, 0, 180);   // scale it to use it with the servo library (value between 0 and 180)
  ESC.write(potValue);    // Send the signal to the ESC
}
*/

/*


#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

RF24 radio(7, 8);

Servo esc10;
int current = 0; 
const byte rxAddr[6] = "00001";
const unsigned long responseTime = 5;

struct DataPacket {
  int pot1Value;
 
};




float lerp(float , float, float);

void setup()
{

 
    esc10.attach(10,  1000, 2000);


  delay(2000);
  radio.begin();
  radio.openReadingPipe(1, rxAddr);
  radio.startListening();
  pinMode(3,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(2,INPUT_PULLUP);
  esc10.write(current);
  
  
  
}

void loop()
{
  if (radio.available())
  {
    DataPacket packet;
  radio.read(&packet, sizeof(DataPacket));
    
    int led1Value = map(packet.pot1Value, 0, 1023, 0, 180);
   
 
        esc10.write(led1Value);
    
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
*/

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
