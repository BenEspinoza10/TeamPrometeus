void cuadrado() {
  //Se asegura que salga de la intersección para evitar marcar extra
  Motor(0, 0);
  delay(100);
  Motor(50, 50);
  delay(200);

  if (I == 5) {  // Me indica que despues viene la dirección de camino
    flagMarcador = true;
    decision();
    flagMarcador = true;
    decision();
    SerialBT.print("Contador_Flag: ");
    SerialBT.println(GiroIzquierda);

  } else if ((I == 6) || (I == 7) && (GiroIzquierda == 1) || (GiroIzquierda == 2)) {  //Dirección de camino izquierda
    girarIzquierda();
    GiroIzquierda = GiroIzquierda - 1;
  } else if ((I == 6) || (I == 7) && (GiroDerecha == 1) || (GiroDerecha == 2)) {  //Dirección de camino derecha
    girarDerecha();
    GiroDerecha = GiroDerecha - 1;
  } else if (I == interseccionFin) {  // Final stop
    Motor(0, 0);
    // funcionLEDS();
  }
}

void decision() {
  while (flagMarcador == true) {
    Motor(20, 20);
    int caso = verificarCaso();
    if (caso == 3) {
      GiroIzquierda++;
      flagMarcador = false;
      while (caso == 3) {
        Motor(20, 20);
        caso = verificarCaso();
      }
    } else if (caso == 4) {
      GiroDerecha++;
      flagMarcador = false;
      while (caso == 4) {
        Motor(20, 20);
        caso = verificarCaso();
      }
    }
  }
}

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
