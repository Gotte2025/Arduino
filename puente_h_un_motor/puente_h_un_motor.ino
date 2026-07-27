int entrada1 = 2;
int entrada2 = 3;
int enableA = 5;

void setup() {
  pinMode(entrada1, OUTPUT);
  pinMode(entrada2, OUTPUT);
  pinMode(enableA, OUTPUT);
}

void loop() {
  digitalWrite(entrada1, HIGH);
  digitalWrite(entrada2, LOW);
  analogWrite(enableA, 128); // Equivalente a 50 %
  delay(3000);
  digitalWrite(entrada1, HIGH);
  digitalWrite(entrada2, LOW);
  analogWrite(enableA, 255);
  delay(3000);
  digitalWrite(entrada1, LOW);
  digitalWrite(entrada2, LOW);
  analogWrite(enableA, 255); // Equivalente al 100 %
  delay(3000);
}
