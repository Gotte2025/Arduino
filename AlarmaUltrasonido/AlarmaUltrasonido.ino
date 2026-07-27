#include <anyrtttl.h>
#include <binrtttl.h>
#include <pitches.h>
const int EchoPin = 3;
const int TriggerPin = 2;
const int PinLed = 13;
int boton1mayor = 10;
int botona1menor = 20;
int boton2mayor = 50;
int botona2menor = 40;
int boton3mayor = 70;
int botona3menor = 60;
int boton4mayor = 110;
int botona4menor = 100;
int cm; 

//project's constants
#define BUZZER_PIN 9
const char * tetris = "tetris:d=4,o=5,b=160:e6,8b,8c6,8d6,16e6,16d6,8c6,8b,a,8a,8c6,e6,8d6,8c6,b,8b,8c6,d6,e6,c6,a,2a,8p,d6,8f6,a6,8g6,8f6,e6,8e6,8c6,e6,8d6,8c6,b,8b,8c6,d6,e6,c6,a,a";
const char *Indiana = "Indiana:d=4,o=5,b=250:e,8p,8f,8g,8p,1c6,8p.,d,8p,8e,1f,p.,g,8p,8a,8b,8p,1f6,p,a,8p,8b,2c6,2d6,2e6,e,8p,8f,8g,8p,1c6,p,d6,8p,8e6,1f.6,g,8p,8g,e.6,8p,d6,8p,8g,e.6,8p,d6,8p,8g,f.6,8p,e6,8p,8d6,2c6";
const char *Simpsons = "The Simpsons:d=4,o=5,b=160:c.6,e6,f#6,8a6,g.6,e6,c6,8a,8f#,8f#,8f#,2g,8p,8p,8f#,8f#,8f#,8g,a#.,8c6,8c6,8c6,c6";
const char *Bond = "Bond:d=4,o=5,b=80:32p,16c#6,32d#6,32d#6,16d#6,8d#6,16c#6,16c#6,16c#6,16c#6,32e6,32e6,16e6,8e6,16d#6,16d#6,16d#6,16c#6,32d#6,32d#6,16d#6,8d#6,16c#6,16c#6,16c#6,16c#6,32e6,32e6,16e6,8e6,16d#6,16d6,16c#6,16c#7,c.7,16g#6,16f#6,g#.6";
void setup() {
  Serial.begin(9600);
  pinMode(TriggerPin, OUTPUT);
  pinMode(PinLed, OUTPUT);
   pinMode(BUZZER_PIN, OUTPUT);
  pinMode(EchoPin, INPUT);
   digitalWrite(PinLed, LOW);
}

void loop() {
  int cm = ping(TriggerPin, EchoPin);
  Serial.print("Distancia: ");
  Serial.println(cm);

 if( cm < boton1mayor && cm > botona1menor ){
   
  alarma();
}
 if( cm < boton2mayor && cm > botona2menor ){
   
  alarma2();
}
  

 if( cm < boton3mayor && cm > botona3menor ){
   
  alarma3();
}
 if( cm < boton4mayor && cm > botona4menor ){
   
  alarma4();
}
}

int ping(int TriggerPin, int EchoPin) {
  long duration, distanceCm;
  
  digitalWrite(TriggerPin, LOW);  //para generar un pulso limpio ponemos a LOW 4us
  delayMicroseconds(4);
  digitalWrite(TriggerPin, HIGH);  //generamos Trigger (disparo) de 10us
  delayMicroseconds(10);
  digitalWrite(TriggerPin, LOW);
  
  duration = pulseIn(EchoPin, HIGH);  //medimos el tiempo entre pulsos, en microsegundos
  
  distanceCm = duration * 10 / 292/ 2;   //convertimos a distancia, en cm
  return distanceCm;
}

void alarma(){
//         
//    anyrtttl::blocking::play(BUZZER_PIN, Indiana);
    digitalWrite(PinLed, HIGH);
analogWrite(BUZZER_PIN,200);
    
    delay(50);
   
    digitalWrite(PinLed, LOW);
    analogWrite(BUZZER_PIN, 0);
  
}
void alarma2(){
//         
//    anyrtttl::blocking::play(BUZZER_PIN, Bond);
    digitalWrite(PinLed, HIGH);
analogWrite(BUZZER_PIN,250);
    
    delay(100);
    
   
   
    digitalWrite(PinLed, LOW);
    analogWrite(BUZZER_PIN, 0);
  
}
void alarma3(){
//         
//    anyrtttl::blocking::play(BUZZER_PIN, Simpsons);
    digitalWrite(PinLed, HIGH);
analogWrite(BUZZER_PIN, 100);
    
       delay(300);
   
    digitalWrite(PinLed, LOW);
    analogWrite(BUZZER_PIN, 0);
  
}

void alarma4(){
//         
//    anyrtttl::blocking::play(BUZZER_PIN, Simpsons);
    digitalWrite(PinLed, HIGH);
analogWrite(BUZZER_PIN, 180);
    
    delay(200);
   
    digitalWrite(PinLed, LOW);
    analogWrite(BUZZER_PIN, 0);
  
}
