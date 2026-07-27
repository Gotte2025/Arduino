// Definimos los pines para el LED RGB
const int pinRojo = D8;
const int pinVerde = D7;
const int pinAzul = D6;

void setup() {
  // Configuramos los pines como salida
  pinMode(pinRojo, OUTPUT);
  pinMode(pinVerde, OUTPUT);
  pinMode(pinAzul, OUTPUT);
}

void loop() {
  // Valores de color R, G y B (0-255)
  int R = 253; // Cambia este valor Rosa
  int G = 0; // Cambia este valor Rosa
  int B = 153;  // Cambia este valor Rosa
 
  
 
  // Llamamos a la función para establecer el color
  setColor(R, G, B);
 
  // Espera 1 segundo antes de cambiar el color
  delay(1000);

}

// Función para establecer el color del LED RGB
void setColor(int red, int green, int blue) {
  analogWrite(pinRojo, red);
  analogWrite(pinVerde, green);
  analogWrite(pinAzul, blue);
}