/*
  Usa página Web en IP 192.168.0.125, para enviar señales Infrarrojas al TV 
  Así reemplazar el control remoto.
  Aplica el sistema OTA, puede reprogramarse en forma inalámbrica
  Se confijura el Router Tp-link, para que le asigne una IP fija al ESP8266, de esa manera evita que modifique el ingreso a la página web.
  Creado el 06/02/2021, modificado el 09/07/21. Lucas Gottero.
*/
#include <Arduino.h>
#if defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#endif  // ESP8266
#if defined(ESP32)
#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#endif  // ESP32
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

const char* kSsid = "TP-Link_D3E6";
const char* kPassword = "41470954";
#ifndef STASSID
#define STASSID kSsid
#define STAPSK  kPassword
#endif

MDNSResponder mdns;

#if defined(ESP8266)
ESP8266WebServer server(80);
#undef HOSTNAME
#define HOSTNAME "esp8266"
#endif  // ESP8266
#if defined(ESP32)
WebServer server(80);
#undef HOSTNAME
#define HOSTNAME "esp32"
#endif  // ESP32

const uint16_t kIrLed = D2;  // // otro pin se resetea. ESP GPIO pin to use. Recommended: 4 (D2).

IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.

void handleRoot() {
  server.send(200, "text/html",
              "<html>" 
              "<head><title> CONTROL REMOTO WEB OTA </title>" 
              "<meta http-equiv=\"Content-Type\" " 
              "content=\"text/html;charset=utf-8\">" 
              "</head>" 
              "<body>" 
              "<h1> >>CONTROL REMOTO wifi-web<< </h1>" 
              "<p>&nbsp;</p>"          
              "<p>&nbsp;</p>"
              "<h1>Presiona los siguientes botones!</h1>" \
              "<p> </p>" \ 
              "<p><a href=\"ir?code=551489775\">Encender / Apagar</a></p>" 
              "<p>&nbsp;</p>"
              "<p><a href=\"ir?code=551502015\">Vol +</a></p>" \ 
              "<p>&nbsp;</p>"
              "<p> </p>" \ 
              "<p><a href=\"ir?code=551534655\">Vol -</a></p>" \ 
              "<p>&nbsp;</p>"
              "<p> </p>" \ 
              "<p><a href=\"ir?code=551485695\">Canal +</a></p>" \
              "<p>&nbsp;</p>"
              "<p> </p>" \  
              "<p><a href=\"ir?code=551518335\">Canal -</a></p>" \ 
              "<p>&nbsp;</p>"
              "<p> </p>" \ 
              "<p><a href=\"ir?code=551546895\">Plataforma </a></p>" \
              "<p>&nbsp;</p>"
              "<p><a href=\"ir?code=551524965\">FECHA DER </a></p>" \ 
              "<p><a href=\"ir?code=551492325\">FECHA IZQ </a></p>" \
              "<p>&nbsp;</p>"
"<p><a href=\"ir?code=551512725\">FECHA ARRIBA </a></p>" \
"<p><a href=\"ir?code=551545365\">FECHA ABAJO </a></p>" \
"<p>&nbsp;</p>"
"<p><a href=\"ir?code=551508645\">OK </a></p>" \

              "</body>" \
              "</html>");
}

void handleIr() {
  for (uint8_t i = 0; i < server.args(); i++) {
    if (server.argName(i) == "code") {
      uint32_t code = strtoul(server.arg(i).c_str(), NULL, 10);
#if SEND_NEC
      irsend.sendNEC(code, 32);
      digitalWrite(D4,1);
      delay(50);
      digitalWrite(D4,0);
#endif  // SEND_NEC
    }
  }
  handleRoot();
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++)
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  server.send(404, "text/plain", message);
}

void setup(void) {
  irsend.begin();
pinMode(D4,OUTPUT);
digitalWrite(D4,0);
  Serial.begin(115200);
  WiFi.begin(kSsid, kPassword);
  Serial.println("");
  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(kSsid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP().toString());
   Serial.print("MAC: ");
   Serial.println(WiFi.macAddress());

#if defined(ESP8266)
  if (mdns.begin(HOSTNAME, WiFi.localIP())) {
#else  // ESP8266
  if (mdns.begin(HOSTNAME)) {
#endif  // ESP8266
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.on("/ir", handleIr);

  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");

   ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_FS
      type = "filesystem";
    }

    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
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

void loop(void) {
  server.handleClient();
  ArduinoOTA.handle();
}
