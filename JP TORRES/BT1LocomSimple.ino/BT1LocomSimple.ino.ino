/*app con BT para L298 sin servos
*/

int retardo = 30; //velocidad servo
int estadoluz = 0; // estado LUZ
int const luz = 13; //Led pin 13
// Pines para el motor A
const int enA = 3;  // Pin PWM para controlar la velocidad del Motor A
const int in1 = 2;  // Pin para el control de dirección 1 del Motor A
const int in2 = 4;  // Pin para el control de dirección 2 del Motor A
int acelerar = 0;
int command; //Int to store app command state.


void iluminacion() {
  if (estadoluz == 0)
  {
    digitalWrite(luz, 1);
  }
  if ( estadoluz == 1)
  {
    digitalWrite(luz, 0);;
  }
  estadoluz = !estadoluz;

  delay(2);
}

void velocidad () {
  analogWrite(enA, acelerar);   // Velocidad máxima (0-255)
}

void forward()
{
  digitalWrite(in1, HIGH); // Dirección 1 HIGH
  digitalWrite(in2, LOW);  // Dirección 2 LOW
  

}

void backward()
{
  digitalWrite(in1, LOW);  // Dirección 1 LOW
  digitalWrite(in2, HIGH); // Dirección 2 HIGH
 
}



void Stop()
{
  acelerar = 0;
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  
}


void ControlBT () {
  if (Serial.available() > 0)
  {
    command = Serial.read();

    switch (command) {
      case 'F': forward();  break;
      case 'B': backward();  break;
      case 'S': Stop();  break;
      case '6': acelerar = 70; break;
      case '7': acelerar = 180; break;
      case '8': acelerar = 250; break;
      case '9': iluminacion(); break;


        delay(2);
    }
  }
}
void setup() {
 
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
    pinMode(luz, OUTPUT);
}

void loop() {
 ControlBT ();
 velocidad ();
}
