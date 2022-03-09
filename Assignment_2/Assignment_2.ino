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
 /* int task1_rate =;
  int task2_rate =;
  int task3_rate =;
  int task4_rate =;
  int task5_rate =;
  int task6_rate =;
  int task7_rate =;
  int task8_rate =;
  int task9_rate =;
  
  int rate = map(task1_rate, task2_rate, task3_rate, task4_rate,task5_rate, task6_rate, task7_rate, task8_rate, task9_rate, 0, 9);
  switch (rate)
  {
    case 0:
    task1();
    break:
    
    case 1:
    task2();
    break;

    case 2:
    task3();
    break:
    
    case 3:
    task4();
    break;

    case 4:
    task5();
    break:
    
    case 5:
    task6();
    break;

    case 6:
    task7();
    break:
    
    case 7:
    task8();
    break;

    case 8:
    task9();
    break:
    
    case 9:
    //No operation.
    break;
    
  }
*/}

void loop() 
{
 task3();

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