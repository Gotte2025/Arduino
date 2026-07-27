#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

const char* host = "Mi_host";
const char* ssid = "G3D";
String latitude, longitude;

ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);


// Connecting WiFi

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid);

  IPAddress Ip(192, 168, 4, 1);
  IPAddress NMask(255, 255, 255, 0);


  WiFi.softAPConfig(Ip, Ip, NMask);
 if (!WiFi.softAP( ssid))
  {
   Serial.println("WiFi.softAP failed.(Password too short?)");
   return;
  }
  IPAddress myIP = WiFi.softAPIP();
  Serial.println();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
// Starting WEB-server

     server.on ( "/", HTTP_handleRoot );
     server.onNotFound ( HTTP_handleRoot );
     server.begin();    
}

void loop() {
  server.handleClient();
   delay(50);
   latitude = "Latitud = " + (String) random(1,90);
   longitude = "Longitud = " + (String) random(-90,-1);
}

void HTTP_handleRoot(void) {
  server.send(200, "text/plain", latitude + "," + longitude);

if( server.hasArg("State") ){
       Serial.println(server.arg("State"));
  }
  server.send(200,"text/html","" );
}
