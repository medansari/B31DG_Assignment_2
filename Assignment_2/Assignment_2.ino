#include <Ticker.h>

#define ERROR_PIN 23
#define Push_button 22
#define SigB 21
#define SigG 15
#define POT 14

const int numPOT_values = 4;    // size of the array for storing potentiometer values
int POT_Value[numPOT_values];   // readings from the POT input
int POT_index;                  // POT value indexing
int POT_total = 0;              // POT total
int POT_average = 0;            // POT average



void setup() 
{
  pinMode(ERROR_PIN, OUTPUT);
  pinMode(Push_button, INPUT);
  pinMode(SigB, OUTPUT);
  pinMode(SigG, INPUT);
  pinMode(POT, INPUT);
  Serial.begin(9600);

  // initiallising all potentiometer values to be 0
  for (int init_POT = 0; init_POT < numPOT_values; init_POT++){
    POT_Value[init_POT] = 0;
  }

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

void task3()
{

}

void task4()
{
  POT_total = POT_total - POT_Value[POT_index];
  POT_Value[POT_index] = analogRead(POT);
}

void task5()
{
  POT_total = POT_total + POT_Value[POT_index];
  POT_index = POT_index + 1;

  if (POT_index >= numPOT_values)
  {
    POT_index = 0;
  } 
  POT_average = POT_total/numPOT_values;
  Serial.println(POT_average);
}