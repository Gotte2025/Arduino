#define SensorNivel A0
#define Led_13 13
int Nivel_liquidos;

void setup()
{
  Serial.begin(9600);
  pinMode(Led_13, OUTPUT);
}

void loop()
{
   Lectura_Sensor ();
   
  if (Nivel_liquidos > 100) {
    digitalWrite(Led_13, HIGH);
  }
  if (Nivel_liquidos < 101) {

    digitalWrite(Led_13, LOW);
  }



}

void Lectura_Sensor (){
  Nivel_liquidos = analogRead(SensorNivel);
  Serial.println(SensorNivel);
}
