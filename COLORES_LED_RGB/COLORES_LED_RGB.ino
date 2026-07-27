// Definimos los pines para el LED RGB
const int pinRojo = 11;
const int pinVerde = 10;
const int pinAzul = 9;

void setup() {
  // Configuramos los pines como salida
  pinMode(pinRojo, OUTPUT);
  pinMode(pinVerde, OUTPUT);
  pinMode(pinAzul, OUTPUT);
}

void loop() {
  // Valores de color R, G y B (0-255)
  int R = 250; // Cambia este valor Rosa
  int G = 1; // Cambia este valor Rosa
  int B = 1;  // Cambia este valor Rosa
 
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