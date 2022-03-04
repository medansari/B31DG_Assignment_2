#include <Ticker.h>

#define ERROR_PIN 23
#define Push_button 22
#define SigB 21
#define SigG 15
#define Sensor 14



void setup() 
{
  pinMode(ERROR_PIN, OUTPUT);
  pinMode(Push_button, INPUT);
  pinMode(SigB, OUTPUT);
  pinMode(SigG, INPUT);
  pinMode(Sensor, INPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

}

void task1()
{
  digitalWrite(SigB, HIGH);
  delayMicroseconds(1300);
  digitalWrite(SigB, LOW);
}

void task2()
{
  int buttonState = digitalRead(Push_button);
  Serial.println(buttonState);
}

