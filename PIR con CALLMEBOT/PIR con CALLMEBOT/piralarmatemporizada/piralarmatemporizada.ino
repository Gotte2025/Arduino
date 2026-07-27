
const int pirPin = 2;     // Pin del sensor PIR
const int ledPin = 13;     // Pin del LED

int pirState = LOW;       // Estado actual del PIR
int lastPirState = LOW;   // Último estado del PIR

unsigned long lastMessageTime = 0;         // Tiempo del último mensaje enviado
const unsigned long messageInterval = 60000; // Intervalo en milisegundos (ej. 30 segundos)
bool firstMessageSent = false;             // Bandera para el primer mensaje

void setup() {
  Serial.begin(115200);
  
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);  // LED apagado al inicio

  
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
  
        Serial.println("Mensaje enviado: ");

        lastMessageTime = millis();  // Actualiza el tiempo del último mensaje
        firstMessageSent = true;     // Marca el primer mensaje como enviado
      }
    } else {
      delay(2000);
      digitalWrite(ledPin, LOW);  // Apaga el LED si no hay movimiento
     
    }
  }
  Serial.println(pirReading);
}
