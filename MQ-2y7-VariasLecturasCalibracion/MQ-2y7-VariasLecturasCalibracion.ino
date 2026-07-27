#include <MQ2.h>
#include <Adafruit_Sensor.h>
#include "MQ7.h"
#define A_PIN A1
#define VOLTAGE 5
MQ7 mq7(A_PIN, VOLTAGE);
//change this with the pin that you use
int pin = A0;
float lpg, co, smoke;
int C2O;

MQ2 mq2(pin);

void setup() {
  Serial.begin(9600);

  mq7.calibrate();    // calculates R0
  // calibrate the device
  mq2.begin();
  lpg = 0;
  co = 0;
  smoke = 0;
  C2O = 0;
}

void loop() {
  lecturaMQ7 (); // lee el sensor de monóxido
  /*
     read the values from the sensor, it returns
     an array which contains 3 values.
     0 : LPG in ppm
     1 : CO in ppm
     2 : SMOKE in ppm
  */
  float* values = mq2.read(true); //set it false if you don't want to print the values to the Serial

  lpg = values[0];
  //  lpg = mq2.readLPG();
  Serial.print("Valor analógico del sensor MQ-2: LGP ");
  Serial.print(lpg);
  Serial.println("ppm");
  co = values[1];
  Serial.print("Valor analógico del sensor MQ-2: co ");
  Serial.print(co);
  Serial.println("ppm");
  //  co = mq2.readCO();
  smoke = values[2];

  Serial.print("Valor analógico del sensor MQ-2: smoke ");
  Serial.print(smoke);
  Serial.println("ppm");
  // smoke = mq2.readSmoke();

  delay(10000);
}
void lecturaMQ7 () {
  C2O = mq7.readPpm();
  Serial.print(" Valor C2O: ");
  Serial.println(C2O);
}
