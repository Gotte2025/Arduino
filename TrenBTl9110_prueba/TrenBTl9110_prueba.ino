#include <SoftwareSerial.h>

/*app con BT para L298 con 6 servos
*/

SoftwareSerial mySerial(8, 9); // RX, TX


int Estado = 1;
int estadoluz = 0; // estado LUZ
int const luz = 13; //Led pin 13
// Pines para el motor A
const int in1 = 5;  // Pin para el control de dirección 1 del Motor A
const int in2 = 6;  // Pin para el control de dirección 2 del Motor A
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




void Stop()
{

  analogWrite(in1, 0);
  analogWrite(in2, 0);

  Estado = 1;
}
void avanzar()
{

  analogWrite(in1, 130); // Dirección 1 HIGH
  analogWrite(in2, 0);  // Dirección 2 LOW

}
void avanzar2()
{

  analogWrite(in1, 180); // Dirección 1 HIGH
  analogWrite(in2, 0);  // Dirección 2 LOW

}
void avanzar3()
{

  analogWrite(in1, 220); // Dirección 1 HIGH
  analogWrite(in2, 0);  // Dirección 2 LOW

}
void avanzar4()
{

  analogWrite(in1, 250); // Dirección 1 HIGH
  analogWrite(in2, 0);  // Dirección 2 LOW

}

void retroceder1()
{

  analogWrite(in1, 0);  // Dirección 1 LOW
  analogWrite(in2, 230); // Dirección 2 HIGH

}

void retroceder()
{

  analogWrite(in1, 0);  // Dirección 1 LOW
  analogWrite(in2, 150); // Dirección 2 HIGH

}

void forward()
{
  Estado = Estado + 1;
  if ( Estado > 2) {
    Estado = 2;
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

  }
}



void setup() {
  mySerial.begin(9600);
Serial.begin(9600);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  pinMode(luz, OUTPUT);
 mySerial.println("Hello, world?");
}

void ControlBT () {
  if (mySerial.available() > 0)
  {
    command = mySerial.read();
    
    switch (command) {
//      case 'F': avanzar();  delay(100);  break;
//      case 'B': retroceder();delay(100);  break;
      case 'S': Stop(); delay(100); break;
      case '9': iluminacion(); break;
//        case 'A':  retroceder1(); delay(100); break;
//      case 'C':  retroceder(); delay(100); break;
//      case 'D':  avanzar(); delay(100); break;
//      case 'E':  avanzar2(); delay(100); break;
//      case 'G':  avanzar3(); delay(100); break;
//      case 'H':  avanzar4();delay(100); break;
  case 1:  retroceder1(); delay(100); break;
      case 2:  retroceder(); delay(100); break;
      case 4:  avanzar(); delay(100); break;
      case 5:  avanzar2(); delay(100); break;
      case 6:  avanzar3(); delay(100); break;
      case 7:  avanzar4();delay(100); break;

        delay(200);
    }
  }
}

void loop() {
  ControlBT ();
 Serial.print("Estado" );
  Serial.println(Estado);
Serial.println("command: ");
Serial.println(command);
delay(1000);
}
