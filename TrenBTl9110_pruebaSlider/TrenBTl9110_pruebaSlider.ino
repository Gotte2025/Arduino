#include <SoftwareSerial.h>

/*app con BT para L298 con 6 servos
*/

SoftwareSerial BT(2,3 );
// El TX del módulo BT va al pin 2 del Arduino
// El RX del módulo BT va al pin 3 del Arduino


int Estado = 1;
int estadoluz = 0; // estado LUZ
int const luz = 13; //Led pin 13
// Pines para el motor A
const int in1 = 5;  // Pin para el control de dirección 1 del Motor A
const int in2 = 6;  // Pin para el control de dirección 2 del Motor A
int acelerar = 0;
int command=2; //Int to store app command state.


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
    BT.begin(9600);
Serial.begin(9600);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
command=2;
  pinMode(luz, OUTPUT);
 BT.println("Hello, world?");
}

void ControlBT () {
  if(BT.available() > 0){
    unsigned int x = BT.read();
      
  
//    command =map(x,0,99,0,6);
    command =x;
    switch (command) {
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
