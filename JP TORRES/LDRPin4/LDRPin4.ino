 int ldrPin = A0; // Pin analógico para el LDR
    int ledPin = 4;  // Pin digital para el LED
    int umbral = 300; // Umbral de luz (ajustar según necesidad)

    void setup() {
      pinMode(ledPin, OUTPUT); // Configurar el pin del LED como salida
      // Serial.begin(9600); // Opcional: para ver el valor del LDR en el Monitor Serial
    }

    void loop() {
      int valorLDR = analogRead(ldrPin); // Leer el valor del LDR
     Serial.print("valorLDR: ");
     Serial.println(valorLDR); // Opcional: muestra el valor del LDR
delay(100);
      if (valorLDR < umbral) { // Si hay poca luz (oscuro)
        digitalWrite(ledPin, HIGH); // Enciende el LED
      } else { // Si hay suficiente luz
        digitalWrite(ledPin, LOW);  // Apaga el LED
      }
      delay(50); // Pequeña espera para estabilizar la lectura
    }
