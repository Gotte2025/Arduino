//LUZ
int estadoluz = 0; // estado LUZ
int const luz=13; //Led pin 13

void iluminacion(){
   if (estadoluz == 0)
  {
    digitalWrite(luz,1);
  }
  if ( estadoluz == 1)
  {
    digitalWrite(luz,0);;
  }
  estadoluz = !estadoluz;

  delay(2);
}
