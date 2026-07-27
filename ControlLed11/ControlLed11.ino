
#include <SoftwareSerial.h>
SoftwareSerial BT(2,3 );
// El TX del módulo BT va al pin 2 del Arduino
// El RX del módulo BT va al pin 3 del Arduino

void setup() {
    BT.begin(9600);
    pinMode(11, OUTPUT);
}

void loop() {
    if(BT.available() > 0){
    unsigned int x = BT.read();
    analogWrite(11,map(x,0,99,0,7));  
    }    
}
