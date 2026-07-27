
/*app con BT para L298 // para pruebas 1 locomotora
*/




int Estado = 2;
int EstadoB = 2;
int estadoluz = 0; // estado LUZ
int const luz = 13; //Led pin 13
int const luzVariable = 9; //Led command
// Pines para el motor A
const int enA = 3;  // Pin PWM para controlar la velocidad del Motor A
const int in1 = 2;  // Pin para el control de dirección 1 del Motor A
const int in2 = 4;  // Pin para el control de dirección 2 del Motor A
// Pines para el motor B
const int enB = 6;  // Pin PWM para controlar la velocidad del Motor A
const int in3 = 5;  // Pin para el control de dirección 1 del Motor B
const int in4 = 7;  // Pin para el control de dirección 2 del Motor B
int VMA1 = 0;
int VMA2 = 0;
int VMR1 = 0;
int VMR2 = 0;
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
void avanzar()
{

  digitalWrite(in1, HIGH); // Dirección 1 HIGH
  digitalWrite(in2, LOW);  // Dirección 2 LOW
  analogWrite(enA, VMA1);   // Velocidad máxima (0-255)
}
void avanzarB()
{

  digitalWrite(in3, HIGH); // Dirección 1 HIGH
  digitalWrite(in4, LOW);  // Dirección 2 LOW
  analogWrite(enB, VMA2);   // Velocidad máxima (0-255)
}

void retroceder()
{

  digitalWrite(in1, LOW);  // Dirección 1 LOW
  digitalWrite(in2, HIGH); // Dirección 2 HIGH
  analogWrite(enA, VMR1);   // Velocidad máxima (0-255)
}
void retrocederB()
{

  digitalWrite(in3, LOW);  // Dirección 1 LOW
  digitalWrite(in4, HIGH); // Dirección 2 HIGH
  analogWrite(enB, VMR2);   // Velocidad máxima (0-255)
}




void forward()
{
  VMA1 = VMA1 + 1;
   if ( VMA1 > 255 ) {
    VMA1 = 255;
    
  
  }
  avanzar();
  }
 
}
void forwardB()
{
  VMA2 = VMA2 + 1;
   if ( VMA2 > 255 ) {
    VMA2 = 255;
    
  
  }
  avanzarB();
  }
 
}

void backward()
{
    VMR1 = VMR1 - 1;
   if ( VMR1 > 0 ) {
    VMR1 = 0;
    
  
  }
  retroceder();
  }
}

void backwardB()
{
     VMR2 = VMR2 - 1;
   if ( VMR2 > 0 ) {
    VMR2 = 0;
    
  
  }
  retrocederB();
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
  pinMode(luz, OUTPUT);
   digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(enA, 0);   // Velocidad máxima (0-255)
  Estado = 2;
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enB, 0);   // Velocidad máxima (0-255)
  EstadoB = 2;
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
    
        delay(20);
    }
  }
}

void loop() {
  ControlBT ();
 
}
