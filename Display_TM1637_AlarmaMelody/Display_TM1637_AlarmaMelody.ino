
#include "Display.h"
#include "SensorMonoxido.h"
#include "Melody.h"

#define Led_13 13


void setup()
{
  Serial.println("Calibrating MQ7");
  mq7.calibrate();  // calculates R0
  Serial.println("Calibration done!");

  pinMode(Led_13, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop()
{
  display.setBrightness(0x0ff);

  Monoxido();

  alarma ();

}



void alarma () {
  dato = C2O;
  if (C2O > 14) {
    alerta ();
    digitalWrite(Led_13, HIGH);
    delay(100);
    digitalWrite(Led_13, LOW);
    delay(100);
    digitalWrite(Led_13, HIGH);
    delay(100);
    digitalWrite(Led_13, LOW);
    delay(100);
    digitalWrite(Led_13, HIGH);
    delay(100);
    digitalWrite(Led_13, LOW);
    delay(100);
    digitalWrite(Led_13, HIGH);
    piratas();
    digitalWrite(buzzer, LOW);
    delay(500);
  }
  if (C2O < 15) {
    pantalla ();
    digitalWrite(Led_13, LOW);
    digitalWrite(buzzer, LOW);
  }

}
