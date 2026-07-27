/*app con BT para L298 con 6 servos 
*/


#include <Servo.h>            // Servo-adicionamos librería para servos

int Estado=1;
int estadoluz = 0; // estado LUZ
int const luz = 13; //Led pin 13
// Pines para el motor A
const int enA = 3;  // Pin PWM para controlar la velocidad del Motor A
const int in1 = 2;  // Pin para el control de dirección 1 del Motor A
const int in2 = 4;  // Pin para el control de dirección 2 del Motor A
int acelerar = 0;
int command; //Int to store app command state.


void iluminacion() {
  if (estadoluz == 0)
  {
    digitalWrite(luz, 1);
  }
  if ( estadoluz == 1)
  {
    digitalWrite(luz, 0);;
  }
  estadoluz = !estadoluz;

  delay(2);
}

void velocidad () {
  analogWrite(enA, acelerar);   // Velocidad máxima (0-255)
}


void Stop()
{
 acelerar = 0;
  
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  velocidad ();
  Estado = 1;
}
void avanzar()
{
  acelerar  = 30;
   digitalWrite(in1, HIGH); // Dirección 1 HIGH
  digitalWrite(in2, LOW);  // Dirección 2 LOW
    velocidad ();
}
void avanzar2()
{
  acelerar  = 90;
   digitalWrite(in1, HIGH); // Dirección 1 HIGH
  digitalWrite(in2, LOW);  // Dirección 2 LOW
    velocidad ();
}
void avanzar3()
{
 acelerar  = 150;
   digitalWrite(in1, HIGH); // Dirección 1 HIGH
  digitalWrite(in2, LOW);  // Dirección 2 LOW
    velocidad ();
}
void avanzar4()
{
 acelerar  = 240;
   digitalWrite(in1, HIGH); // Dirección 1 HIGH
  digitalWrite(in2, LOW);  // Dirección 2 LOW
    velocidad ();
}

void retroceder()
{
  acelerar  = 50;
 digitalWrite(in1, LOW);  // Dirección 1 LOW
  digitalWrite(in2, HIGH); // Dirección 2 HIGH
  velocidad ();
}

void forward()
{
  Estado = Estado + 1;
  if ( Estado > 5 ) {
    Estado = 5;
  }
  switch (Estado)
  {

    case 0:
      retroceder();
      Serial.println("avance Reversa");
      break;

    case 1:
      Stop();
      Serial.println("avance Stop");
      break;
    case 2:
      avanzar();
      Serial.println("avance 1era");
      break;
    case 3:
      avanzar2();
      Serial.println("avance 2da");
      break;
    case 4:
      avanzar3();
      Serial.println("avance 3era");
      break;
    case 5:
      avanzar4();
      Serial.println("avance 4ta");
      break;


  }
}

void backward()
{
  Estado = Estado - 1;
  if (Estado < 0 ) {
    Estado = 0;
  }
  switch (Estado)
  {

    case 0:
      retroceder();
      Serial.println("avance Reversa");
      break;

    case 1:
      Stop();
      Serial.println("avance Stop");
      break;
    case 2:
      avanzar();
      Serial.println("avance 1era");
      break;
    case 3:
      avanzar2();
      Serial.println("avance 2da");
      break;
    case 4:
      avanzar4();
      Serial.println("avance 3era");
      break;
    case 5:
      avanzar4();
      Serial.println("avance 4ta");
      break;

  }
}



void setup() {
  Serial.begin(9600);

  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
 
  pinMode(luz, OUTPUT);

}

void ControlBT () {
  if (Serial.available() > 0)
  {
    command = Serial.read();

    switch (command) {
      case 'F': forward();  break;
      case 'B': backward();  break;
      case 'S': Stop();  break;
           case '9': iluminacion(); break;


        delay(2);
    }
  }
}

void loop() {
ControlBT ();

}
