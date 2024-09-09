void cuadrado() {
  Motor(0, 0);
  delay(100);
  Motor(50, 50);
  delay(200);
  if (I == 9) {// Me indica que despues viene la dirección de camino
    flag = false;
    Motor(0, 0);
    delay(2000);
    Motor(50, 50);
    delay(200);
  }
 else if (I == 11) {// Final stop
    Motor(0, 0);
    //    funcionLEDS();
  }
}
void girarIzquierda () {
  Motor(0, 0);
  delay(100);
  Motor (50, -50);
  delay (1000);
  Motor(50, 50);
  delay(250);
}
void girarDerecha () {
  Motor(0, 0);
  delay(100);
  Motor (-50, 50);
  delay (1000);
  Motor(50, 50);
  delay(250);
}
