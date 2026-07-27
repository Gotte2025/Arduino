#include <Servo.h>

Servo servo_1;  //SERVO 1

Servo servo_2;  //SERVO 2

Servo servo_3;  //SERVO 3

Servo servo_4;  //SERVO 4

Servo servo_5;  //SERVO 5

Servo servo_6;  //SERVO 6

int estado1 = 0;
int estado2 = 0;
int estado3 = 0;
int estado4 = 0;
int estado5 = 0;
int estado6 = 0;

int retardo = 10;


int angulo = 20;

void setup() {

  pinMode(2, INPUT);
  servo_1.attach(9);
  servo_1.write(0);

  pinMode(3, INPUT);
  servo_2.attach(10);
  servo_2.write(0);

  pinMode(4, INPUT);
  servo_3.attach(11);
  servo_3.write(0);

  pinMode(5, INPUT);
  servo_4.attach(12);
  servo_4.write(0);

pinMode(7, INPUT);
  servo_5.attach(6);
  servo_5.write(0);

pinMode(13, INPUT);
  servo_6.attach(8);
  servo_6.write(0);
}

void loop() {

  //SERVO 1

  if (digitalRead(2) == 0 && estado1 == 0) {
    for (int pos = 0; pos < angulo; pos++) {
      servo_1.write(pos);
      delay(retardo);
    }

    estado1 = 1;
    delay(100);
  }

  if (digitalRead(2) == 0 && estado1 == 1) {
    for (int pos = angulo; pos >= 0; pos--) {
      servo_1.write(pos);
      delay(retardo);
    }

    estado1 = 0;
    delay(100);
  }

  // SERVO 2

  if (digitalRead(3) == 0 && estado2 == 0) {
    for (int pos = 0; pos < angulo; pos++) {
      servo_2.write(pos);
      delay(retardo);
    }

    estado2 = 1;
    delay(100);
  }

  if (digitalRead(3) == 0 && estado2 == 1) {
    for (int pos = angulo; pos >= 0; pos--) {
      servo_2.write(pos);
      delay(retardo);
    }

    estado2 = 0;
    delay(100);
  }

  // SERVO 3

  if (digitalRead(4) == 0 && estado3 == 0) {
    for (int pos = 0; pos < angulo; pos++) {
      servo_3.write(pos);
      delay(retardo);
    }

    estado3 = 1;
    delay(100);
  }

  if (digitalRead(4) == 0 && estado3 == 1) {
    for (int pos = angulo; pos >= 0; pos--) {
      servo_3.write(pos);
      delay(retardo);
    }

    estado3 = 0;
    delay(100);
  }
    // SERVO 4

  if (digitalRead(5) == 0 && estado4 == 0) {
    for (int pos = 0; pos < angulo; pos++) {
      servo_4.write(pos);
      delay(retardo);
    }

    estado4 = 1;
    delay(100);
  }

  if (digitalRead(5) == 0 && estado4 == 1) {
    for (int pos = angulo; pos >= 0; pos--) {
      servo_4.write(pos);
      delay(retardo);
    }

    estado4 = 0;
    delay(100);
  }

 // SERVO 5

  if (digitalRead(7) == 0 && estado5 == 0) {
    for (int pos = 0; pos < angulo; pos++) {
      servo_5.write(pos);
      delay(retardo);
    }

    estado5 = 1;
    delay(100);
  }

  if (digitalRead(7) == 0 && estado5 == 1) {
    for (int pos = angulo; pos >= 0; pos--) {
      servo_5.write(pos);
      delay(retardo);
    }

    estado5 = 0;
    delay(100);
  }

// SERVO 6

  if (digitalRead(13) == 0 && estado6 == 0) {
    for (int pos = 0; pos < angulo; pos++) {
      servo_6.write(pos);
      delay(retardo);
    }

    estado6 = 1;
    delay(100);
  }

  if (digitalRead(13) == 0 && estado6 == 1) {
    for (int pos = angulo; pos >= 0; pos--) {
      servo_6.write(pos);
      delay(retardo);
    }

    estado6 = 0;
    delay(100);
  }


  delay(10);  // Delay a little bit to improve simulation performance
}
