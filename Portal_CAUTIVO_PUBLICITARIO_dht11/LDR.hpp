//LDR
const int LDRPin = A0;
//variables LDR
const long A = 1000; // Resistencia en oscuridad K
const int B = 15; // Resistencia a la luz (10 lux)
const int Rc = 10; // Resistencia calibracion K
int v;
int ilum;

void iluminacion ()
{
  

  v = analogRead(LDRPin);

  ilum = ((long)v*A*10)/((long)B*Rc*(1024-v));
}
