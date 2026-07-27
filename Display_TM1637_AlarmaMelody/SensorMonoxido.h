
#include <Adafruit_Sensor.h>
#include "MQ7.h"
#define A_PIN A0
#define VOLTAGE 5
// init MQ7 device
MQ7 mq7(A_PIN, VOLTAGE);
int C2O;

//setup


//    Serial.println("Calibrating MQ7");
//  mq7.calibrate();  // calculates R0
//  Serial.println("Calibration done!");

void Monoxido() {
  C2O = mq7.readPpm();
  
}
