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
int Estado = 1;
int Direccion = 2;
//user interface HTML code----------------
String html = R"***(
<!DOCTYPE html><html><head><title>:: CONTROL AUTO :: </title>
<html>
 <head>

  <title>CONTROL AUTO</title>
  <style>
    
    .centrado{text-align:center;border:1px dotted #000; padding:8px;}
    
    center{margin:16px 0;}
  </style>
</head>
  <body bgcolor=black>
   <br> </br>
     <br> </br>
  <center>
    <h1>SWITCH AUTO</h1> <style> h1 {color: white;}</style>
     <br> </br>
     <br> </br>
      <br> </br>
     <br> </br>
    </center>  
     <p><a href=/ledon>AVANZAR</a></p> <style>  a {color: white;}</style>
     </center>
     <br> </br>
     <br> </br>  
     <center>
    <p><a href=/ledoff>DETENER</a> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href=/derecha> DERECHA</a> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  <a href=/centro>CENTRO</a> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;   <a href=/izquierda>IZQUIERDA</a>    </p>
    <br> </br>
     <br> </br>
     <br> </br>
   </center>
    <p><a href=/retroceder>ATRAS</a></p>
    <br> </br>
     <br> </br>   
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
}
//===============================================
void loop()
{
	server.handleClient();

}

void forward()
{
  Estado= Estado + 1;
  if( Estado > 6 ){
  Estado=6;
}
  switch (Estado)
 {  

case 0:  
 reversa();
 Serial.println("avance Reversa");
break; 

case 1:  
Stop();
 Serial.println("avance Stop");
break;  
case 2:  
segunda(); 
Serial.println("avance 1era");
break; 
case 3:  
  segunda(); 
 Serial.println("avance 2da");
break;  
case 4:  
  tercera();
 Serial.println("avance 3era");
break;  
case 5:  
cuarta(); 
Serial.println("avance 4ta");
break; 
case 6:  
quinta(); 
Serial.println("avance 5era");
break; 

}
 }

void backward()
{
  Estado= Estado - 1; 
    if(Estado < 0 ){
 Estado = 0; 
}
  switch (Estado)
 {  

case 0:  
 reversa();
 Serial.println("avance Reversa");
break; 

case 1:  
Stop();
 Serial.println("avance Stop");
break;  
case 2:  
segunda(); 
Serial.println("avance 1era");
break; 
case 3:  
  segunda(); 
 Serial.println("avance 2da");
break;  
case 4:  
  tercera();
 Serial.println("avance 3era");
break;  
case 5:  
cuarta(); 
Serial.println("avance 4ta");
break; 
case 6:  
quinta(); 
Serial.println("avance 5era");
break; 
}
}


void left()
{
   Direccion= Direccion + 1;
  if( Direccion > 4 ){
  Direccion=4;
}
  switch (Direccion)
 {  

case 0:  
  motorD.write(100);  //sentido horario
 motorI.write(100);  //sentido horario
 Serial.println("Izquierda");
break; 

case 1:  
  motorD.write(120);  //sentido horario
 motorI.write(120);  //sentido horario
 Serial.println("ctroizquierda");
break;  
case 2:  
  motorD.write(135);  //sentido horario
 motorI.write(135);  //sentido horario
Serial.println("Centro");
break; 
case 3:  
    motorD.write(150);  //sentido horario
 motorI.write(150);  //sentido horario
 Serial.println("Ctroderecha");
break;  
case 4:  
  motorD.write(180);  //sentido horario
 motorI.write(180);  //sentido horario
 Serial.println("Derecha");
break; 
 }
}
void right()
{
    Direccion= Direccion - 1;
  if( Direccion  < 0 ){
  Direccion=0;
}
  switch (Direccion)
 {  

case 0:  
  motorD.write(80);  //sentido horario
 motorI.write(80);  //sentido horario
 Serial.println("Izquierda");
break; 

case 1:  
  motorD.write(60);  //sentido horario
 motorI.write(60);  //sentido horario
 Serial.println("ctroizquierda");
break;  
case 2:  
  motorD.write(50);  //sentido horario
 motorI.write(50);  //sentido horario
Serial.println("Centro");
break; 
case 3:  
  motorD.write(45);  //sentido horario
 motorI.write(45);  //sentido horario
 Serial.println("Ctroderecha");
break;  
case 4:  
  motorD.write(40);  //sentido horario
 motorI.write(40);  //sentido horario
 Serial.println("Derecha");
break; 
 }

}
void center()
{
  motorG.write(90);  //sentido antihorario

}

void Stop()
{
  motorD.write(90);  //sentido antihorario
  motorI.write(90);  //sentido antihorario
Estado = 1;

}
void primera()
{
  
  motorD.write(80);  //sentido horario
 motorI.write(100);  //sentido horario
  Serial.println("avance");


}
void segunda()
{
  
  motorD.write(70);  //sentido horario
 motorI.write(120);  //sentido horario
  Serial.println("avance");

}
void tercera()
{
  
  motorD.write(50);  //sentido horario
 motorI.write(140);  //sentido horario
  Serial.println("avance");

}
void cuarta()
{
  
  motorD.write(20);  //sentido horario
 motorI.write(160);  //sentido horario
  Serial.println("avance");

}
void quinta()
{
  
  motorD.write(0);  //sentido horario
 motorI.write(180);  //sentido horario
  Serial.println("avance");

}
void reversa()
{
  
  motorD.write(130);  //sentido horario
 motorI.write(50);  //sentido horario
  Serial.println("avance");

}
