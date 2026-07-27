#include <ESP8266WiFi.h>
#include <DHT.h>

// Pines y configuraciones
#define STASS_AUTORECONNECT 1
#define DPRINT(...) Serial.printf(__VA_ARGS__)

// --- Configuración del sensor DHT11 ---
#define DHTPIN D1    // Pin donde se conecta el sensor DHT11
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// --- Configuración del Access Point ---
const char* ssid = "MiAP_DHT11";
const char* password = "clave_segura";
const int httpPort = 80;
WiFiServer server(httpPort);

// --- Variables globales ---
float temperature;
float humidity;

void setup() {
  Serial.begin(115200);
  delay(10);

  Serial.println("Configurando AP...");
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("Dirección IP del AP: ");
  Serial.println(myIP);

  dht.begin();
  Serial.println("Sensor DHT11 inicializado");
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    // Espera a que se conecte un cliente.
    return;
  }

  // Lee la temperatura y la humedad del sensor
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  
  // Verifica si no hay lecturas válidas
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Error leyendo del sensor DHT11!");
    client.stop();
    return;
  }

  // Construye la página HTML para mostrar los datos
  String html = "<html><body>";
  html += "<h1>Datos del sensor DHT11</h1>";
  html += "<p>Temperatura: " + String(temperature) + " °C</p>";
  html += "<p>Humedad: " + String(humidity) + " %</p>";
  html += "</body></html>";

  // Envía la respuesta al cliente
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println();
  client.println(html);

  Serial.println("Datos enviados al cliente.");
}
