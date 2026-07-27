
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>
#include "LDR.hpp";
#include "pagina.hpp";

#define DHTPIN D2

const byte DNS_PORT = 53;
IPAddress apIP(172, 217, 28, 1);
DNSServer dnsServer;

ESP8266WebServer server(80);

float temperature_celsius;
int temperature_fahrenheit;
int porcentaje_humedad;
int sensacion_termica;
int temperature;
int humidity;
float puntoRocio;

#define DHTTYPE DHT11  // DHT 11 \
                       // // Crear objeto para DHT11:
DHT dht = DHT(DHTPIN, DHTTYPE);



void startWebServer() {
  server.on("/", handleRoot);

   //} );

  server.on("/CLIMA.jpg", []() {
    getSpiffImg("/CLIMA.jpg", "image/jpg");
  });

  
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("#################### Server BEGIN!! ####################");
}


void handleRoot() {

  String rootWebPage = "<!DOCTYPE html><html><head><title>:: MINI ESTACION :: </title>";
  rootWebPage += "<body bgcolor=skyblue> ";
  rootWebPage += "</head><body\"><h1><font color=white>MINI ESTACION METEOROLOGICA</h1>";
  rootWebPage += "<img src=\"/bandera.gif\" alt=\"\"  height=300 width=350 /><br/>";
  rootWebPage += "<img src=\"/CLIMA.jpg\" alt=\"\"  height=30 width=40 /><br/>";
  // rootWebPage += "<p>=iluminacion: " + String(ilum)+ " % </p>"; // Asi se suben los valores a la Access point
  rootWebPage += "<p>=Temperatura: " + String(temperature_celsius) + " °C </p>";  // Asi se suben los valores a la Access point
  rootWebPage += "<p>=Humedad: " + String(porcentaje_humedad) + " % </p>";      // Asi se suben los valores a la Access point
  rootWebPage += "</body></html>";

  server.send(200, "text/html", rootWebPage);
}



void handleNotFound() {

 handleRoot();
}

void getSpiffImg(String path, String TyPe) {
  if (SPIFFS.exists(path)) {
    File file = SPIFFS.open(path, "r");
    server.streamFile(file, TyPe);
    file.close();
  }
}


void sensordht() {
  // Lectura de Sensor:
  temperature_celsius = dht.readTemperature();
  temperature_fahrenheit = dht.readTemperature(true);
  porcentaje_humedad = dht.readHumidity();
  sensacion_termica = dht.computeHeatIndex(temperature_celsius, porcentaje_humedad, false);
}

void punto_rocio() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  puntoRocio = pow((humidity / 100), 0.125) * (110 + temperature) - 110;
}





void setup() {
  Serial.begin(115200);
  while (!Serial) {
    delay(1);
  }

  WiFi.mode(WIFI_AP);  //Only Access point
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP("LDR");
  dnsServer.start(DNS_PORT, "*", apIP);
  SPIFFS.begin();
  Serial.println("----- Web Server Start ------");
  startWebServer();
  dht.begin();
}

void loop() {
  dnsServer.processNextRequest();
  server.handleClient();
  sensordht();
  punto_rocio();
}
