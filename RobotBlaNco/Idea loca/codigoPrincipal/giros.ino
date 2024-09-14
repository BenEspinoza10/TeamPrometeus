
//giro hacia la izquierda sobre el eje en 90 grados
void girarIzquierda() {
  Motor(0, 0);
  delay(100);
  Motor(50, -50);
  delay(1000);
  Motor(50, 50);
  delay(250);
}

//giro hacia la derecha sobre el eje en 90 grados
void girarDerecha() {
  Motor(0, 0);
  delay(100);
  Motor(-50, 50);
  delay(1000);
  Motor(50, 50);
  delay(250);
}

//Giro en 90 grados hacia la derecha con giroscopio
void girarDerechaGiroscopio() {
  //Primero frenar
  Motor(0, 0);
  delay(250);
  mpu.calcGyroOffsets();  // Calibrar giroscopio
  int angulo = leerGiroscopio();
  int anguloInicial = angulo;
  while (angulo >= (anguloInicial - 90)) {
    Motor(50, -50);
    angulo = leerGiroscopio();
  }
  //Primero frenar
  Motor(0, 0);
  delay(250);
  //avanzar para asegurarse de salir del giro
  Motor(50, 50);
  delay(500);
}

//Giro en 90 grados hacia la izquierda con giroscopio
void girarIzquierdaGiroscopio() {
  //Primero frenar
  Motor(0, 0);
  delay(250);
  mpu.calcGyroOffsets();  // Calibrar giroscopio
  int angulo = leerGiroscopio();
  int anguloInicial = angulo;
  while (angulo <= (90 + anguloInicial)) {
    Motor(-50, 50);
    angulo = leerGiroscopio();
  }
  //Primero frenar
  Motor(0, 0);
  delay(250);
  //avanzar para asegurarse de salir del giro
  Motor(50, 50);
  delay(500);
}
