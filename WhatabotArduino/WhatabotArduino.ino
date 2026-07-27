#include <ArduinoWiFiServer.h>
#include <BearSSLHelpers.h>
#include <CertStoreBearSSL.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiGratuitous.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiType.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiClientSecureBearSSL.h>
#include <WiFiServer.h>
#include <WiFiServerSecure.h>
#include <WiFiServerSecureBearSSL.h>
#include <WiFiUdp.h>

#include <WhatabotAPIClient.h>
#include <WiFiManager.h>

#define WHATABOT_API_KEY "a07f5530-06cf-4cae-9882"
#define WHATABOT_CHAT_ID "5493496418942"
#define WHATABOT_PLATFORM "whatsapp"

WiFiManager wifiManager;
WhatabotAPIClient whatabotClient(WHATABOT_API_KEY, WHATABOT_CHAT_ID, WHATABOT_PLATFORM);

//You must connect to the generated network, and from there, you can set the SSID and password for your Wi-Fi network to which the ESP8266 will connect.
//If you dont want to use WiFiManager you can still connect to WiFi using other logic.
#define AP_SSID "Sanchez - Santucci"
#define AP_PASS "40575645"

void setup() {
  Serial.begin(115200);
  wifiManager.autoConnect(AP_SSID, AP_PASS);
  whatabotClient.begin();
  whatabotClient.onMessageReceived(onMessageReceived); 
  whatabotClient.onServerResponseReceived(onServerResponseReceived);
}

void loop() {
  whatabotClient.loop(); 
  
}

void onServerResponseReceived(String message) {
  Serial.println(message); 
}

void onMessageReceived(String message) {
  message.toUpperCase();
  Serial.println(message);

  if (message.equals("START")) {
    whatabotClient.sendMessageWS("Starting");
    // Add your logic for starting here
  } else if (message.equals("STOP")) {
    whatabotClient.sendMessageWS("Stopping");
    // Add your logic for stopping here
  } else if (message.equals("PAUSE")) {
    whatabotClient.sendMessageWS("Pausing");
    // Add your logic for pausing here
  } else if (message.equals("RESUME")) {
    whatabotClient.sendMessageWS("Resumming");
    // Add your logic for resuming here
  } else {
    whatabotClient.sendMessageWS("Unknown command");
    // Handle unknown commands here (optional)
  }
  
}
