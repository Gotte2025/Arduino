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
#define MQ_PIN D0
#define VOLTAGE 5
MQ7 mq7(MQ_PIN, VOLTAGE);
#define ledPin D4
 int MQ7Reading=LOW;
int MQ7State=LOW;
int lastMQ7State;
unsigned long lastMessageTime = 0;         // Tiempo del último mensaje enviado
const unsigned long messageInterval = 120000; // Intervalo en milisegundos (ej. 30 segundos)
bool firstMessageSent = false;             // Bandera para el primer mensaje


void setup() {
  Serial.begin(115200);
  wifiManager.autoConnect(AP_SSID, AP_PASS);
 whatabotClient.sendMessageREST("Hi from Whatabot for ESP8266");
    mq7.calibrate();    // calculates R0
     pinMode(ledPin, OUTPUT);
     pinMode(MQ_PIN, INPUT);
  digitalWrite(ledPin, LOW);  // LED apagado al inicio
}

void loop() {
LecturaMQ ();
   
  }
   



void LecturaMQ (){
  int MQ7Reading = digitalRead(MQ_PIN);  // Lee el estado del PIR
 Serial.print("estado snesro: ");
 Serial.println(MQ7Reading);
  // Si el estado del PIR ha cambiado
  if (MQ7State != lastMQ7State) {
   lastMQ7State = MQ7State;
    
    // Si detecta movimiento
    if (MQ7State == HIGH) {
      digitalWrite(ledPin, HIGH);  // Enciende el LED
      
      // Verifica si es el primer mensaje o si ha pasado el intervalo
      if (!firstMessageSent || (millis() - lastMessageTime >= messageInterval)) {
        String mensaje = "ATENCION NIVELES ALTOS DE MONOXIDO";  // Mensaje para la notificacion 
       whatabotClient.sendMessageREST("ATENCION NIVELES ALTOS DE MONOXIDO");
       

        lastMessageTime = millis();  // Actualiza el tiempo del último mensaje
        firstMessageSent = true;     // Marca el primer mensaje como enviado
      }
    } else {
      delay(2000);
      digitalWrite(ledPin, LOW);  // Apaga el LED si no hay movimiento
       
    }
  }
}
