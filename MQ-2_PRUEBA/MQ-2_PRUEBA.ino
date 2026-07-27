// Define el pin al que está conectado el sensor MQ-2
const int mq2Pin = A0; //  Pin analógico A0

void setup() {
  // Inicializa la comunicación serial para mostrar los datos
  Serial.begin(9600);
}

void loop() {
  // Lee el valor analógico del sensor
  int sensorValue = analogRead(mq2Pin);

  // Imprime el valor leído en el monitor serial
  Serial.print("Valor analógico del sensor MQ-2: ");
  Serial.println(sensorValue);

  // Espera un breve período de tiempo antes de la próxima lectura
  delay(500); // Espera 500 milisegundos
}
