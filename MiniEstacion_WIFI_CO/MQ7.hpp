#include <Adafruit_Sensor.h>
#include "MQ7.h"
#define A_PIN A0
#define VOLTAGE 5
MQ7 mq7(A_PIN, VOLTAGE);
int C2O;
//SETUP

	//mq7.calibrate();		// calculates R0
 
//LOOP

  //Monoxido();

  
void Monoxido() {
C2O=mq7.readPpm();
}
 
