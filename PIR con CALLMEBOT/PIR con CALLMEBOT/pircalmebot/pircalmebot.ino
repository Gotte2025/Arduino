#include <WiFi.h>
#include <Callmebot_ESP32.h>

const char* ssid = "NombreWIFI"; // Nombre de Red Wifi
const char* password = "Contraseña";  // Contraseña 
String phoneNumber = "+NUMero de telefono"; // Numero de Telefono 
String apiKey = "API KEY";  // API KEY

const int pirPin = 5;     // Pin del sensor PIR
const int ledPin = 4;     // Pin del LED

int pirState = LOW;       // Estado actual del PIR
int lastPirState = LOW;   // Último estado del PIR

unsigned long lastMessageTime = 0;         // Tiempo del último mensaje enviado
const unsigned long messageInterval = 30000; // Intervalo en milisegundos (ej. 30 segundos)
bool firstMessageSent = false;             // Bandera para el primer mensaje

void setup() {
  Serial.begin(115200);
  
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);  // LED apagado al inicio

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  int pirReading = digitalRead(pirPin);  // Lee el estado del PIR

  // Si el estado del PIR ha cambiado
  if (pirReading != lastPirState) {
    lastPirState = pirReading;
    Serial.println("Ocurrio un Movimiento");
    // Si detecta movimiento
    if (pirReading == HIGH) {
      digitalWrite(ledPin, HIGH);  // Enciende el LED
      
      // Verifica si es el primer mensaje o si ha pasado el intervalo
      if (!firstMessageSent || (millis() - lastMessageTime >= messageInterval)) {
        String mensaje = "Alerta: Movimiento detectado por el sensor PIR";  // Mensaje para la notificacion 
        Callmebot.whatsappMessage(phoneNumber, apiKey, mensaje);
        Serial.println("Mensaje enviado: " + mensaje);

        lastMessageTime = millis();  // Actualiza el tiempo del último mensaje
        firstMessageSent = true;     // Marca el primer mensaje como enviado
      }
    } else {
      delay(2000);
      digitalWrite(ledPin, LOW);  // Apaga el LED si no hay movimiento
    }
  }
}

