#include "Arduino.h"
#include <Servo.h>
Servo motorD;  // crea el objeto servo
Servo motorI;  // crea el objeto servo
#define PMD 6 // vincula el servo al pin digital 6
#define PMI 5 // vincula el servo al pin digital 5

void setup() {

  motorD.attach(PMD);
  motorI.attach(PMI);
}

void loop() {
  forward();
  delay (2000);
  backward();
  delay (2000);
  left();
  delay (2000);
  right();
  delay (2000);
  delay (2000);
  backwardRight();
  delay (2000);
  backwardLeft();
  delay (2000);
  Stop();
  delay (2000);
}

void forward()
{
  motorD.write(180);  //sentido horario
  motorI.write(180);  //sentido horario
  Serial.println("avance");
}

void backward()
{
  motorD.write(0);  //sentido antihorario
  motorI.write(0);  //sentido antihorario
  Serial.println("retroceso");
}
void left()
{
  motorD.write(135);  //sentido antihorario
  motorI.write(45);  //sentido antihorario
  Serial.println("izquierda");
}
void right()
{
  motorD.write(45);  //sentido antihorario
  motorI.write(135);  //sentido antihorario
  Serial.println("derecha");
}

void backwardRight()
{
  motorD.write(45);  //sentido antihorario
  motorI.write(0);  //sentido antihorario
  Serial.println("retrocesoderecha");
}
void backwardLeft()
{
  motorD.write(0);  //sentido antihorario
  motorI.write(45);  //sentido antihorario
  Serial.println("retrocesoizquierda");
}
void Stop()
{
  motorD.write(90);  //sentido antihorario
  motorI.write(90);  //sentido antihorario
 

}
