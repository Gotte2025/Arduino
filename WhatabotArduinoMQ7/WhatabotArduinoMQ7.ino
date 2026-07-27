#include <WhatabotAPIClient.h>
#include <WiFiManager.h>

#define WHATABOT_API_KEY "a07f5530-06cf-4cae-9882"
#define WHATABOT_CHAT_ID "5493496418942"
#define WHATABOT_PLATFORM "whatsapp"

WiFiManager wifiManager;
WhatabotAPIClient whatabotClient(WHATABOT_API_KEY, WHATABOT_CHAT_ID, WHATABOT_PLATFORM);

//You must connect to the generated network, and from there, you can set the SSID and password for your Wi-Fi network to which the ESP8266 will connect.
//If you dont want to use WiFiManager you can still connect to WiFi using other logic.
#define AP_SSID "Sanchez - Santucci"
#define AP_PASS "40575645"
#include <Adafruit_Sensor.h>
#include "MQ7.h"
#define A_PIN A0
#define VOLTAGE 5
MQ7 mq7(A_PIN, VOLTAGE);
int C2O;
int MQ7State = LOW;       // Estado actual del MQ7
int lastMQ7State = LOW;   // Último estado del MQ7

unsigned long lastMessageTime = 0;         // Tiempo del último mensaje enviado
const unsigned long messageInterval = 120000; // Intervalo en milisegundos (ej. 30 segundos)
bool firstMessageSent = false;             // Bandera para el primer mensaje
const int ledPin = D4;     // Pin del LED

void setup() {
  Serial.begin(115200);
  wifiManager.autoConnect(AP_SSID, AP_PASS);
  whatabotClient.begin();
  whatabotClient.onMessageReceived(onMessageReceived); 
  whatabotClient.onServerResponseReceived(onServerResponseReceived);
mq7.calibrate();    // calculates R0
pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);  // LED apagado al inicio
}

void loop() {
  whatabotClient.loop(); 
}

void onServerResponseReceived(String message) {
  Serial.println(message); 
}

void onMessageReceived(String message) {
  message.toUpperCase();
  Serial.println(message);

  if (message.equals("START")) {
    whatabotClient.sendMessageWS("Starting");
    // Add your logic for starting here
  } else if (message.equals("STOP")) {
    whatabotClient.sendMessageWS("Stopping");
    // Add your logic for stopping here
  } else if (message.equals("PAUSE")) {
    whatabotClient.sendMessageWS("Pausing");
    // Add your logic for pausing here
  } else if (message.equals("RESUME")) {
    whatabotClient.sendMessageWS("Resumming");
    // Add your logic for resuming here
  } else {
    whatabotClient.sendMessageWS("Unknown command");
    // Handle unknown commands here (optional)
  }
  
}

void LecturaMQ (){
  int MQ7Reading = analogRead(A_PIN);  // Lee el estado del PIR
 MQ7State
 if(MQ7Reading > 10){
   MQ7State=HIGH;
 }
  // Si el estado del PIR ha cambiado
  if (MQ7State != lastMQ7State) {
   lastMQ7State = MQ7State;
    Serial.println("MONOXIDO ALTO /// PELIGRO !!!");
    // Si detecta movimiento
    if (MQ7State == HIGH) {
      digitalWrite(ledPin, HIGH);  // Enciende el LED
      
      // Verifica si es el primer mensaje o si ha pasado el intervalo
      if (!firstMessageSent || (millis() - lastMessageTime >= messageInterval)) {
        String mensaje = "Alerta: Movimiento detectado por el sensor PIR";  // Mensaje para la notificacion 
        Callmebot.whatsappMessage(phoneNumber, apiKey, mensaje);
        Serial.println("Mensaje enviado: " + mensaje);

        lastMessageTime = millis();  // Actualiza el tiempo del último mensaje
        firstMessageSent = true;     // Marca el primer mensaje como enviado
      }
    } else {
      delay(2000);
      digitalWrite(ledPin, LOW);  // Apaga el LED si no hay movimiento
       
    }
  }
}
