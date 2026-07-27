#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>

const char* ssid = "G3D";
const char* password = "1234";
IPAddress apIP(192, 168, 4, 1);

ESP8266WebServer server(80);

void handleRoot() {
  String html = "<html><body>";
  html += "<form method='POST' action='/submit'>";
  html += "Nombre: <input type='text' name='nombre'><br>";
  html += "<input type='submit' value='Enviar'>";
  html += "</form></body></html>";
  server.send(200, "text/html", html);
}

void handleSubmit() {
  String nombre = server.arg("nombre");
  //Procesa el nombre recibido, por ejemplo, guardarlo en una variable o imprimirlo.
  server.send(200, "text/html", "<html><body>Datos recibidos: " + nombre + "</body></html>");
}

void setup() {
  Serial.begin(115200);
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0)); // Configura la IP del AP
  server.on("/", handleRoot);
  server.on("/submit", HTTP_POST, handleSubmit);
  server.begin();
}

void loop() {
  server.handleClient();
}
