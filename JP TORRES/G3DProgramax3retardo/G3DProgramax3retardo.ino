#include <Servo.h>

const int ServoPin = 9;
const int buttonPin = 12;

int buttonstate=0;
int directionState=0;

int ledr = 6;
int ledv = 5;

Servo barrera;
int pos = 0;

void setup() {
  barrera.attach(9);
  pinMode(buttonPin,INPUT);
  pinMode(ledr, OUTPUT);
  pinMode(ledv, OUTPUT);

}

void loop() {
  buttonstate=digitalRead(buttonPin);

  if( directionState==0){
    if(buttonstate==HIGH){
      directionState=1;

      for(pos = 0;pos<100;pos = pos+1)
     {
      digitalWrite(ledr, LOW);
      digitalWrite(ledv, HIGH);
      barrera.write(pos);
      delay(30);
       
     }
    }
  }
else if(directionState==1){
  if(buttonstate == HIGH)
  {
    
 directionState=0;
  for (pos=100;pos>=1; pos=pos-1)
  {
    digitalWrite(ledv, LOW);
      digitalWrite(ledr, HIGH);
      barrera.write(pos);
      delay(30);
  }
}
}
}
