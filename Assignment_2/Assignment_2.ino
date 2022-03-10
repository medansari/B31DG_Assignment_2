#include <Ticker.h> 

#define ERROR_PIN 23    // define error pins for task 8
#define Push_button 22  // define push button pin for task 2
#define SigB 21         // define signal b pin for task 1
#define SigG 15         // define signal generator pin for task 3
#define POT 14          // defining an analog potentiometer pin for task 4
#define exec_time 26    // defining execution time for task 4

const int numPOT_values = 4;    // size of the array for storing potentiometer values
int POT_Value[numPOT_values];   // readings from the POT input
int POT_index;                  // POT value indexing
int POT_total = 0;              // POT total
int POT_average = 0;            // POT average

int error_code = 0;            // inititialising error_code as an integer equal to 0
int buttonState;               // inititialising buttonState as an integer

unsigned long duration;           //inititialising duration as a unsigned long
unsigned long durationTotal;      //inititialising durationTotal as a unsigned long
int freq;                       //inititialising freq as a float 
 


Ticker Timer;           //intiallising ticker timer  
int ticks = 0;          // initiallising ticks iniatlly equal 0

void setup() 
{
  // assigning inputs and outputs for all the pins
  pinMode(ERROR_PIN, OUTPUT);
  pinMode(Push_button, INPUT);
  pinMode(SigB, OUTPUT);
  pinMode(exec_time, OUTPUT);
  pinMode(SigG, INPUT);
  pinMode(POT, INPUT);
  // initiallisng serial monitor at the baud rate of 9600
  Serial.begin(9600);
  // starting the ticker at 10ms periodically
  Timer.attach_ms(10, periodic_timer);

  // initiallising all potentiometer values to be 0
  for (int init_POT = 0; init_POT < numPOT_values; init_POT++){
    POT_Value[init_POT] = 0;
  }

}
//ticker function
void periodic_timer() 
{
  ticks++;      // incrementing ticker

//implementing task 1 at 67Hz
  if ((ticks % 1) == 0)
  {
    task1();
  }

//implementing task 2 at 5Hz
  if ((ticks % 20) == 0)
  {
    task2();
  }

//implementing task 3 at 1Hz
  if ((ticks % 100) == 0)
  {
    task3();
  }

//implementing task 4 and 5 at 24Hz
  if ((ticks % 4) == 0)
  {
    task4();
    task5();
  }

  //implementing task 6 at 10Hz
  if ((ticks % 10) == 0)
  {
    task6();
  }

  //implementing task 7 and 8 at 3Hz
  if ((ticks % 33) == 0)
  {
    task7();
    task8();
  }
 //implementing task 9 at 0.2Hz
 if ((ticks % 500) == 0)
    {
     task9();
     ticks = 0;     // setting the ticks equal to 0 after implementing task 9
    }
 }

void loop() 
{
}

// implementing function for task 1
void task1()
{
  digitalWrite(SigB, HIGH);   // setting signal b high
  delayMicroseconds(50);      // delay of 50 microseconds
  digitalWrite(SigB, LOW);    // setting signal b low
}

// implementing function for task 2
void task2()
{
  delayMicroseconds(2);                       // adding a delay for debouncing 
  buttonState = digitalRead(Push_button);     // read the state of the button
  delayMicroseconds(2);                       // adding a delay for debouncing 
}

// implementing function for task 3
void task3()
{
  duration = pulseIn(SigG, HIGH);         // reading in pulse duartion

// if the pulse duration is equal to 0 return 
  if (duration == 0)
  {
    return;
  }
  
  durationTotal = (duration*2);         // calculate the total duration
  freq = (1000000/(durationTotal));     // calculate the frequency 
}

// implementing function for task 4
void task4()
{
  digitalWrite(exec_time, HIGH);                        // checking execution time
  POT_total = POT_total - POT_Value[POT_index];         // subtracting from the pot_tatal
  POT_Value[POT_index] = analogRead(POT);               // storing the potentiometer values in the indexes 
  digitalWrite(exec_time, LOW);
}

// implementing function for task 5
void task5()
{
  // storing the total potentiometer value
  POT_total = POT_total + POT_Value[POT_index];      
  POT_index = POT_index + 1;                          
  if (POT_index >= numPOT_values)
  {
    POT_index = 0;
  } 
  POT_average = POT_total/numPOT_values;    //calculating POT average
}

// implementing function for task 6
void task6()
{
  // using for loop to implement following task 1000 times
  for (int i = 0; i<999; i++)
  {
    __asm__ __volatile__ ("nop");
  }
}

// implementing function for task 7
void task7()
{
  // using if statements to check error 
  if (POT_average>(4095/2))
  {
    error_code = 1; // setting error code to 1
  }
  else 
  {
    error_code = 0; // setting error code to 0
  }
}

// implementing function for task 8
void task8()
{
  if (error_code == 1)
  {
    digitalWrite(ERROR_PIN, HIGH);  // setting  led on when error code is 1
  }

  else
  {
    digitalWrite(ERROR_PIN, LOW);   // setting  led off otherwise
  }
}

// implementing function for task 9
void task9()
{
  // printing button state, frequency and pot average in a CSV format

  Serial.print(buttonState);  
  Serial.print(",");
  Serial.print(freq);
  Serial.print(",");
  Serial.println(POT_average);
}
