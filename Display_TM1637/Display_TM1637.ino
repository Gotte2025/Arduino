
int tempc;
int vout; 
#define sensor A0   
#include "Display.h" 


void setup()
{
}

void loop()
{
display.setBrightness(0x0ff);
vout = analogRead(sensor);
tempc =(vout*500)/1024;

pantalla ();

}
