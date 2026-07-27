//====================================
//ESP8266 Access Point Control of LED
//====================================
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "Arduino.h"
#include <Servo.h>
Servo motorD;  // crea el objeto servo
Servo motorI;  // crea el objeto servo
Servo motorG;  // crea el objeto servo
#define PMD 4 // vincula el servo al pin D2 Esp8266
#define PMI 5 // vincula el servo al pin D1 Esp8266
#define PMG 2 // vincula el servo al pin D4 Esp8266
int Velocidad; 


//user interface HTML code----------------
String html = R"***(
<!DOCTYPE html><html><head><title>:: CONTROL AUTO :: </title>
<html>
 <head>

  <title>   CONTROL AUTO</title>
  <style>
    
    .centrado{text-align:center;border:1px dotted #000; padding:8px;}
    
    center{margin:16px 0;}
  </style>
</head>
  <body>
  <center>
    <h1>SWITCH AUTO</h1>
    </center>
    <center>
     <p><a href=/ledon>AVANZAR</a></p>
     </center>
     <center>
    <p><a href=/ledoff>DETENER</a></p>
    </center>
        <center>
    <p><a href=/retroceder>ATRAS</a></p>
    </center>
         <center>
    <p><a href=/derecha>DERECHA</a></p>
    </center>
          <center>
    <p><a href=/izquierda>IZQUIERDA</a></p>
    </center>
          <center>
    <p><a href=/centro>CENTRO</a></p>
    </center>
  </body>
</html>
)***";
//--------------------------------------

const char* ssid = "Control Auto";
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
  //digitalWrite(led, 1);
  forward();
  server.send(200, "text/html", html);
}
void retroceder()
{
  //digitalWrite(led, 0);
 backward();
  server.send(200, "text/html", html);
}
void ledoff()
{
  //digitalWrite(led, 0);
  Stop();
  server.send(200, "text/html", html);
}

void derecha()
{
  //digitalWrite(led, 0);
 right();
  server.send(200, "text/html", html);
}
void izquierda()
{
  //digitalWrite(led, 0);
  left();
  server.send(200, "text/html", html);
}
void centro()
{
  //digitalWrite(led, 0);
  center();
  server.send(200, "text/html", html);
}
//===============================================
void setup()
{
//  pinMode(led, OUTPUT); delay(1000);
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
   server.on("/retroceder", retroceder);
   server.on("/derecha", derecha);
   server.on("/izquierda", izquierda);
   server.on("/centro", centro);
	server.begin();
	Serial.println("HTTP server started");
  motorD.attach(PMD);
  motorI.attach(PMI);
  motorG.attach(PMG);
  Velocidad=135;
}
//===============================================
void loop()
{
	server.handleClient();
}

void forward()
{
  
  motorD.write(Velocidad);  //sentido horario
  motorI.write(Velocidad);  //sentido horario
  Serial.println("avance");
}

void backward()
{
  motorD.write(0);  //sentido antihorario
  motorI.write(0);  //sentido antihorario
  Serial.println("retroceso");
}
void left()
{
  motorG.write(135);  //sentido antihorario
  
  Serial.println("izquierda");
}
void right()
{
  motorG.write(45);  //sentido antihorario
 
}
void center()
{
  motorG.write(90);  //sentido antihorario
 
}

void Stop()
{
  motorD.write(90);  //sentido antihorario
  motorI.write(90);  //sentido antihorario


}
