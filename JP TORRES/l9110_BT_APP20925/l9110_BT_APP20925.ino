/*
  L9110 motor driver controlando 2 motores CC
  COPIAR Y PEGAR SOBRE EL SKETCH DE ARDUINO
*/

const int AIA = 6;  // (pwm) pin 6 conectado a pin A-IA
const int AIB = 5;  // (pwm) pin 5 conectado a pin A-IB
const int BIA = 10; // (pwm) pin 10 conectado a pin B-IA
const int BIB = 9;  // (pwm) pin 9 conectado a pin B-IB
int Estado = 1;
int velocidad = 0;
// cambie este valor (100 a 255) para controlar
// la velocidad de los motores

int estadoluz = 0; // estado LUZ
int const luz = 13; //Led pin 13

int command; //Int to store app command state.

void avanzar()
{
  velocidad = 150;
  analogWrite(AIA, velocidad);
  analogWrite(AIB, 0);
  analogWrite(BIA, 0);
  analogWrite(BIB, velocidad);
}
void avanzar2()
{
  velocidad = 200;
  analogWrite(AIA, velocidad);
  analogWrite(AIB, 0);
  analogWrite(BIA, 0);
  analogWrite(BIB, velocidad);
}
void avanzar3()
{
  velocidad = 220;
  analogWrite(AIA, velocidad);
  analogWrite(AIB, 0);
  analogWrite(BIA, 0);
  analogWrite(BIB, velocidad);
}
void avanzar4()
{
  velocidad = 255;
  analogWrite(AIA, velocidad);
  analogWrite(AIB, 0);
  analogWrite(BIA, 0);
  analogWrite(BIB, velocidad);
}

void retroceder()
{
  velocidad = 150;
  analogWrite(AIA, 0);
  analogWrite(AIB, velocidad);
  analogWrite(BIA, velocidad);
  analogWrite(BIB, 0);
}



void Stop()
{
  velocidad = 0;
  analogWrite(AIA, 0);
  analogWrite(AIB, 0);
  analogWrite(BIA, 0);
  analogWrite(BIB, 0);
  Estado = 1;
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
  pinMode(AIA, OUTPUT); // fijar los pines como salidas
  pinMode(AIB, OUTPUT);
  pinMode(BIA, OUTPUT);
  pinMode(BIB, OUTPUT);
  pinMode(luz, OUTPUT);
}
void ControlBT () {

}
void loop() {
  if (Serial.available() > 0)
  {
    command = Serial.read();

    switch (command) {
      case 'F': forward();  break;
      case 'B': backward();  break;
      case 'S': Stop();  break;
      case '9': iluminacion(); break;


        delay(20);
    }
  }
  delay(100);
}
