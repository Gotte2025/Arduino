/**
 
  Alarma: 99999
  Equipo: 99999
  Programa:AMQ7W1-prueba6-
  Usuario:Rafael Gottero.
  Domicilio Red: Rivadavia 3220 Dpto 4
  Aviso externo: Lucas Gottero Cel: 3496 579670 (Cel Rafa)

*/

#include <ESP8266WiFi.h>
#include <Callmebot_ESP8266.h>

const char* ssid = "Sanchez - Santucci";
const char* password = "40575645";

// apiKey : Follow instruction on https://www.callmebot.com/blog/free-api-whatsapp-messages/
String phoneNumber = "+5493496579670"; // (Cel Rafa)
String apiKey = "2335187";

#include <Adafruit_Sensor.h>
#include "MQ7.h"
#define A_PIN A0
#define VOLTAGE 5
MQ7 mq7(A_PIN, VOLTAGE);
#define ledPin D4
#define BuzPin D8
int C2O;
int parametro = 20; // mínimo activación alarma
int parametro2 = 30; // mínimo activación alarma
bool firstMessageSent = false;
const long ALARMA_INTERVALO = 1 * 60 * 1000; // 5 minutos en milisegundos
unsigned long tiempoAnterior = 0;

String messsage = "ALERTA PELIGRO MONOXIDO !!! https://www.murciasalud.es/web/sanidad-ambiental/monoxido-de-carbono ";
String messsage1 = "Alarma activada";
String messsage2 = "Valor de Monoxido mayor a  " + String (parametro) + " ppm !!!" ;
String messsage3 = "Valor de Monoxido mayor a  " + String (parametro2) + " ppm, ventilar ambiente riesgo para la salud !!!" ;

void setup() {
  Serial.begin(115200);
  
  mq7.calibrate();    // calculates R0

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);  // LED apagado al inicio
  pinMode(BuzPin, OUTPUT);
  analogWrite(BuzPin, 0);  // Buzzer apagado al inicio

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  Callmebot.begin();
  Callmebot.whatsappMessage(phoneNumber, apiKey, messsage1);
  alarmainterna();

}

void loop() {
  sistema();
}
void sistema() {
  
  unsigned long tiempoActual = millis();
  
lecturaMQ7 (); // lee el sensor de monóxido

   if (tiempoActual - tiempoAnterior >= ALARMA_INTERVALO && C2O >= parametro ) {
    // if (tiempoActual - tiempoAnterior >= ALARMA_INTERVALO) {
       
    alertaWssp(); // En vía mensaje de Whatsapp al exterior
    alarmainterna(); // Disparar la alarma interior del domicilio
    tiempoAnterior = tiempoActual; // Actualizar el tiempo anterior
  }
   if (tiempoActual - tiempoAnterior >= ALARMA_INTERVALO && C2O >= parametro2 ) {
    // if (tiempoActual - tiempoAnterior >= ALARMA_INTERVALO) {
       
    alertaWssp2(); // En vía mensaje de Whatsapp al exterior
    alarmainterna(); // Disparar la alarma interior del domicilio
     alarmainterna();
      alarmainterna();
    tiempoAnterior = tiempoActual; // Actualizar el tiempo anterior
  }
}

void alarmainterna() {
  digitalWrite(ledPin, HIGH); // Enciende el pin de la alarma
  analogWrite(BuzPin, 250);  // Buzzer apagado al inicio
  delay(3000); // Dejar la alarma encendida por 1 segundo (ejemplo)
  digitalWrite(ledPin, LOW); // Apaga la alarma
  analogWrite(BuzPin, 0);  // Buzzer apagado al inicio
}
void alertaWssp() {
  Callmebot.whatsappMessage(phoneNumber, apiKey, messsage);
  Callmebot.whatsappMessage(phoneNumber, apiKey, messsage2);
  Serial.println(Callmebot.debug());
  Serial.println("¡ALARMA!");
}
void alertaWssp2() {
  Callmebot.whatsappMessage(phoneNumber, apiKey, messsage);
  Callmebot.whatsappMessage(phoneNumber, apiKey, messsage3);
  Serial.println(Callmebot.debug());
  Serial.println("¡ALARMA!");
}
void lecturaMQ7 (){
   C2O = mq7.readPpm();
  Serial.print(" Valor C2O: ");
  Serial.println(C2O);
}
