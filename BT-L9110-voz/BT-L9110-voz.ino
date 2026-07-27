/*Lee el valor analogico entregado 
al presionar una tecla y convierte 
ese valor al numero que corresponde a la
tecla presionada
*/
#include <SoftwareSerial.h>
//Aquí conectamos los pins RXD en pin#5,TDX en pin#4 del módulo Bluetooth.
SoftwareSerial BT(2,3);
String voice;
long tiempoactual;
long tiempoanterior=0;
int tiempo=500;
const int AIA = 6;  // (pwm) pin 6 conectado a pin A-IA 
const int AIB = 5;  // (pwm) pin 5 conectado a pin A-IB 
const int BIA = 10; // (pwm) pin 10 conectado a pin B-IA  
const int BIB = 9;  // (pwm) pin 9 conectado a pin B-IB 
//byte velocidadAnterior;
byte velocidad = 160;  
// cambie este valor (100 a 255) para controlar 
// la velocidad de los motores 
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position


void setup()
{
BT.begin(9600); //Velocidad del puerto del bluetooth
Serial.begin(9600); //Abrimos la comunicación serie
 pinMode(AIA, OUTPUT); // fijar los pines como salidas
  pinMode(AIB, OUTPUT);
  pinMode(BIA, OUTPUT);
  pinMode(BIB, OUTPUT);
  myservo.attach(11); 
Serial.println("INICIANDO!");

}
void loop(){
//voice =»»;
while (BT.available()){
delay(20);
char c = BT.read();
voice += c;
}
if (voice.length() > 0) {
Serial.println(voice);
if(voice=="avanzar"){
 avanzar();
}
if(voice=="retroceder"){
  retroceder();
}
if(voice=="acelerar"){

}
if(voice=="frenar"){
  frenar ();
}
if(voice=="derecha"){
  pos= pos + 45 ;
   myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);
}
if(voice=="izquierda"){
 pos= pos - 45 ;
   myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);
  
}
if(voice=="centro"){
 pos= 90;
   myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);
  
}
}
for(int i=0;i<voice.length();i++){
voice.remove(i);

}
}

void avanzar()
{
  analogWrite(AIA, 0);
  analogWrite(AIB, 200);
  analogWrite(BIA, 0);
  analogWrite(BIB, 200);
}

void retroceder()
{
  analogWrite(AIA, 200);
  analogWrite(AIB, 0);
  analogWrite(BIA, 200);
  analogWrite(BIB, 0);
}
void frenar ()
{
  analogWrite(AIA, 0);
  analogWrite(AIB, 0);
  analogWrite(BIA, 0);
  analogWrite(BIB, 0);
}

void izquierda()
{
  analogWrite(AIA, velocidad);
  analogWrite(AIB, 0);
  analogWrite(BIA, 0);
  analogWrite(BIB, velocidad);
}

void derecha()
{
  analogWrite(AIA, 0);
  analogWrite(AIB, velocidad);
  analogWrite(BIA, velocidad);
  analogWrite(BIB, 0);
}
