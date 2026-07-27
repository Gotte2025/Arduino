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
#define A_PIN A0
#define VOLTAGE 5
MQ7 mq7(A_PIN, VOLTAGE);
int C2O;

char ssid[] = SECRET_SSID;  // your network SSID (name)
char pass[] = SECRET_PASS;  // your network password
int keyIndex = 0;           // your network key Index number (needed only for WEP)
WiFiClient client;

unsigned long myChannelNumber = SECRET_CH_ID;
const char* myWriteAPIKey = SECRET_WRITE_APIKEY;


// Initialize our values
float number1 = 0;


String myStatus = "";
int x = 0;

//sensores



// Creacion de variables:

int valor_monoxido;

void Monoxido() {
C2O=mq7.readPpm();
}
void setup() {
  Serial.begin(115200);  // Initialize serial

  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);  // Initialize ThingSpeak
  //sensores
 mq7.calibrate();   // calculates R0
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


  // traslada valores


  number1 = valor_monoxido;
  
  
  delay(20000);  // Wait 20 seconds to update the channel again
}
