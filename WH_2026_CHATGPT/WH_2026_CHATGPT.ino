#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <DHT.h>
#include <FS.h>

/* ---------- WIFI AP ---------- */
const char* ssid = "WeatherHouse";

/* ---------- DNS (PORTAL CAUTIVO) ---------- */
DNSServer dnsServer;
const byte DNS_PORT = 53;

/* ---------- WEB SERVER ---------- */
ESP8266WebServer server(80);

/* ---------- DHT ---------- */
#define DHTPIN D2        // GPIO4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

/* ---------- LED ---------- */
#define LED_PIN D6       // GPIO12

/* ---------- VARIABLES ---------- */
float humedad = 0;
float temperatura = 0;
bool posibleTormenta = false;

/* ---------- HTML ---------- */
String paginaWeb() {
  String imagen = posibleTormenta ? "vieja.jpg" : "viejo.jpg";
  String mensaje = posibleTormenta ? "⚠️ Posible tormenta!" : "☀️ Buen tiempo!";

  String html = "<!DOCTYPE html><html><head>";
  html += "<meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "<meta http-equiv='refresh' content='6'>";
  html += "<title>Weather House</title>";

  html += "<style>";
  html += "body{font-family:Arial;text-align:center;background:#eaeaea;}";
  html += ".card{background:white;padding:20px;margin:40px auto;width:320px;border-radius:15px;}";
  html += "img{width:220px;margin-top:10px;}";
  html += "h2{margin:8px 0;}";
  html += "</style></head><body>";

  html += "<div class='card'>";
  html += "<h1>🏠 Weather House</h1>";
  html += "<h2>🌡️ Temperatura: " + String(temperatura) + " °C</h2>";
  html += "<h2>💧 Humedad: " + String(humedad) + " %</h2>";
  html += "<h2>" + mensaje + "</h2>";
  html += "<img src='/" + imagen + "'>";
  html += "</div></body></html>";

  return html;
}

/* ---------- HANDLERS ---------- */
void handleRoot() {
  server.send(200, "text/html", paginaWeb());
}

void redirigirPortal() {
  server.sendHeader("Location", "/", true);
  server.send(302, "text/plain", "");
}

void setup() {
  Serial.begin(115200);

  /* LED SIEMPRE ENCENDIDO */
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);

  /* DHT */
  dht.begin();

  /* SPIFFS */
  if (!SPIFFS.begin()) {
    Serial.println("❌ Error montando SPIFFS");
    return;
  }

  /* WIFI AP ABIERTO */
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid);

  Serial.print("📡 Conectarse a: ");
  Serial.println(WiFi.softAPIP());

  /* DNS: atrapa todo */
  dnsServer.start(DNS_PORT, "*", WiFi.softAPIP());

  /* PORTAL CAUTIVO */
  server.on("/", handleRoot);
  server.on("/generate_204", redirigirPortal);        // Android
  server.on("/hotspot-detect.html", redirigirPortal);// iOS
  server.on("/ncsi.txt", redirigirPortal);           // Windows
  server.onNotFound(redirigirPortal);

  /* IMÁGENES */
  server.serveStatic("/viejo.jpg", SPIFFS, "/viejo.jpg");
  server.serveStatic("/vieja.jpg", SPIFFS, "/vieja.jpg");

  server.begin();
}

void loop() {
  dnsServer.processNextRequest();
  server.handleClient();

  humedad = dht.readHumidity();
  temperatura = dht.readTemperature();

  if (!isnan(humedad) && !isnan(temperatura)) {
    posibleTormenta = (humedad >= 40);
  }

  delay(2000);
}
