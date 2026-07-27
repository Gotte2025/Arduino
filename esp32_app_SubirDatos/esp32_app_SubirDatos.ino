

#include <ESP8266WiFi.h>
 
// Nombre y contraseña de tu red WiFi.
const char* ssid = "Wi-Fi Sanchez";
const char* password = "diabolicos";

#define Poten  A0 // AO va al terminal intermedio del potenciómetro.
int valor;
String respuesta = "0";

WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  
// Conecta a la red wifi.
  Serial.println();
  Serial.print("Conectando con ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Conectado con WiFi.");
 
  // Inicio del Servidor web.
  server.begin();
  Serial.println("Servidor web iniciado.");
 
  // Esta es la IP
  Serial.print("Esta es la IP para conectar: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
}
 
void loop() {
  // Consulta si se ha conectado algún cliente.
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  Serial.print("Nuevo cliente: ");
  Serial.println(client.remoteIP());

  // Espera hasta que el cliente envíe datos.
  while(!client.available()){ delay(1); }

/////////////////////////////////////////////////////
// Lee la información enviada por el cliente.
String req = client.readStringUntil('\r');
Serial.println(req);

// Realiza la petición del cliente.
if (req.indexOf("estado") != -1){
   valor = analogRead(Poten); // Consulta el valor del potenciómetro.
   respuesta = String(valor);
   Serial.println(respuesta);
   delay(10);
   }

//////////////////////////////////////////////
  // Página WEB. ////////////////////////////
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  Comillas importantes.
  
  client.println(respuesta);
  
  Serial.print("Cliente desconectado: ");
  Serial.println(client.remoteIP());
  client.flush();
  client.stop();
}
