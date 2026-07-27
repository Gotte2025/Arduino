#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

// --- Datos WiFi iniciales ---
String ssid = "Rivadavia3220";
String password = "12345678";

// --- Datos CallMeBot ---
String phoneNumber = "+5493496418942";
String apiKey = "2335187";

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println();
  Serial.println("Conectando a WiFi...");
  WiFi.begin(ssid.c_str(), password.c_str());

  int intentos = 0;
  while (WiFi.status() != WL_CONNECTED && intentos < 20) {
    delay(500);
    Serial.print(".");
    intentos++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println();
    Serial.println("✅ Conectado a WiFi");
    Serial.print("IP local: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println();
    Serial.println("⚠️ No se pudo conectar al WiFi inicial.");
  }

  // --- Configurar rutas ---
  server.on("/", handleRoot);
  server.on("/config", handleConfig);
  server.on("/send", handleSend);

  server.begin();
  Serial.println("Servidor HTTP iniciado");
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  String html = "<h2>Servidor ESP8266 CallMeBot</h2>";
  html += "<p>Conectado a: " + ssid + "</p>";
  html += "<p>IP: " + WiFi.localIP().toString() + "</p>";
  html += "<p>Usa /config o /send desde la App Kodular.</p>";
  server.send(200, "text/html", html);
}

// --- Configurar WiFi + CallMeBot ---
void handleConfig() {
  if (server.hasArg("ssid")) ssid = server.arg("ssid");
  if (server.hasArg("pass")) password = server.arg("pass");
  if (server.hasArg("phone")) phoneNumber = server.arg("phone");
  if (server.hasArg("key")) apiKey = server.arg("key");

  server.send(200, "text/plain", "✅ Datos guardados correctamente.");

  Serial.println("📡 Nuevos datos recibidos:");
  Serial.println("SSID: " + ssid);
  Serial.println("PASS: " + password);
  Serial.println("PHONE: " + phoneNumber);
  Serial.println("APIKEY: " + apiKey);
}

// --- Enviar mensaje CallMeBot ---
void handleSend() {
  if (!server.hasArg("msg")) {
    server.send(400, "text/plain", "Error: falta mensaje.");
    return;
  }

  String message = server.arg("msg");
  message.replace(" ", "%20");

  String url = "http://api.callmebot.com/whatsapp.php?phone=" + phoneNumber +
               "&text=" + message + "&apikey=" + apiKey;

  WiFiClient client;
  if (client.connect("api.callmebot.com", 80)) {
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: api.callmebot.com\r\n" +
                 "Connection: close\r\n\r\n");
    delay(500);
    client.stop();
    server.send(200, "text/plain", "📨 Mensaje enviado correctamente.");
    Serial.println("Mensaje enviado: " + message);
  } else {
    server.send(500, "text/plain", "❌ Error al conectar con CallMeBot.");
  }
}
