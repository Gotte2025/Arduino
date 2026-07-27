#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include "MQ7.h"

#define A_PIN A0
#define VOLTAGE 5

// init MQ7 device
MQ7 mq7(A_PIN, VOLTAGE);

int CO;
//
//// Pines y configuraciones
//#define STASS_AUTORECONNECT 1
//#define DPRINT(...) Serial.printf(__VA_ARGS__)
//


// --- Configuración del Access Point ---
const char* ssid = "MiAP_mq7";
const char* password = "1234";
const int httpPort = 80;
WiFiServer server(httpPort);
//

void setup() {
  Serial.begin(115200);
  delay(10);

  Serial.println("Configurando AP...");
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("Dirección IP del AP: ");
  Serial.println(myIP);
  
// --- Configuración del sensor MQ7 ---


  Serial.println("");   // blank new line
  Serial.println("Calibrating MQ7");
  mq7.calibrate();    // calculates R0
  Serial.println("Calibration done!");
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    // Espera a que se conecte un cliente.
    return;
  }

  // Lee la temperatura y la humedad del sensor
  CO = mq7.readPpm();
 
  


  // Construye la página HTML para mostrar los datos
  String html = "<html><body>";
  html += "<h1>Datos del sensor MQ7</h1>";
  html += "<p>GAS: " + String(CO) + " %</p>";
   html += "</body></html>";

  // Envía la respuesta al cliente
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println();
  client.println(html);

  Serial.println("Datos enviados al cliente.");
}
