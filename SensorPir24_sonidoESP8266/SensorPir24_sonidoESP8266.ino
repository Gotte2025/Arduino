const int LEDPin= D4;
const int PIRPin= D2;

void setup()
{
  pinMode(LEDPin, OUTPUT);
  pinMode(PIRPin, INPUT);
  pinMode (D1, OUTPUT); //pin configurado como salida
}

void loop()
{
  int value= digitalRead(PIRPin);
 
  if (value == HIGH)
  {
    digitalWrite(LEDPin, HIGH);
    delay(50);
    piratas ();
    digitalWrite(LEDPin, LOW);
    delay(50);
  }
  else
  {
    digitalWrite(LEDPin, LOW);
  }
}

void piratas (){

tone(D1, 293.66, 200);
delay(200);
tone(D1, 293.66, 100);
delay(100);
tone(D1, 293.66, 200);
delay(200);
tone(D1, 293.66, 100);
delay(100);
tone(D1, 293.66, 200);
delay(200);
tone(D1, 293.66, 100);
delay(100);
tone(D1, 293.66, 100);
delay(100);
tone(D1, 293.66, 100);
delay(100);

}