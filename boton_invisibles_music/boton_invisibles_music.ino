#include <anyrtttl.h>
#include <binrtttl.h>
#include <pitches.h>
const int EchoPin = 3;
const int TriggerPin = 2;
const int PinLed = 13;
int boton1mayor = 40;
int botona1menor = 30;
int contador=0; 
int cantidad=8;

int cm; 

//project's constants
#define BUZZER_PIN 9
//const char * tetris = "tetris:d=4,o=5,b=160:e6,8b,8c6,8d6,16e6,16d6,8c6,8b,a,8a,8c6,e6,8d6,8c6,b,8b,8c6,d6,e6,c6,a,2a,8p,d6,8f6,a6,8g6,8f6,e6,8e6,8c6,e6,8d6,8c6,b,8b,8c6,d6,e6,c6,a,a";
const char *Indiana = "Indiana:d=4,o=5,b=250:e,8p,8f,8g,8p,1c6,8p.,d,8p,8e,1f,p.,g,8p,8a,8b,8p,1f6,p,a,8p,8b,2c6,2d6,2e6,e,8p,8f,8g,8p,1c6,p,d6,8p,8e6,1f.6,g,8p,8g,e.6,8p,d6,8p,8g,e.6,8p,d6,8p,8g,f.6,8p,e6,8p,8d6,2c6";
const char *Simpsons = "The Simpsons:d=4,o=5,b=160:c.6,e6,f#6,8a6,g.6,e6,c6,8a,8f#,8f#,8f#,2g,8p,8p,8f#,8f#,8f#,8g,a#.,8c6,8c6,8c6,c6";
//const char *Bond = "Bond:d=4,o=5,b=80:32p,16c#6,32d#6,32d#6,16d#6,8d#6,16c#6,16c#6,16c#6,16c#6,32e6,32e6,16e6,8e6,16d#6,16d#6,16d#6,16c#6,32d#6,32d#6,16d#6,8d#6,16c#6,16c#6,16c#6,16c#6,32e6,32e6,16e6,8e6,16d#6,16d6,16c#6,16c#7,c.7,16g#6,16f#6,g#.6";
const char *Wilhelmu ="Wilhelmu:d=4,o=5,b=90:d,g,g,8a,8b,8c6,8a,b,8a,8b,c6,b,8a,8g,a,2g,p,d,g,g,8a,8b,8c6,8a,b,8a,8b,c6,b,8a,8g,a,2g,p,8b,8c6,2d6,e6,2d6,c6,b,8a,8b,c6,b,a,g,2a,p,d,8g,8f#,8g,8a,b,2a,g,f#,d,8e,8f#,g,g,f#,2g";
const char *GeorgeofthejungleTheme = "GeorgeofthejungleTheme:d=4,o=6,b=127:f5,p,p,c5,p,p,f5,p,f5,p,f5,a5,p,c,p,f5,p,f5,p,g5,g5,p,a5,p,p,p,f5,f5,f5,f5,g5,g5,p,f5,p,p,p,f";
const char *OneMoreT = "OneMoreT:d=16,o=5,b=125:4e,4e,4e,4e,4e,4e,8p,4d#.,4e,4e,4e,4e,4e,4e,8p,4d#.,4e,4e,4e,4e,4e,4e,8p,4d#.,4f#,4f#,4f#,4f#,4f#,4f#,8f#,4d#.,4e,4e,4e,4e,4e,4e,8p,4d#.,4e,4e,4e,4e,4e,4e,8p,4d#.,1f#,2f#";
const char *TakeOnMe = "TakeOnMe:d=4,o=4,b=160:8f#5,8f#5,8f#5,8d5,8p,8b,8p,8e5,8p,8e5,8p,8e5,8g#5,8g#5,8a5,8b5,8a5,8a5,8a5,8e5,8p,8d5,8p,8f#5,8p,8f#5,8p,8f#5,8e5,8e5,8f#5,8e5,8f#5,8f#5,8f#5,8d5,8p,8b,8p,8e5,8p,8e5,8p,8e5,8g#5,8g#5,8a5,8b5,8a5,8a5,8a5,8e5,8p,8d5,8p,8f#5,8p,8f#5,8p,8f#5,8e5,8e5";
//const char *Entertainer = "Entertainer:d=4,o=5,b=140:8d,8d#,8e,c6,8e,c6,8e,2c.6,8c6,8d6,8d#6,8e6,8c6,8d6,e6,8b,d6,2c6,p,8d,8d#,8e,c6,8e,c6,8e,2c.6,8p,8a,8g,8f#,8a,8c6,e6,8d6,8c6,8a,2d6";
//const char *Muppets = "Muppets:d=4,o=5,b=250:c6,c6,a,b,8a,b,g,p,c6,c6,a,8b,8a,8p,g.,p,e,e,g,f,8e,f,8c6,8c,8d,e,8e,8e,8p,8e,g,2p,c6,c6,a,b,8a,b,g,p,c6,c6,a,8b,a,g.,p,e,e,g,f,8e,f,8c6,8c,8d,e,8e,d,8d,c";
//const char *Xfiles = "Xfiles:d=4,o=5,b=125:e,b,a,b,d6,2b.,1p,e,b,a,b,e6,2b.,1p,g6,f#6,e6,d6,e6,2b.,1p,g6,f#6,e6,d6,f#6,2b.,1p,e,b,a,b,d6,2b.,1p,e,b,a,b,e6,2b.,1p,e6,2b.";
const char *Looney = "Looney:d=4,o=5,b=140:32p,c6,8f6,8e6,8d6,8c6,a.,8c6,8f6,8e6,8d6,8d#6,e.6,8e6,8e6,8c6,8d6,8c6,8e6,8c6,8d6,8a,8c6,8g,8a#,8a,8f";
const char *thCenFox = "20thCenFox:d=16,o=5,b=140:b,8p,b,b,2b,p,c6,32p,b,32p,c6,32p,b,32p,c6,32p,b,8p,b,b,b,32p,b,32p,b,32p,b,32p,b,32p,b,32p,b,32p,g#,32p,a,32p,b,8p,b,b,2b,4p,8e,8g#,8b,1c#6,8f#,8a,8c#6,1e6,8a,8c#6,8e6,1e6,8b,8g#,8a,2b";

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
//  Serial.print("Distancia: ");
//  Serial.println(cm);

 if( cm < boton1mayor && cm > botona1menor ){
  digitalWrite(PinLed, HIGH);
  delay(200);
  digitalWrite(PinLed, LOW);
  delay(200);
   contador++;
   Serial.print("contador: ");
   Serial.println(contador);
    if(contador > cantidad){
    contador = 0;
  }
  music();
 
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

void music(){
  

     switch (contador) {
    case 1:
    anyrtttl::blocking::play(BUZZER_PIN, Indiana);
      Serial.println("El valor es 1");
      break;
    case 2:
    anyrtttl::blocking::play(BUZZER_PIN, Simpsons);
      Serial.println("El valor es 2");
      break;
    case 3:
    anyrtttl::blocking::play(BUZZER_PIN, thCenFox);
      Serial.println("El valor es 3");
      break;
       case 4:
    anyrtttl::blocking::play(BUZZER_PIN, Looney);
      Serial.println("El valor es 4");
      break;
          case 5:
    anyrtttl::blocking::play(BUZZER_PIN, Wilhelmu);
      Serial.println("El valor es 5");
      break;
            case 6:
    anyrtttl::blocking::play(BUZZER_PIN, GeorgeofthejungleTheme);
      Serial.println("El valor es 6");
      break;
              case 7:
    anyrtttl::blocking::play(BUZZER_PIN, OneMoreT);
      Serial.println("El valor es 7");
      break;
                  case 8:
    anyrtttl::blocking::play(BUZZER_PIN, TakeOnMe);
      Serial.println("El valor es 8");
      break;
//                     case 9:
//    anyrtttl::blocking::play(BUZZER_PIN, Entertainer);
//      Serial.println("El valor es 9");
//      break;

                        
 
  }
    delay(50);
   
   
  
}
