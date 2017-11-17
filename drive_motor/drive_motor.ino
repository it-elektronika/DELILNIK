#include <ARDBOX-Analog.h>


const int stepPin = 9;
const int enPin = 6; 
const int dirPin = 5;


const int numberOfPulsesPerTurn = 400;
const int pauseThreshold = 400;
int numberOfPulses;
int numberOfTurns;

int pause;
int pauseLow;

int task;
char button;
char home_switch;
char end_switch;

void setup() 
{
  // Sets the two pins as Outputs
  pinMode(stepPin,OUTPUT);
  pinMode(enPin,OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(button, INPUT);
  pinMode(home_switch, INPUT);
  pinMode(end_switch, INPUT);

  
  numberOfTurns = 1;
  numberOfPulses = numberOfPulsesPerTurn * numberOfTurns;
  pause = (numberOfPulses / 2) + pauseThreshold;
  
  
  //digitalWrite(enPin,HIGH); 
  Serial.begin(9600);
}


void loop() 
{
  int i;
  int pulseCount = 0;
  int pulseCountAcc = 0;
  int pulseCountDec = 0;
  
  button = digitalRead(I0_9);
  
  if(button==HIGH)
  {
    delay(1000);
    task = 1;
    
    for(i = 0; i < numberOfPulses; i++)
    { 
      home_switch = digitalRead(I0_8);
      end_switch = digitalRead(I0_7);
      
      if(home_switch == HIGH || end_switch == HIGH)
      {
        digitalWrite(enPin,HIGH);    
      }
      if(task == 1)
      {
        digitalWrite(dirPin, HIGH);
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(3);
        digitalWrite(stepPin, LOW);
        pause = pause - 1;
        delayMicroseconds(pause);
        pulseCount++;
        pulseCountAcc++;
        
        if(pause == pauseThreshold)
        {
          task = 2;
          continue;
        }
      }

      if(task == 2)
      {
        
        digitalWrite(dirPin, HIGH);
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(3);
        digitalWrite(stepPin, LOW); 
        pause = pause + 1;
        delayMicroseconds(pause);
        pulseCount++;
        pulseCountDec++;
      }
    } 
    Serial.println(pulseCountAcc);
    Serial.println(pulseCountDec);
    Serial.println(pulseCount); 
 }
}




