#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <SPIFFS.h>
#include <FS.h>

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
     if (!SPIFFS.begin(true)) {
    Serial.println("Ocurrió un error al montar SPIFFS");
    return;
}
  // Ejemplo de escritura en un archivo
  File file = SPIFFS.open("/ejemplo.txt", FILE_WRITE);
  if (!file) {
    Serial.println("Error al abrir el archivo para escritura");
    return;
  }
  file.println("Este es un ejemplo de texto guardado en SPIFFS.");
  file.close();

  // Ejemplo de lectura de un archivo
  file = SPIFFS.open("/ejemplo.txt", "r");
  if (!file) {
    Serial.println("Error al abrir el archivo para lectura");
    return;
  }
  Serial.println("Contenido del archivo:");
  while (file.available()) {
    Serial.write(file.read());
  }
  file.close();

  // Ejemplo de listar archivos
  Serial.println("\nListando archivos en SPIFFS:");
  File root = SPIFFS.open("/");
  File file2 = root.openNextFile();
  while (file2) {
    Serial.print("Archivo: ");
    Serial.println(file2.name());
    file2 = root.openNextFile();
  }
}

void loop() {
  server.handleClient();
}
