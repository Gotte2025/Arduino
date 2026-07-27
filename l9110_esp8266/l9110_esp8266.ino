/*
 L9110 motor driver controlando 2 motores CC
 COPIAR Y PEGAR SOBRE EL SKETCH DE ARDUINO
*/

const int AIA = 4;  // (pwm) pin D2 conectado a pin A-IA 
const int AIB = 5;  // (pwm) pin D1 conectado a pin A-IB 
 

byte velocidad = 250;  
// cambie este valor (100 a 255) para controlar 
// la velocidad de los motores 

void setup() {
  pinMode(AIA, OUTPUT); // fijar los pines como salidas
  pinMode(AIB, OUTPUT);
  
}

void loop() {
 avanzar();
    for (int i = 0; i < 2000; i++) {  // Avanza durante 1 segundo (aproximadamente)
   
    delay(1);
  }
retroceder();
 delay (1000);

 
  
}

void avanzar()
{
  analogWrite(AIA, 0);
  analogWrite(AIB, velocidad);
    
  
}

void retroceder()
{
  analogWrite(AIA, velocidad);
  analogWrite(AIB, 0);
  
}

void detener()
{
  analogWrite(AIA, 0);
  analogWrite(AIB, 0);
 delay(1000);
}

void derecha()
{
  analogWrite(AIA, 0);
  analogWrite(AIB, velocidad);

}
