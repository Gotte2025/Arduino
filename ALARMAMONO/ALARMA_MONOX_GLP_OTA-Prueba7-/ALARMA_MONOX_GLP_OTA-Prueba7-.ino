/**
 ALARMA MONOXIDO 
 */
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <ESP8266WiFi.h>
#include <Callmebot_ESP8266.h>

const char* ssid = "Sanchez - Santucci";
const char* password = "40575645";
// Note :
// phoneNumber : Indonesia +62, Example: "+62897461238"
// apiKey : Follow instruction on https://www.callmebot.com/blog/free-api-whatsapp-messages/
String phoneNumber = "+5493496418942";
String apiKey = "2335187";

#include <Adafruit_Sensor.h>
#include "MQ7.h"
#define A_PIN A0
#define VOLTAGE 5
MQ7 mq7(A_PIN, VOLTAGE);
#define ledPin D4
#define BuzPin D8
 int C2O;
int parametro = 20;
bool firstMessageSent = false;        
int ALARMA_INTERVALO = 1 * 60 * 1000; // 5 minutos en milisegundos
int tiempoAnterior = 0;

String messsage = "ALERTA PELIGRO MONOXIDO !!! https://www.murciasalud.es/web/sanidad-ambiental/monoxido-de-carbono ";
String messsage1 = "Alarma activada";
String messsage2 = "Valor de Monoxido: " + String (C2O) + " ppm !!!" ;
void sonido(){
    digitalWrite(ledPin, HIGH); // Enciende el pin de la alarma
     analogWrite(BuzPin, 250);  // Buzzer apagado al inicio
    delay(3000); // Dejar la alarma encendida por 1 segundo (ejemplo)
     digitalWrite(ledPin, LOW); // Apaga la alarma
     analogWrite(BuzPin, 0);  // Buzzer apagado al inicio
}
void setup() {
	Serial.begin(115200);
    mq7.calibrate();    // calculates R0
    
     pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);  // LED apagado al inicio
   pinMode(BuzPin, OUTPUT);
  analogWrite(BuzPin, 0);  // Buzzer apagado al inicio
 WiFi.mode(WIFI_STA);
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
  Callmebot.whatsappMessage(phoneNumber, apiKey, messsage1);
 sonido();

	 while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();

}
 ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_FS
      type = "filesystem";
    }
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}


void lecturaMQ7 (){
    unsigned long tiempoActual = millis();

  C2O = mq7.readPpm();
Serial.print(" Valor C2O: ");
Serial.println(C2O);
  if (tiempoActual - tiempoAnterior >= ALARMA_INTERVALO && C2O >= parametro ) {
// if (tiempoActual - tiempoAnterior >= ALARMA_INTERVALO) {
    // Disparar la alarma
    // Whatsapp Message
  Callmebot.whatsappMessage(phoneNumber, apiKey, messsage);
    Callmebot.whatsappMessage(phoneNumber, apiKey, "Valor de Monoxido: " + String (C2O) + " ppm !!!");
  Serial.println(Callmebot.debug());
    Serial.println("¡ALARMA!");
   sonido();
    tiempoAnterior = tiempoActual; // Actualizar el tiempo anterior
  }
}


void loop() {
  ArduinoOTA.handle();
  lecturaMQ7 ();
}
