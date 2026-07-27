/*Lee el valor analogico entregado 
al presionar una tecla y convierte 
ese valor al numero que corresponde a la
tecla presionada
*/
#include <SoftwareSerial.h>
//Aquí conectamos los pins RXD en pin#5,TDX en pin#4 del módulo Bluetooth.
SoftwareSerial BT(4,5);
String voice;
long tiempoactual;
long tiempoanterior=0;
int tiempo=500;

boolean on1;
boolean on2;
boolean on3;
boolean on4;
boolean on5;

int ojo_derecho=12;
int ojo_izquierdo=13;
int derecha=11;
int corazon=10; 
int izquierda=9;

void setup()
{
BT.begin(9600); //Velocidad del puerto del bluetooth
Serial.begin(9600); //Abrimos la comunicación serie
pinMode(ojo_derecho,OUTPUT);
pinMode(ojo_izquierdo,OUTPUT);
pinMode(derecha,OUTPUT);
pinMode(corazon,OUTPUT);
pinMode(izquierda,OUTPUT);
Serial.println("INICIANDO!");
prueba ();
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
if(voice=="ojo derecho"){
  on1=!on1;
  digitalWrite(ojo_derecho,on1? HIGH:LOW);
}
if(voice=="ojo izquierdo"){
  on2=!on2;
  digitalWrite(ojo_izquierdo,on2? HIGH:LOW);
}
if(voice=="derecha"){
  on3=!on3;
  digitalWrite(derecha,on3? HIGH:LOW);
}
if(voice=="corazón"){
  on4=!on4;
  digitalWrite(corazon,on4? HIGH:LOW);
}
if(voice=="izquierda"){
  on5=!on5;
  digitalWrite(izquierda,on5? HIGH:LOW);
}
if(voice=="latido"){
  for(int i=0;i<10;i++){
  digitalWrite(corazon,1);
  delay(100);
  digitalWrite(corazon,0);
  delay(100);}
  on4=!on4;
  digitalWrite(corazon,on4? HIGH:LOW);
  
}
if(voice=="latido fuerte"){
  for(int i=0;i<10;i++){
  digitalWrite(corazon,1);
  delay(50);
  digitalWrite(corazon,0);
  delay(50);}
  on4=!on4;
  digitalWrite(corazon,on4? HIGH:LOW);
  }

if(voice=="alegre"){
  digitalWrite(ojo_derecho,1);
  digitalWrite(ojo_izquierdo,1);
  delay(100);
  for(int i=0;i<10;i++){
  digitalWrite(ojo_derecho,1);
  delay(500);
  digitalWrite(ojo_derecho,0);
  delay(500);
 }
 on1=!on1;
  digitalWrite(ojo_derecho,on1? HIGH:LOW);
   on2=!on2;
  digitalWrite(ojo_izquierdo,on2? HIGH:LOW);
  }
}
for(int i=0;i<voice.length();i++){
voice.remove(i);

}
}

void prueba ()
{
digitalWrite(ojo_derecho,HIGH);
delay(50);
digitalWrite(ojo_izquierdo,HIGH);
delay(50);
digitalWrite(derecha,HIGH);
delay(50);
digitalWrite(corazon,HIGH);
delay(50);
digitalWrite(izquierda,HIGH);
delay(2000);
digitalWrite(ojo_derecho,LOW);
delay(50);
digitalWrite(ojo_izquierdo,LOW);
delay(50);
digitalWrite(derecha,LOW);
delay(50);
digitalWrite(corazon,LOW);
delay(50);
digitalWrite(izquierda,LOW);
delay(2000);

}
