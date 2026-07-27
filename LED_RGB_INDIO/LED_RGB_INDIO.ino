// Definimos los pines para el LED RGB
const int pinRojo = D8;
const int pinVerde = D7;
const int pinAzul = D6;

void setup() {
  // put your setup code here, to run once:
  pinMode(pinRojo, OUTPUT);
  pinMode(pinVerde, OUTPUT);
  pinMode(pinAzul, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  ROJO();
  delay(1000);
  // VERDE();
  // delay(1000);
  // AZUL();
  // delay(1000);
}

void ROJO() {
  analogWrite(pinRojo, 153);
  analogWrite(pinVerde, 0);
  analogWrite(pinAzul, 0);
}
void VERDE() {
  analogWrite(pinRojo, 50);
  analogWrite(pinVerde, 250);
  analogWrite(pinAzul, 100);
}
void AZUL() {
  analogWrite(pinRojo, 100);
  analogWrite(pinVerde, 50);
  analogWrite(pinAzul, 200);
}