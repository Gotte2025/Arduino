#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "xxxxxxxxxxxxxxxx";
const char* password = "xxxxxxxxxxxxxxx";
const char* serverUrl = "https://us-central1-gasalert.cloudfunctions.net/sendAlert"; // Se genera al subir a Firebase

int mq7_pin = A0;
int umbral = 400;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Conectando WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado!");
}

void loop() {
  int lectura = analogRead(mq7_pin);
  Serial.println(lectura);
  if (lectura > umbral) {
    enviarAlerta(lectura);
    delay(60000); // evita múltiples alertas
  }
  delay(1000);
}

void enviarAlerta(int valor) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");
    String body = "{\"value\":" + String(valor) + "}";
    int code = http.POST(body);
    Serial.println(code > 0 ? "Alerta enviada!" : "Error al enviar");
    http.end();
  }
}
