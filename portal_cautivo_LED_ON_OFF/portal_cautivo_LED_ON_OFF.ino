//====================================
//ESP8266 Access Point Control of LED
//====================================
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
//user interface HTML code----------------
String html = R"***(
<!DOCTYPE html>
<html>
  <head>    
    <title>SWITCH LED</title>
  </head>
  <body>
    <h1>SWITCH LED</h1>
    <p><a href=/ledon>LED on</a></p>
    <p><a href=/ledoff>LED off</a></p>
  </body>
</html>
)***";
//--------------------------------------
#define led D4
const char* ssid = "ControlLed";
IPAddress IPaddr (192, 168, 168, 168);
IPAddress IPmask(255, 255, 255, 0);
ESP8266WebServer server(80);
//--------------------------------------
void handleRoot()
{
  server.send(200, "text/html", html);
}
void ledon()
{
  digitalWrite(led, 1);
  server.send(200, "text/html", html);
}
void ledoff()
{
  digitalWrite(led, 0);
  server.send(200, "text/html", html);
}
//===============================================
void setup()
{
  pinMode(led, OUTPUT); delay(1000);
	Serial.begin(115200);
	Serial.println();
	Serial.print("Configuring access point...");
  WiFi.softAP(ssid);
  WiFi.softAPConfig(IPaddr, IPaddr, IPmask); 
	IPAddress myIP = WiFi.softAPIP();
	Serial.print("AP IP address: ");
	Serial.println(myIP);
	server.on("/", handleRoot);
  server.on("/ledon", ledon);
  server.on("/ledoff", ledoff);
	server.begin();
	Serial.println("HTTP server started");
}
//===============================================
void loop()
{
	server.handleClient();
}