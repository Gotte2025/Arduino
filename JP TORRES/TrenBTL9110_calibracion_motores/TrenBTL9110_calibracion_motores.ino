




int Estado = 2;
int EstadoB = 2;
int estadoluz = 0; // estado LUZ
int const luz = 13; //Led pin 13

const int AIA = 6;  // (pwm) pin 6 conectado a pin A-IA
const int AIB = 5;  // (pwm) pin 5 conectado a pin A-IB
const int BIA = 10; // (pwm) pin 10 conectado a pin B-IA
const int BIB = 9;  // (pwm) pin 9 conectado a pin B-IB
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
   analogWrite(AIA, 0);
  analogWrite(AIB, 0);
  VMA1=0;
  VMR1=0;
}
void StopB()
{
   analogWrite(BIA, 0);
  analogWrite(BIB, 0);
  VMR2=0;
  VMR2=0;
}
void avanzar()
{

   analogWrite(AIA, 0);
  analogWrite(AIB, VMA1);
}
void avanzarB()
{

   analogWrite(BIA, 0);
  analogWrite(BIB, VMA2);
}

void retroceder()
{

   analogWrite(AIA, VMR1);
  analogWrite(AIB, 0);
}
void retrocederB()
{

   analogWrite(BIA, VMR2);
  analogWrite(BIB, 0);
}




void forward()
{
  VMA1 = VMA1 + 1;
   if ( VMA1 > 255 ) {
    VMA1 = 255;
    
  
  }
  avanzar();
  }
 

void forwardB()
{
  VMA2 = VMA2 + 1;
   if ( VMA2 > 255 ) {
    VMA2 = 255;
    
  
  }
  avanzarB();
  }
 


void backward()
{
    VMR1 = VMR1 - 1;
   if ( VMR1 < 0 ) {
    VMR1 = 0;
    
  
  }
  retroceder();
  }


void backwardB()
{
     VMR2 = VMR2 - 1;
   if ( VMR2 < 0 ) {
    VMR2 = 0;
    
  
  }
  retrocederB();
  }





void setup() {

Serial.begin(9600);


  pinMode(AIA, OUTPUT); // fijar los pines como salidas
  pinMode(AIB, OUTPUT);
  pinMode(BIA, OUTPUT);
  pinMode(BIB, OUTPUT);
  pinMode(luz, OUTPUT);
  analogWrite(AIA, 0);
  analogWrite(AIB, 0);
  analogWrite(BIA, 0);
  analogWrite(BIB, 0);
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
