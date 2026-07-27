#include <Servo.h>
#include <FSTools.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include <DHT.h>


#define DHTPIN D2

const byte DNS_PORT = 53;
IPAddress apIP(172, 217, 28, 1);
DNSServer dnsServer;

ESP8266WebServer server(80);

float temperature_celsius;
int temperature_fahrenheit;
int porcentaje_humedad;
int sensacion_termica;
int temperature;
int humidity;
float puntoRocio;

#define DHTTYPE DHT11  // DHT 11 \
  // // Crear objeto para DHT11:
DHT dht = DHT(DHTPIN, DHTTYPE);



void startWebServer() {
  server.on("/", handleRoot);



  server.on("/NUBES.gif", []() {
    getSpiffImg("/NUBES.gif", "image/gif");
  });
  server.on("/lluvia.jpg", []() {
    getSpiffImg("/lluvia.jpg", "image/jpg");
  });
  server.on("/casita.jpg", []() {
    getSpiffImg("/casita.jpg", "image/jpg");
  });

  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("#################### Server BEGIN!! ####################");
}


void handleRoot() {

  String rootWebPage = "<!DOCTYPE html><html><head><title>:: WEATHER HOUSE  :: </title>";
  rootWebPage += "<body bgcolor=WHITE> ";
  rootWebPage += "<center> ";
  rootWebPage += "<h1>WEATHER HOUSE</h1>";
  rootWebPage += "</center> ";
  rootWebPage += "<div class=centrar-imagen> <img src=/casita.jpg alt=Descripción de la imagen> </div> <style> .centrar-imagen {text-align: center;} </style>";
  rootWebPage += "<center> ";
  rootWebPage += "<H3>SEGUN LAS CONDICIONES DEL CLIMA, EL TIEMPO PUEDE SER INESTARBLE !!!.</H3>";
  rootWebPage += "<center> ";
  rootWebPage += "<div class=centrar-imagen> <img src=/lluvia.jpg alt=Descripción de la imagen> </div> <style> .centrar-imagen {text-align: center;} </style>";
  rootWebPage += "<center> ";
  rootWebPage += "<h2>TEMPERATURA: </h2>";
  rootWebPage += "</center> ";
  rootWebPage += " <div class=contenedor-flex> <p>   " + String(temperature_celsius) + " °C </p> </div> <style>.contenedor-flex { display: flex;justify-content: center; /* Centra horizontalmente */align-items: Right; /* Centra verticalmente */ height: 300px; /* Ajusta la altura del contenedor si es necesario */<style>}";
  rootWebPage += "<div class=centrar-imagen> <img src=/lluvia.jpg  alt=Descripción de la imagen> </div> <style> .centrar-imagen {text-align: center;} </style>";
  rootWebPage += "<center> ";
  rootWebPage += "<h2>HUMEDAD: </h2>";
  rootWebPage += "</center> ";
  rootWebPage += " <div class=contenedor-flex> <p>  " + String(porcentaje_humedad) + " % </p> </div> <style>.contenedor-flex { display: flex;justify-content: center; /* Centra horizontalmente */align-items: Right; /* Centra verticalmente */  height: 300px; /* Ajusta la altura del contenedor si es necesario */<style>}";
  rootWebPage += "<div class=centrar-imagen> <img src=/lluvia.jpg  alt=Descripción de la imagen> </div> <style> .centrar-imagen {text-align: center;} </style>";
  rootWebPage += "<center> ";
  rootWebPage += "<h2>SENSACION TERMICA: </h2>";
  rootWebPage += "</center> ";
  rootWebPage += " <div class=contenedor-flex> <p> " + String(sensacion_termica) + " °C </p> </div> <style>.contenedor-flex { display: flex;justify-content: center; /* Centra horizontalmente */align-items: Right; /* Centra verticalmente */  height: 300px; /* Ajusta la altura del contenedor si es necesario */<style>}";
  rootWebPage += "<div class=centrar-imagen> <img src=/lluvia.jpg alt=Descripción de la imagen> </div> <style> .centrar-imagen {text-align: center;} </style>";
  rootWebPage += "</body></html>";
  server.send(200, "text/html", rootWebPage);
}
void handleRoot2() {

  String rootWebPage = "<!DOCTYPE html><html><head><title>:: WEATHER HOUSE :: </title>";
  rootWebPage += "<body bgcolor=lightblue> ";
  rootWebPage += "<center> ";
  rootWebPage += "<h1>WEATHER HOUSE</h1>";
  rootWebPage += "</center> ";
  rootWebPage += "<div class=centrar-imagen> <img src=/casita.jpg alt=Descripción de la imagen> </div> <style> .centrar-imagen {text-align: center;} </style>";
  rootWebPage += "<center> ";
  rootWebPage += "<H3>SEGUN LAS CONDICIONES DEL CLIMA, EL TIEMPO ES BUENO CON MINIMAS POSIBILIDAD DE PRECIPITACIONES !!!.</H3>";
  rootWebPage += "<center> ";
  rootWebPage += "<div class=centrar-imagen> <img src=/NUBES.gif alt=Descripción de la imagen> </div> <style> .centrar-imagen {text-align: center;} </style>";
  rootWebPage += "<center> ";
  rootWebPage += "<h2>TEMPERATURA: </h2>";
  rootWebPage += "</center> ";
  rootWebPage += " <div class=contenedor-flex> <p>   " + String(temperature_celsius) + " °C </p> </div> <style>.contenedor-flex { display: flex;justify-content: center; /* Centra horizontalmente */align-items: Right; /* Centra verticalmente */ height: 300px; /* Ajusta la altura del contenedor si es necesario */<style>}";
  rootWebPage += "<div class=centrar-imagen> <img src=/lluvia.jpg  alt=Descripción de la imagen> </div> <style> .centrar-imagen {text-align: center;} </style>";
  rootWebPage += "<center> ";
  rootWebPage += "<h2>HUMEDAD: </h2>";
  rootWebPage += "</center> ";
  rootWebPage += " <div class=contenedor-flex> <p>  " + String(porcentaje_humedad) + " % </p> </div> <style>.contenedor-flex { display: flex;justify-content: center; /* Centra horizontalmente */align-items: Right; /* Centra verticalmente */  height: 300px; /* Ajusta la altura del contenedor si es necesario */<style>}";
  rootWebPage += "<div class=centrar-imagen> <img src=/lluvia.jpg  alt=Descripción de la imagen> </div> <style> .centrar-imagen {text-align: center;} </style>";
  rootWebPage += "<center> ";
  rootWebPage += "<h2>SENSACION TERMICA: </h2>";
  rootWebPage += "</center> ";
  rootWebPage += " <div class=contenedor-flex> <p> " + String(sensacion_termica) + " °C </p> </div> <style>.contenedor-flex { display: flex;justify-content: center; /* Centra horizontalmente */align-items: Right; /* Centra verticalmente */  height: 300px; /* Ajusta la altura del contenedor si es necesario */<style>}";
  rootWebPage += "<div class=centrar-imagen> <img src=/lluvia.jpg alt=Descripción de la imagen> </div> <style> .centrar-imagen {text-align: center;} </style>";
  rootWebPage += "</body></html>";
  server.send(200, "text/html", rootWebPage);
}



void handleNotFound() {
if (porcentaje_humedad > 50 ){
   handleRoot();  // tell servo to go to position in variable 'pos'
                          // waits 15ms for the servo to reach the position
}
if (porcentaje_humedad < 50 ){
    handleRoot2();  // tell servo to go to position in variable 'pos'
                          // waits 15ms for the servo to reach the position
}
 // handleRoot();
}

void getSpiffImg(String path, String TyPe) {
  if (SPIFFS.exists(path)) {
    File file = SPIFFS.open(path, "r");
    server.streamFile(file, TyPe);
    file.close();
  }
}


void sensordht() {
  // Lectura de Sensor:
  temperature_celsius = dht.readTemperature();
  temperature_fahrenheit = dht.readTemperature(true);
  porcentaje_humedad = dht.readHumidity();
  sensacion_termica = dht.computeHeatIndex(temperature_celsius, porcentaje_humedad, false);
}

void punto_rocio() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  puntoRocio = pow((humidity / 100), 0.125) * (110 + temperature) - 110;
}





void setup() {
  Serial.begin(115200);
  while (!Serial) {
    delay(1);
  }

  WiFi.mode(WIFI_AP);  //Only Access point
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP("WEATHER HOUSE");
  dnsServer.start(DNS_PORT, "*", apIP);
  SPIFFS.begin();
  Serial.println("----- Web Server Start ------");
  startWebServer();
  dht.begin();
    
}

void loop() {
  dnsServer.processNextRequest();
  server.handleClient();
  sensordht();
  punto_rocio();
 
}
