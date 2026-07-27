
/*app con BT para L298 // para pruebas 3 locomotora
 
 Sistema de control por APP Bluethoot para controlar 3 locomotoras de modelismo ferroviarío.

 Octubre 2025

 G3D
*/



int VA1=80;
int VA2=110;
int VA3=210;
int VA4=230;
int VA5=254;
int VR1=80;
int VR2=190;
int Estado = 2;
int EstadoB = 2;
int EstadoC = 2;
int estadoluz = 0; // estado LUZ
int const luz = 13; //Led pin 13

// Pines para el motor A
const int enA = 3;  // Pin PWM para controlar la velocidad del Motor A
const int in1 = 2;  // Pin para el control de dirección 1 del Motor A
const int in2 = 4;  // Pin para el control de dirección 2 del Motor A
// Pines para el motor B
const int enB = 6;  // Pin PWM para controlar la velocidad del Motor B
const int in3 = 5;  // Pin para el control de dirección 1 del Motor B
const int in4 = 7;  // Pin para el control de dirección 2 del Motor B
// Pines para el motor C
const int enC = 9;  // Pin PWM para controlar la velocidad del Motor C
const int in5 = 8;  // Pin para el control de dirección 1 del Motor C
const int in6 = 10;  // Pin para el control de dirección 2 del Motor C

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
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(enA, 0);   // Velocidad máxima (0-255)
  Estado = 2;
}
void StopB()
{
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enB, 0);   // Velocidad máxima (0-255)
  EstadoB = 2;
}
void StopC()
{
  digitalWrite(in5, LOW);
  digitalWrite(in6, LOW);
  analogWrite(enC, 0);   // Velocidad máxima (0-255)
  EstadoC = 2;
}


void avanzar()
{

  digitalWrite(in1, HIGH); // Dirección 1 HIGH
  digitalWrite(in2, LOW);  // Dirección 2 LOW
  analogWrite(enA, VA1);   // Velocidad máxima (0-255)
}
void avanzarB()
{

  digitalWrite(in3, HIGH); // Dirección 1 HIGH
  digitalWrite(in4, LOW);  // Dirección 2 LOW
  analogWrite(enB, VA1);   // Velocidad máxima (0-255)
}
void avanzarC()
{

  digitalWrite(in5, HIGH); // Dirección 1 HIGH
  digitalWrite(in6, LOW);  // Dirección 2 LOW
  analogWrite(enC, VA1);   // Velocidad máxima (0-255)
}
void avanzar2()
{

  digitalWrite(in1, HIGH); // Dirección 1 HIGH
  digitalWrite(in2, LOW);  // Dirección 2 LOW
  analogWrite(enA, VA2);   // Velocidad máxima (0-255)
}
void avanzar2B()
{

  digitalWrite(in3, HIGH); // Dirección 1 HIGH
  digitalWrite(in4, LOW);  // Dirección 2 LOW
  analogWrite(enB, VA2);   // Velocidad máxima (0-255)
}
void avanzar2C()
{

  digitalWrite(in5, HIGH); // Dirección 1 HIGH
  digitalWrite(in6, LOW);  // Dirección 2 LOW
  analogWrite(enC, VA2);   // Velocidad máxima (0-255)
}
void avanzar3()
{

  digitalWrite(in1, HIGH); // Dirección 1 HIGH
  digitalWrite(in2, LOW);  // Dirección 2 LOW
  analogWrite(enA, VA3);   // Velocidad máxima (0-255)
}
void avanzar3B()
{

  digitalWrite(in3, HIGH); // Dirección 1 HIGH
  digitalWrite(in4, LOW);  // Dirección 2 LOW
  analogWrite(enB, VA3);   // Velocidad máxima (0-255)
}
void avanzar3C()
{

  digitalWrite(in5, HIGH); // Dirección 1 HIGH
  digitalWrite(in6, LOW);  // Dirección 2 LOW
  analogWrite(enC, VA3);   // Velocidad máxima (0-255)
}
void avanzar4()
{

  digitalWrite(in1, HIGH); // Dirección 1 HIGH
  digitalWrite(in2, LOW);  // Dirección 2 LOW
  analogWrite(enA, VA4);   // Velocidad máxima (0-255)
}
void avanzar4B()
{

  digitalWrite(in3, HIGH); // Dirección 1 HIGH
  digitalWrite(in4, LOW);  // Dirección 2 LOW
  analogWrite(enB, VA4);   // Velocidad máxima (0-255)
}
void avanzar4C()
{

  digitalWrite(in5, HIGH); // Dirección 1 HIGH
  digitalWrite(in6, LOW);  // Dirección 2 LOW
  analogWrite(enC,VA4);   // Velocidad máxima (0-255)
}
void avanzar5()
{

  digitalWrite(in1, HIGH); // Dirección 1 HIGH
  digitalWrite(in2, LOW);  // Dirección 2 LOW
  analogWrite(enA, VA5);   // Velocidad máxima (0-255)
}
void avanzar5B()
{

  digitalWrite(in3, HIGH); // Dirección 1 HIGH
  digitalWrite(in4, LOW);  // Dirección 2 LOW
  analogWrite(enB, VA5);   // Velocidad máxima (0-255)
}
void avanzar5C()
{

  digitalWrite(in5, HIGH); // Dirección 1 HIGH
  digitalWrite(in6, LOW);  // Dirección 2 LOW
  analogWrite(enC, VA5);   // Velocidad máxima (0-255)
}
void retroceder()
{

  digitalWrite(in1, LOW);  // Dirección 1 LOW
  digitalWrite(in2, HIGH); // Dirección 2 HIGH
  analogWrite(enA, VR1);   // Velocidad máxima (0-255)
}
void retrocederB()
{

  digitalWrite(in3, LOW);  // Dirección 1 LOW
  digitalWrite(in4, HIGH); // Dirección 2 HIGH
  analogWrite(enB, VR1);   // Velocidad máxima (0-255)
}
void retrocederC()
{

  digitalWrite(in5, LOW);  // Dirección 1 LOW
  digitalWrite(in6, HIGH); // Dirección 2 HIGH
  analogWrite(enC, VR1);   // Velocidad máxima (0-255)
}
void retroceder1()
{

  digitalWrite(in1, LOW);  // Dirección 1 LOW
  digitalWrite(in2, HIGH); // Dirección 2 HIGH
  analogWrite(enA, VR2);   // Velocidad máxima (0-255)
}
void retroceder1B()
{

  digitalWrite(in3, LOW);  // Dirección 1 LOW
  digitalWrite(in4, HIGH); // Dirección 2 HIGH
  analogWrite(enB, VR2);   // Velocidad máxima (0-255)
}
void retroceder1C()
{

  digitalWrite(in5, LOW);  // Dirección 1 LOW
  digitalWrite(in6, HIGH); // Dirección 2 HIGH
  analogWrite(enC, VR2);   // Velocidad máxima (0-255)
}


void forward()
{
  Estado = Estado + 1;
  if ( Estado > 7 ) {
    Estado = 7;
  }
  switch (Estado)
  {


    case 0:
      retroceder1();
      Serial.println("Motor 1 -avance Reversa2");
      break;

    case 1:
      retroceder();
      Serial.println("Motor 1 -avance Reversa1");
      break;

    case 2:
      Stop();
      Serial.println("Motor 1 -avance Stop");
      break;

    case 3:
      avanzar();
      Serial.println("Motor 1 -avance 1era");
      break;

    case 4:
      avanzar2();
      Serial.println("Motor 1 -avance 2da");
      break;

    case 5:
      avanzar3();
      Serial.println("Motor 1 -avance 3era");
      break;

    case 6:
      avanzar4();
      Serial.println("Motor 1 -avance 4ta");
      break;

 case 7:
      avanzar5();
      Serial.println("Motor 1 -avance 5ta");
      break;
  }
}
void forwardB()
{
  EstadoB = EstadoB + 1;
  if ( EstadoB > 7 ) {
    EstadoB = 7;
  }
  switch (EstadoB)
  {


    case 0:
      retroceder1B();
      Serial.println("Motor 2 - avance Reversa2");
      break;

    case 1:
      retrocederB();
      Serial.println("Motor 2 - avance Reversa1");
      break;

    case 2:
      StopB();
      Serial.println("Motor 2 - avance Stop");
      break;

    case 3:
      avanzarB();
      Serial.println("Motor 2 - avance 1era");
      break;

    case 4:
      avanzar2B();
      Serial.println("Motor 2 - avance 2da");
      break;

    case 5:
      avanzar3B();
      Serial.println("Motor 2 - avance 3era");
      break;

    case 6:
      avanzar4B();
      Serial.println("Motor 2 - avance 4ta");
      break;
 case 7:
      avanzar5B();
      Serial.println("Motor 2 - avance 5ta");
      break;

  }
}
void forwardC()
{
  EstadoC = EstadoC + 1;
  if ( EstadoC > 7 ) {
    EstadoC = 7;
  }
  switch (EstadoC)
  {


    case 0:
      retroceder1C();
      Serial.println("Motor 3 - avance Reversa2");
      break;

    case 1:
      retrocederC();
      Serial.println("Motor 3 - avance Reversa1");
      break;

    case 2:
      StopC();
      Serial.println("Motor 3 - avance Stop");
      break;

    case 3:
      avanzarC();
      Serial.println("Motor 3 - avance 1era");
      break;

    case 4:
      avanzar2C();
      Serial.println("Motor 3 - avance 2da");
      break;

    case 5:
      avanzar3C();
      Serial.println("Motor 3 - avance 3era");
      break;

    case 6:
      avanzar4C();
      Serial.println("Motor 3 - avance 4ta");
      break;
case 7:
      avanzar5C();
      Serial.println("Motor 3 - avance 5ta");
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
      Serial.println("Motor 1 - avance Reversa2");
      break;

    case 1:
      retroceder();
      Serial.println("Motor 1 - avance Reversa1");
      break;

    case 2:
      Stop();
      Serial.println("Motor 1 - avance Stop");
      break;

    case 3:
      avanzar();
      Serial.println("Motor 1 - avance 1era");
      break;

    case 4:
      avanzar2();
      Serial.println("Motor 1 - avance 2da");
      break;

    case 5:
      avanzar3();
      Serial.println("Motor 1 - avance 3era");
      break;

    case 6:
      avanzar4();
      Serial.println("Motor 1 - avance 4ta");
      break;
case 7:
      avanzar5();
      Serial.println("Motor 1 - avance 5ta");
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
      Serial.println("Motor 2 - avance Reversa2");
      break;

    case 1:
      retrocederB();
      Serial.println("Motor 2 - avance Reversa1");
      break;

    case 2:
      StopB();
      Serial.println("Motor 2 - avance Stop");
      break;

    case 3:
      avanzarB();
      Serial.println("Motor 2 - avance 1era");
      break;

    case 4:
      avanzar2B();
      Serial.println("Motor 2 - avance 2da");
      break;

    case 5:
      avanzar3B();
      Serial.println("Motor 2 - avance 3era");
      break;

    case 6:
      avanzar4B();
      Serial.println("Motor 2 - avance 4ta");
      break;

    case 7:
      avanzar5B();
      Serial.println("Motor 2 - avance 5ta");
      break;

  }
}

void backwardC()
{
  EstadoC = EstadoC - 1;
  if (EstadoC < 0 ) {
    EstadoC = 0;
  }
  switch (EstadoC)
  {
    case 0:
      retroceder1C();
      Serial.println("Motor 3 - avance Reversa2");
      break;

    case 1:
      retrocederC();
      Serial.println("Motor 3 - avance Reversa1");
      break;

    case 2:
      StopC();
      Serial.println("Motor 3 - avance Stop");
      break;

    case 3:
      avanzarC();
      Serial.println("Motor 3 - avance 1era");
      break;

    case 4:
      avanzar2C();
      Serial.println("Motor 3 - avance 2da");
      break;

    case 5:
      avanzar3C();
      Serial.println("Motor 3 - avance 3era");
      break;

    case 6:
      avanzar4C();
      Serial.println("Motor 3 - avance 4ta");
      break;

    case 7:
      avanzar5C();
      Serial.println("Motor 3 - avance 5ta");
      break;
  }
}



void setup() {

Serial.begin(9600);

  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
 pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
   pinMode(enC, OUTPUT);
  pinMode(in5, OUTPUT);
  pinMode(in6, OUTPUT);
  pinMode(luz, OUTPUT);
   digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(enA, 0);   // Velocidad máxima (0-255)
  Estado = 2;
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enB, 0);   // Velocidad máxima (0-255)
  EstadoB = 2;
    digitalWrite(in5, LOW);
  digitalWrite(in6, LOW);
  analogWrite(enC, 0);   // Velocidad máxima (0-255)
  EstadoC = 2;
}

void ControlBT () {

if (Serial.available() > 0)
  {
    command = Serial.read();
  
    switch (command) {
      case '9': iluminacion(); break;
            case 'F': forward(); delay(100); break;
            case 'B': backward();delay(100);  break;
      case 'S': Stop(); delay(100); break;
          case 'G': forwardB(); delay(100); break;
            case 'C': backwardB();delay(100);  break;
      case 'T': StopB(); delay(100); break;
         case 'H': forwardC(); delay(100); break;
            case 'D': backwardC();delay(100);  break;
      case 'U': StopC(); delay(100); break;
    
        delay(20);
    }
  }
}

void loop() {
  ControlBT ();
 
}
