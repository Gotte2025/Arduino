/**
 * @file Whatsapp_Message.ino
 * @author Hafidh Hidayat (hafidhhidayat@hotmail.com)
 * @brief Example Whatsapp Message
 * 
 * @copyright Copyright (c) 2022
 * 
 * Github :
 * https://github.com/hafidhh
 * https://github.com/hafidhh/Callmebot_ESP8266
 */

#include <ESP8266WiFi.h>
#include <Callmebot_ESP8266.h>

const char* ssid = "xxxxxxxxxxx";
const char* password = "xxxxxxxxxx";
// Note :
// phoneNumber : Indonesia +62, Example: "+62897461238"
// apiKey : Follow instruction on https://www.callmebot.com/blog/free-api-whatsapp-messages/
String phoneNumber = "+5493496418942";
String apiKey = "2335187";
String messsage = "Esto es una Prueba";

void setup() {
	Serial.begin(115200);

	WiFi.begin(ssid, password);
	Serial.println("Connecting");
	while(WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}
	Serial.println("");
	Serial.print("Connected to WiFi network with IP Address: ");
	Serial.println(WiFi.localIP());

	Callmebot.begin();

	// Whatsapp Message
	Callmebot.whatsappMessage(phoneNumber, apiKey, messsage);
	Serial.println(Callmebot.debug());

}

void loop() {
	
}
