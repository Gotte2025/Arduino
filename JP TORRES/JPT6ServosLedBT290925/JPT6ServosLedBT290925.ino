#include <Servo.h>            // Servo-adicionamos librería para servos

Servo servo1;     // Servo- pin 9
Servo servo2;     // Servo- pin 10
Servo servo3;     // Servo- pin 11
Servo servo4;     // Servo- pin 12
Servo servo5;     // Servo- pin 6
Servo servo6;     // Servo- pin 8
int estado1 = 0;  // estado Desvio 1
int estado2 = 0;  // estado Desvio 2
int estado3 = 0;  // estado Desvio 3
int estado4 = 0;  // estado Desvio 4
int estado5 = 0;  // estado Desvio 5
int estado6 = 0;  // estado Desvio 6
int estadoluz = 0; // estado LUZ
int const luz = 13; //Led pin 13

int angulo = 0 ;    // Servo-angulo de inicio

int command; //Int to store app command state.

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  servo1.attach (9);       // Define el pin 9 para el servo01
  servo2.attach (10);       // Define el pin 10 para el servo02
  servo3.attach (11);       // Define el pin 11 para el servo03
  servo4.attach (12);       // Define el pin 12 para el servo04
  servo5.attach (6);       // Define el pin 6 para el servo05
  servo6.attach (8);       // Define el pin 9 para el servo06
  servo1.write(0);         // si el servo es de 180°
  servo2.write(0);             //si el servo es de 180°
  servo3.write(0);         // si el servo es de 180° // si el servo es de 180°
  servo4.write(0);         // si el servo es de 180°
  servo5.write(0);         // si el servo es de 180°
  servo6.write(0);         //si el servo es de 180°
 pinMode(luz, OUTPUT);    //Luz en pin 13 
  
  delay(1000);
}

//ILUMINACION PIN 13

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

//DESVIO 1

// movimiento en ángulo creciente
void servocrece1()
{
  for (angulo = 0; angulo <= 30; angulo += 1)
  {
    servo1.write(angulo);
    delay(50);
  }
}

// movimiento en ángulo decreciente
void servodecrece1()
{
  for (angulo = 30; angulo >= 0; angulo -= 1)
  {
    servo1.write(angulo);
    delay(50);
  }
}
void Desvio1() {

  if (estado1 == 0)
  {
    servocrece1();
  }
  if ( estado1 == 1)
  {
    servodecrece1();
  }
  estado1 = !estado1;

  delay(2);
}

//DESVIO 2

// movimiento en ángulo creciente
void servocrece2()
{
  for (angulo = 0; angulo <= 30; angulo += 1)
  {
    servo2.write(angulo);
    delay(50);
  }
}

// movimiento en ángulo decreciente
void servodecrece2()
{
  for (angulo = 30; angulo >= 0; angulo -= 1)
  {
    servo2.write(angulo);
    delay(50);
  }
}
void Desvio2() {

  if (estado2 == 0)
  {
    servocrece2();
  }
  if ( estado2 == 1)
  {
    servodecrece2();
  }
  estado2 = !estado2;

  delay(2);
}

//DESVIO 3

// movimiento en ángulo creciente
void servocrece3()
{
  for (angulo = 0; angulo <= 30; angulo += 1)
  {
    servo3.write(angulo);
    delay(50);
  }
}

// movimiento en ángulo decreciente
void servodecrece3()
{
  for (angulo = 30; angulo >= 0; angulo -= 1)
  {
    servo3.write(angulo);
    delay(50);
  }
}
void Desvio3() {

  if (estado3 == 0)
  {
    servocrece3();
  }
  if ( estado3 == 1)
  {
    servodecrece3();
  }
  estado3 = !estado3;

  delay(2);
}

//DESVIO 4

// movimiento en ángulo creciente
void servocrece4()
{
  for (angulo = 0; angulo <= 30; angulo += 1)
  {
    servo4.write(angulo);
    delay(50);
  }
}

// movimiento en ángulo decreciente
void servodecrece4()
{
  for (angulo = 30; angulo >= 0; angulo -= 1)
  {
    servo4.write(angulo);
    delay(50);
  }
}
void Desvio4() {

  if (estado4 == 0)
  {
    servocrece4();
  }
  if ( estado4 == 1)
  {
    servodecrece4();
  }
  estado4 = !estado4;

  delay(2);
}

//DESVIO 5

// movimiento en ángulo creciente
void servocrece5()
{
  for (angulo = 0; angulo <= 30; angulo += 1)
  {
    servo5.write(angulo);
    delay(50);
  }
}

// movimiento en ángulo decreciente
void servodecrece5()
{
  for (angulo = 30; angulo >= 0; angulo -= 1)
  {
    servo5.write(angulo);
    delay(50);
  }
}
void Desvio5() {

  if (estado5 == 0)
  {
    servocrece5();
  }
  if ( estado5 == 1)
  {
    servodecrece5();
  }
  estado5 = !estado5;

  delay(2);
}


//DESVIO 6

// movimiento en ángulo creciente
void servocrece6()
{
  for (angulo = 0; angulo <= 30; angulo += 1)
  {
    servo6.write(angulo);
    delay(50);
  }
}

// movimiento en ángulo decreciente

void servodecrece6()
{
  for (angulo = 30; angulo >= 0; angulo -= 1)
  {
    servo6.write(angulo);
    delay(50);
  }
}

void Desvio6() {

  if (estado6 == 0)
  {
    servocrece6();
  }
  if ( estado6 == 1)
  {
    servodecrece6();
  }
  estado6 = !estado6;

  delay(2);
}

void loop() {

  if (Serial.available() > 0)
  {
    command = Serial.read();

    switch (command) {
      case '0': Desvio1() ;  break;
      case '1': Desvio2(); break;
      case '2': Desvio3(); break;
       case '3': Desvio4(); break;
       case '4': Desvio5(); break;
       case '5': Desvio6(); break;
 case '9': iluminacion(); break;
        delay(2);
    }
  }
}
