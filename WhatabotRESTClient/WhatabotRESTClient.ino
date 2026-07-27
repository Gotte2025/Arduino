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
  whatabotClient.sendMessageREST("Hi from Whatabot for ESP8266");
}

void loop() {
 
}
