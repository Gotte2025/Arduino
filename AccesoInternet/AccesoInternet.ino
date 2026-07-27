#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <WiFiManager.h>

// Define el nombre del portal cautivo y la contraseña (opcional)
#ifndef STASSID
#define STASSID "MiRed"
#define STAPSK  "MiContraseña"
#endif

const char* ssid     = STASSID;
const char* password = STAPSK;

void setup() {
  Serial.begin(115200);
  Serial.println("Iniciando...");

  WiFiManager wifiManager;

  // Borra las credenciales WiFi si es necesario (opcional)
  // wifiManager.resetSettings();

  // Inicia el portal cautivo automáticamente si no se puede conectar a la red
  if (!wifiManager.autoConnect("ESP8266_Config")) {
    Serial.println("Fallo al conectar y timeout del portal cautivo");
    delay(3000);
    // Si no se conecta, reiniciar
    ESP.restart();
  }

  // Si se conecta, imprime la IP
  Serial.println("Conectado a la red Wi-Fi!");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Tu código aquí
}
