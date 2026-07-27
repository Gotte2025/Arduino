/*
  WriteMultipleFields
  
  Description: Writes values to fields 1,2,3,4 and status in a single ThingSpeak update every 20 seconds.
  
  Hardware: ESP8266 based boards
  
  !!! IMPORTANT - Modify the secrets.h file for this project with your network connection and ThingSpeak channel details. !!!
  
  Note:
  - Requires ESP8266WiFi library and ESP8622 board add-on. See https://github.com/esp8266/Arduino for details.
  - Select the target hardware from the Tools->Board menu
  - This example is written for a network using WPA encryption. For WEP or WPA, change the WiFi.begin() call accordingly.
  
  ThingSpeak ( https://www.thingspeak.com ) is an analytic IoT platform service that allows you to aggregate, visualize, and 
  analyze live data streams in the cloud. Visit https://www.thingspeak.com to sign up for a free account and create a channel.  
  
  Documentation for the ThingSpeak Communication Library for Arduino is in the README.md folder where the library was installed.
  See https://www.mathworks.com/help/thingspeak/index.html for the full ThingSpeak documentation.
  
  For licensing information, see the accompanying license file.
  
  Copyright 2018, The MathWorks, Inc.
*/
//Librerias
#include "ThingSpeak.h"
#include "secrets.h"
#include <ESP8266WiFi.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>
#include "MQ7.h"





char ssid[] = SECRET_SSID;  // your network SSID (name)
char pass[] = SECRET_PASS;  // your network password
int keyIndex = 0;           // your network key Index number (needed only for WEP)
WiFiClient client;

unsigned long myChannelNumber = SECRET_CH_ID;
const char* myWriteAPIKey = SECRET_WRITE_APIKEY;

// Pines


#define DHTPIN D2
#define LED D4
#define A_PIN A0
#define VOLTAGE 5
#define LDRPin D5

// init MQ7 device
MQ7 mq7(A_PIN, VOLTAGE);

// Initialize our values
float number1 = 0;
float number2 = 0;
int number3 = 0;
int number4 = 0;
int number5 = 0;
float number6 = 0;
int number7 = 0;

String myStatus = "";
int x = 0;


// Creacion de variables:
float temperature_celsius;
int temperature_fahrenheit;
int porcentaje_humedad;
int sensacion_termica;
int temperature;
int humidity;
int C2O;
float puntoRocio;
int ilum;

#define DHTTYPE DHT11  // DHT 11 \
 // Crear objeto para DHT11:
DHT dht = DHT(DHTPIN, DHTTYPE);


void setup() {
  Serial.begin(115200);  // Initialize serial
  pinMode(LDRPin, INPUT);
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);  // Initialize ThingSpeak
  //sensores
  dht.begin();
  Serial.println("Calibrating MQ7");
  mq7.calibrate();  // calculates R0
  Serial.println("Calibration done!");
}

void loop() {
  //pinMode(LED,OUTPUT);
  // Connect or reconnect to WiFi
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while (WiFi.status() != WL_CONNECTED) {
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);
    }
    Serial.println("\nConnected.");
    // digitalWrite(LED,1);
  }

  // set the fields with the values
  ThingSpeak.setField(1, number1);  // field 1-temperature_celsius
  ThingSpeak.setField(2, number2);  // field 2-temperature_fahrenheit
  ThingSpeak.setField(3, number3);  //
  ThingSpeak.setField(4, number4);  //
  ThingSpeak.setField(5, number5);
  ThingSpeak.setField(6, number6);
  ThingSpeak.setField(7, number7);

  // figure out the status message
  if (number1 > number2) {
    myStatus = String("field1 is greater than field2");
  } else if (number1 < number2) {
    myStatus = String("field1 is less than field2");
  } else {
    myStatus = String("field1 equals field2");
  }

  // set the status
  ThingSpeak.setStatus(myStatus);

  // write to the ThingSpeak channel
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if (x == 200) {
    Serial.println("Channel update successful.");
  } else {
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }

  //Lee Sensor y calcula
  sensordht();
  punto_rocio();
  Monoxido();
  iluminacion_led();

  // traslada valores


  number1 = temperature_celsius;
  number2 = temperature_fahrenheit;
  number3 = porcentaje_humedad;
  number4 = sensacion_termica;
  number5 = puntoRocio;
  number6 = C2O;
  number7 = ilum;


  delay(20000);  // Wait 20 seconds to update the channel again
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

void Monoxido() {
  C2O = mq7.readPpm();
}

void iluminacion_led() {

  ilum = digitalRead(LDRPin);
}
