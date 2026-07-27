/*Código simple para la comunicación por voz y BT
*/
char C;
String voice;

void setup() {
Serial.begin(9600);
pinMode(13,OUTPUT);
pinMode(12,OUTPUT);

}

void loop() {
  if(Serial.available()>0);
  { 
  voice=Serial.readString();
  Serial.print(voice);
  if(voice=="prender")
  {
    digitalWrite(13,HIGH);
    digitalWrite(12,HIGH);
  }
  else if(voice=="apagar"){
   digitalWrite(13,LOW);
    digitalWrite(12,LOW);
  }

}
}
