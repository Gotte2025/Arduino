// Juan Antonio Villalpando
// kio4.com

void setup() { 
Serial.begin(9600);
}

void loop() { 
if(Serial.available() > 1)
   {
      int grados = Serial.read();
      int servo = Serial.read();
      Serial.print("Servo = ");
      Serial.println(servo);
      Serial.print("Grados = ");
      Serial.println(grados);
   } // =>Fin del available

}
