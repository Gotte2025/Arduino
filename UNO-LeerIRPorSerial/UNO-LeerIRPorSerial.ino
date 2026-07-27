#include <IRremote.h>

#define IR_PIN 2   // Pin donde conectaste el OUT del receptor IR

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);
  Serial.println("Listo para recibir señales IR...");
}

void loop() {
  if (IrReceiver.decode()) {

    Serial.println("Señal recibida:");
    Serial.print("Protocolo: ");
    Serial.println(IrReceiver.decodedIRData.protocol);

    Serial.print("Valor HEX: 0x");
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);

    Serial.print("Bits: ");
    Serial.println(IrReceiver.decodedIRData.numberOfBits);

    Serial.println("----------------------");

    IrReceiver.resume(); // Esperar la siguiente señal
  }
}
