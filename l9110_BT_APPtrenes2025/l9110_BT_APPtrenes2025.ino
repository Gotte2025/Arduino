#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX
/*app con BT para L298 // para pruebas 1 locomotora
*/


const int AIA = 6;  // (pwm) pin 6 conectado a pin A-IA
const int AIB = 5;  // (pwm) pin 5 conectado a pin A-IB
const int BIA = 10; // (pwm) pin 10 conectado a pin B-IA
const int BIB = 9;  // (pwm) pin 9 conectado a pin B-IB

int Estado = 2;
int EstadoB = 2;
int estadoluz = 0; // estado LUZ
int const luz = 13; //Led pin 13

int command; //Int to store app command state.


void Stop()
{

  analogWrite(AIA, 0);
  analogWrite(AIB, 0);
  analogWrite(BIA, 0);
  analogWrite(BIB, 0);
  Estado = 2;
}
void StopB()
{

  analogWrite(AIA, 0);
  analogWrite(AIB, 0);
  analogWrite(BIA, 0);
  analogWrite(BIB, 0);
  EstadoB = 2;
}
void avanzar()
{

  analogWrite(AIA, 0);
  analogWrite(AIB, 110);
  analogWrite(BIA, 0);
  analogWrite(BIB, 110);
}
void avanzarB()
{

  analogWrite(AIA, 0);
  analogWrite(AIB, 110);
  analogWrite(BIA, 0);
  analogWrite(BIB, 110);
}
void avanzar2()
{

  analogWrite(AIA, 0);
  analogWrite(AIB, 150);
  analogWrite(BIA, 0);
  analogWrite(BIB, 150);
}
void avanzar2B()
{

  analogWrite(AIA, 0);
  analogWrite(AIB, 150);
  analogWrite(BIA, 0);
  analogWrite(BIB, 150);
}
void avanzar3()
{
  analogWrite(AIA, 0);
  analogWrite(AIB, 190);
  analogWrite(BIA, 0);
  analogWrite(BIB, 190);
}
void avanzar3B()
{
  analogWrite(AIA, 0);
  analogWrite(AIB, 190);
  analogWrite(BIA, 0);
  analogWrite(BIB, 190);
}
void avanzar4()
{

  analogWrite(AIA, 0);
  analogWrite(AIB, 255);
  analogWrite(BIA, 0);
  analogWrite(BIB, 255);
}
void avanzar4B()
{
  analogWrite(AIA, 0);
  analogWrite(AIB, 255);
  analogWrite(BIA, 0);
  analogWrite(BIB, 255);
}
void retroceder()
{

  analogWrite(AIA, 110);
  analogWrite(AIB, 0);
  analogWrite(BIA, 110);
  analogWrite(BIB, 0);
}
void retrocederB()
{

  analogWrite(AIA, 110);
  analogWrite(AIB, 0);
  analogWrite(BIA, 110);
  analogWrite(BIB, 0);
}
void retroceder1()
{
  analogWrite(AIA, 150);
  analogWrite(AIB, 0);
  analogWrite(BIA, 150);
  analogWrite(BIB, 0);
}
void retroceder1B()
{
  analogWrite(AIA, 150);
  analogWrite(AIB, 0);
  analogWrite(BIA, 150);
  analogWrite(BIB, 0);
}


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



void forward()
{
  Estado = Estado + 1;
  if ( Estado > 6 ) {
    Estado = 6;
  }
  switch (Estado)
  {


    case 0:
      retroceder1();
      Serial.println("avance Reversa2");
      break;

    case 1:
      retroceder();
      Serial.println("avance Reversa1");
      break;

    case 2:
      Stop();
      Serial.println("avance Stop");
      break;

    case 3:
      avanzar();
      Serial.println("avance 1era");
      break;

    case 4:
      avanzar2();
      Serial.println("avance 2da");
      break;

    case 5:
      avanzar3();
      Serial.println("avance 3era");
      break;

    case 6:
      avanzar4();
      Serial.println("avance 4ta");
      break;


  }
}
void forwardB()
{
  EstadoB = EstadoB + 1;
  if ( EstadoB > 6 ) {
    EstadoB = 6;
  }
  switch (EstadoB)
  {


    case 0:
      retroceder1B();
      Serial.println("avance Reversa2");
      break;

    case 1:
      retrocederB();
      Serial.println("avance Reversa1");
      break;

    case 2:
      StopB();
      Serial.println("avance Stop");
      break;

    case 3:
      avanzarB();
      Serial.println("avance 1era");
      break;

    case 4:
      avanzar2B();
      Serial.println("avance 2da");
      break;

    case 5:
      avanzar3B();
      Serial.println("avance 3era");
      break;

    case 6:
      avanzar4B();
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
      retroceder1();
      Serial.println("avance Reversa2");
      break;

    case 1:
      retroceder();
      Serial.println("avance Reversa1");
      break;

    case 2:
      Stop();
      Serial.println("avance Stop");
      break;

    case 3:
      avanzar();
      Serial.println("avance 1era");
      break;

    case 4:
      avanzar2();
      Serial.println("avance 2da");
      break;

    case 5:
      avanzar3();
      Serial.println("avance 3era");
      break;

    case 6:
      avanzar4();
      Serial.println("avance 4ta");
      break;


  }
}

void backwardB()
{
  EstadoB = EstadoB - 1;
  if (EstadoB < 0 ) {
    EstadoB = 0;
  }
  switch (EstadoB)
  {
    case 0:
      retroceder1B();
      Serial.println("avance Reversa2");
      break;

    case 1:
      retrocederB();
      Serial.println("avance Reversa1");
      break;

    case 2:
      StopB();
      Serial.println("avance Stop");
      break;

    case 3:
      avanzarB();
      Serial.println("avance 1era");
      break;

    case 4:
      avanzar2B();
      Serial.println("avance 2da");
      break;

    case 5:
      avanzar3B();
      Serial.println("avance 3era");
      break;

    case 6:
      avanzar4B();
      Serial.println("avance 4ta");
      break;


  }
}


void setup() {
  mySerial.begin(9600);
  Serial.begin(9600);
  pinMode(AIA, OUTPUT); // fijar los pines como salidas
  pinMode(AIB, OUTPUT);
  pinMode(BIA, OUTPUT);
  pinMode(BIB, OUTPUT);
  pinMode(luz, OUTPUT);
}

void ControlBT () {
  if (mySerial.available() > 0)
  {
    command = mySerial.read();

    switch (command) {
      case '9': iluminacion(); break;
      case 'F': forward(); delay(100); break;
      case 'B': backward(); delay(100);  break;
      case 'S': Stop(); delay(100); break;
      case 'G': forwardB(); delay(100); break;
      case 'C': backwardB(); delay(100);  break;
      case 'T': StopB(); delay(100); break;

        delay(20);
    }
  }
}
void loop() {
  ControlBT ();

  delay(100);
}
