/*app con BT para L298 // para pruebas 1 locomotora
*/




int Estado=2;
int estadoluz = 0; // estado LUZ
int const luz = 13; //Led pin 13
// Pines para el motor A
const int enA = 3;  // Pin PWM para controlar la velocidad del Motor A
const int in1 = 2;  // Pin para el control de dirección 1 del Motor A
const int in2 = 4;  // Pin para el control de dirección 2 del Motor A

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
void avanzar()
{
  
   digitalWrite(in1, HIGH); // Dirección 1 HIGH
  digitalWrite(in2, LOW);  // Dirección 2 LOW
    analogWrite(enA, 20);   // Velocidad máxima (0-255)
}
void avanzar2()
{
 
   digitalWrite(in1, HIGH); // Dirección 1 HIGH
  digitalWrite(in2, LOW);  // Dirección 2 LOW
    analogWrite(enA, 40);   // Velocidad máxima (0-255)
}
void avanzar3()
{

   digitalWrite(in1, HIGH); // Dirección 1 HIGH
  digitalWrite(in2, LOW);  // Dirección 2 LOW
   analogWrite(enA, 60);   // Velocidad máxima (0-255)
}
void avanzar4()
{

   digitalWrite(in1, HIGH); // Dirección 1 HIGH
  digitalWrite(in2, LOW);  // Dirección 2 LOW
    analogWrite(enA, 100);   // Velocidad máxima (0-255)
}

void retroceder()
{

 digitalWrite(in1, LOW);  // Dirección 1 LOW
  digitalWrite(in2, HIGH); // Dirección 2 HIGH
  analogWrite(enA, 20);   // Velocidad máxima (0-255)
}
void retroceder1()
{

 digitalWrite(in1, LOW);  // Dirección 1 LOW
  digitalWrite(in2, HIGH); // Dirección 2 HIGH
  analogWrite(enA, 40);   // Velocidad máxima (0-255)
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
      case 'F': forward(); delay(100); break;
      case 'B': backward();delay(100);  break;
      case 'S': Stop(); delay(100); break;
           case '9': iluminacion(); break;


        delay(20);
    }
  }
}

void loop() {
ControlBT ();

}
