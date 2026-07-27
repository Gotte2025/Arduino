int command; //Int to store app command state.
void ControlBT () {
  if (Serial.available() > 0)
  {
    command = Serial.read();

    switch (command) {
      case 'F': forward();  break;
      case 'B': backward();  break;
      case 'S': Stop();  break;
      case '0': Desvio1() ;  break;
      case '1': Desvio2(); break;
      case '2': Desvio3(); break;
      case '3': Desvio4(); break;
      case '4': Desvio5(); break;
      case '5': Desvio6(); break;
      case '6': acelerar = 70; break;
      case '7': acelerar = 180; break;
      case '8': acelerar = 250; break;
      case '9': iluminacion(); break;


        delay(2);
    }
  }
}
