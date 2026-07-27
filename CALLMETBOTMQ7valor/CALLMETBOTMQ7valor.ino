/**
 * @file Whatsapp_Message.ino
 * @author Hafidh Hidayat (hafidhhidayat@hotmail.com)
 * @brief Example Whatsapp Message
 * 
 * @copyright Copyright (c) 2022
 * 
 * Github :
 * https://github.com/hafidhh
 * https://github.com/hafidhh/Callmebot_ESP8266
 */

#include <ESP8266WiFi.h>
#include <Callmebot_ESP8266.h>

const char* ssid = "Wi-Fi-Sanchez_5G";
const char* password = "diabolicos";
// Note :
// phoneNumber : Indonesia +62, Example: "+62897461238"
// apiKey : Follow instruction on https://www.callmebot.com/blog/free-api-whatsapp-messages/
String phoneNumber = "+5493496418942";
String apiKey = "2335187";
String messsage = "ALERTA PELIGRO MONOXIDO !!! Valor: ";

#include <Adafruit_Sensor.h>
#include "MQ7.h"
#define A_PIN A0
#define VOLTAGE 5
MQ7 mq7(A_PIN, VOLTAGE);
#define ledPin D4
 int C2O;
int parametro = 20;
bool firstMessageSent = false;        
const long ALARMA_INTERVALO = 1 * 60 * 1000; // 1 minutos en milisegundos
unsigned long tiempoAnterior = 0;

void setup() {
	Serial.begin(115200);
    mq7.calibrate();    // calculates R0
    
     pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);  // LED apagado al inicio

	WiFi.begin(ssid, password);
	Serial.println("Connecting");
	while(WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}
	Serial.println("");
	Serial.print("Connected to WiFi network with IP Address: ");
	Serial.println(WiFi.localIP());

	Callmebot.begin();

	

}

void loop() {
	lecturaMQ7 ();
}
void lecturaMQ7 (){
    unsigned long tiempoActual = millis();

  C2O = mq7.readPpm();

  if (tiempoActual - tiempoAnterior >= ALARMA_INTERVALO && C2O >= parametro ) {
    // Disparar la alarma
    // Whatsapp Message
  Callmebot.whatsappMessage(phoneNumber, apiKey, messsage + String(C2O) );
  Serial.println(Callmebot.debug());
    Serial.println("¡ALARMA!");
    digitalWrite(ledPin, HIGH); // Enciende el pin de la alarma
    delay(1000); // Dejar la alarma encendida por 1 segundo (ejemplo)
    digitalWrite(ledPin, LOW); // Apaga la alarma
    tiempoAnterior = tiempoActual; // Actualizar el tiempo anterior
  }
}
