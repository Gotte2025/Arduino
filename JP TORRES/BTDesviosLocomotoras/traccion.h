
// Pines para el motor A
const int enA = 3;  // Pin PWM para controlar la velocidad del Motor A
const int in1 = 2;  // Pin para el control de dirección 1 del Motor A
const int in2 = 4;  // Pin para el control de dirección 2 del Motor A
int acelerar = 0;
void velocidad () {
  analogWrite(enA, acelerar);   // Velocidad máxima (0-255)
}

void forward()
{
  digitalWrite(in1, HIGH); // Dirección 1 HIGH
  digitalWrite(in2, LOW);  // Dirección 2 LOW
  velocidad ();

}

void backward()
{
  digitalWrite(in1, LOW);  // Dirección 1 LOW
  digitalWrite(in2, HIGH); // Dirección 2 HIGH
  velocidad ();
}



void Stop()
{
  acelerar = 0;
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  velocidad ();
}
