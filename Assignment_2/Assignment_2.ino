#include <Ticker.h>

#define ERROR_PIN 23
#define Push_button 22
#define SigB 21
#define SigG 15
#define POT 14
#define timer_pin 26

const int numPOT_values = 4;    // size of the array for storing potentiometer values
int POT_Value[numPOT_values];   // readings from the POT input
int POT_index;                  // POT value indexing
int POT_total = 0;              // POT total
int POT_average = 0;            // POT average

int error_code = 0;
int buttonState;

 unsigned long duration;
 unsigned long durationTotal;
 float freq;
 


 Ticker Timer;
 int ticks = 0;

void setup() 
{
  Timer.attach_ms(10, periodicPrint);
  pinMode(ERROR_PIN, OUTPUT);
  pinMode(Push_button, INPUT);
  pinMode(SigB, OUTPUT);
  pinMode(timer_pin, OUTPUT);
  pinMode(SigG, INPUT);
  pinMode(POT, INPUT);
  Serial.begin(9600);

  // initiallising all potentiometer values to be 0
  for (int init_POT = 0; init_POT < numPOT_values; init_POT++){
    POT_Value[init_POT] = 0;
  }

}

void periodicPrint() 
{
  ticks++;
  int task1_rate =(ticks % 1);
  int task2_rate =(ticks % 20);
  int task3_rate =(ticks % 100);
  int task4_5_rate =(ticks % 4);
  int task6_rate =(ticks % 10);
  int task7_8_rate =(ticks % 33);
  int task8_rate =(ticks % 33);
  int task9_rate =(ticks % 500);


if (task1_rate == 0)
{
  task1();
}

else if (task2_rate == 0)
{
  task2();
}

else if (task3_rate == 0)
{
  task3();
}

else if (task4_5_rate == 0)
{
  task4();
  task5();
}
else if (task6_rate == 0)
{
  task6();
}

else if (task7_8_rate == 0)
{
  task7();
  task8();
}

else if (task9_rate == 0)
{
  task9();
  ticks = 0;
}
  

}

void loop() 
{


}

void task1()
{
  digitalWrite(SigB, HIGH);
  delayMicroseconds(50);
  digitalWrite(SigB, LOW);
  delayMicroseconds(50);
}

void task2()
{
  delayMicroseconds(2);
  buttonState = digitalRead(Push_button);
  delayMicroseconds(2);
}

void task3()
{
  duration = pulseIn(SigG, HIGH);
  durationTotal = (duration*2);
  freq = (1000000/(durationTotal));
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
}

void task6()
{
  for (int i = 0; i<99; i++)
  {
    __asm__ __volatile__ ("nop");
  }
}

void task7()
{
  if (POT_average>(4095/2))
  {
    error_code = 1;
  }
  else 
  {
    error_code = 0;
  }
}

void task8()
{
  if (error_code == 1)
  {
    digitalWrite(ERROR_PIN, HIGH);
  }

  else
  {
    digitalWrite(ERROR_PIN, LOW);
  }
}

void task9()
{
  delay(1);
  Serial.println(".");
  Serial.print(buttonState);
  Serial.print(",");
  Serial.print(freq);
  Serial.print(",");
  Serial.print(POT_average);
  delay(1);
}
