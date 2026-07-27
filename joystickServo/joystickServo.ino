#include <Servo.h>

#define PIN_VRx A0
#define PIN_VRy A1
#define PIN_SW 2
#define PIN_SERVO 6

Servo motor;
int x, y;
int x_ang, y_ang;


void setup() {
  // inicializar monitor serie a 9600 baudios
  Serial.begin(9600);
  
  // configurar el pin del pulsador como entrada con pullup
  pinMode( PIN_SW, INPUT_PULLUP );

  // inicializar el servo para trabajar con el pin 6
  motor.attach(PIN_SERVO);

  // colocar el servo en la posición de 0 grados
  motor.write(0);
  
}

void loop() {
  // leer posición del joystick con Arduino
  x = analogRead(PIN_VRx);
  y = analogRead(PIN_VRy);

  // mapear los valores a grados
  x_ang = map( x, 0, 1023, 0, 180 );
  y_ang = map( y, 0, 1023, 0, 180 );

  // Imprimir datos al monitor serie
  Serial.print( "X_ang:" );
  Serial.print(x_ang);
  Serial.print("  ");

  Serial.print( "Y_ang:" );
  Serial.print(y_ang);
  Serial.print( " SW:");
  Serial.print( digitalRead(PIN_SW) );
  Serial.println();

  // actualizar ángulo del motor
  motor.write( x_ang );

  // esperar 250 ms
  delay(250);
}