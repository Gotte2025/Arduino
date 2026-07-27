
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include "archivos.hpp";
#include "pagina.hpp";

const byte DNS_PORT = 53;
IPAddress apIP(172, 217, 28, 1);
DNSServer dnsServer;

ESP8266WebServer server(80);




//LDR
const int LDRPin = A0;
//variables LDR
const long A = 1000; // Resistencia en oscuridad K
const int B = 15; // Resistencia a la luz (10 lux)
const int Rc = 10; // Resistencia calibracion K
int v;
int ilum;

void startWebServer() {
  server.on("/", handleRoot);

// } );
  
  server.on("/coca.jpg", []() {
    getSpiffImg("/coca.jpg", "image/jpg");
  } );
   server.on("/bandera.gif", []() {
    getSpiffImg("/bandera.gif", "image/gif");
  } );
   server.on("/iluminacion", []() {
    analogRead(ilum);
  } );
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("#################### Server BEGIN!! ####################");
}


void handleRoot() {

  String rootWebPage = "<!DOCTYPE html><html><head><title>:: COCA COLA :: </title>";
  rootWebPage += "<body bgcolor=red> ";
  rootWebPage += "</head><body\"><h1><font color=white>Juntos para algo mejor!</h1>";
  rootWebPage += "<img src=\"/bandera.gif\" alt=\"\"  height=300 width=350 /><br/>";
  rootWebPage += "<img src=\"/coca.jpg\" alt=\"\"  height=30 width=40 /><br/>";
  rootWebPage += "<p>=iluminacion: " + String(ilum)+ " % </p>"; // Asi se suben los valores a la Access point
  rootWebPage += "</body></html>";

  server.send(200, "text/html", rootWebPage);
}

void handleRoot2() {

  String rootWebPage = "<!DOCTYPE html><html><head><title>:: LDR :: </title>";
  rootWebPage += "<body bgcolor=blue> ";
  rootWebPage += "</head><body\"><h1><font color=white>iluminado!</h1>";
  rootWebPage += "<img src=\"/bandera.gif\" alt=\"\"  height=300 width=350 /><br/>";
 rootWebPage += "ilum";
  rootWebPage += "<img src=\"/coca.jpg\" alt=\"\"  height=30 width=40 /><br/>";
  
   rootWebPage += "</body></html>";

  server.send(200, "text/html", rootWebPage);
}

void handleNotFound() {
  iluminacion ();
  Serial.println(ilum);
  if(ilum < 101){
handleRoot();
  }
   if(ilum > 99){
handleRoot2();
  }
  
}

void getSpiffImg(String path, String TyPe) {
  if (SPIFFS.exists(path)) {
    File file = SPIFFS.open(path, "r");
    server.streamFile(file, TyPe);
    file.close();
  }
}







void setup() {
  Serial.begin(115200);
  while (!Serial) {
    delay(1);
  }

  WiFi.mode(WIFI_AP);           //Only Access point
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP("LDR");
  dnsServer.start(DNS_PORT, "*", apIP);
  SPIFFS.begin();
  Serial.println("----- Web Server Start ------");
  startWebServer();
}

void loop() {
  dnsServer.processNextRequest();
  server.handleClient();

}
void iluminacion ()
{
  

  v = analogRead(LDRPin);

  ilum = ((long)v*A*10)/((long)B*Rc*(1024-v));
}
