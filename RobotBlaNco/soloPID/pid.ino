void pid() {
  //Se lee la posicion actual
  posicion = sigueLineas.readLineBlack(valoresSensor);

  //Se cambia de escala la posicion de [0,7000] a [-255,255]
  posicion = map(posicion, 0, 7000, -255, 255);
  if (posicion > 200 && posicion < -200) {
    kp = 1;
    ki = 0;
    kd = 50;
  } else if (posicion < 20 && posicion > -20) {
    kp = 0;
    ki = 0;
    kd = 0;
  } else {
    kp = 0.8;
    ki = 0;
    kd = 90;
  }
  //Se calcula el error
  error = posicion - ref;

  //Se calcular la integral y derivada
  integral = integral + lastError + error3 + error4 + error5 + error6;
  derivada = error - lastError;

  //Se calcula el giro y las velocidades de cada rueda
  giro = (kp * error ) + ( ki * integral) + ( kd * derivada);
  veli = tp + giro;
  veld = tp - giro;

  //Se limita por arriba la velocidad de los motores
  if (veli > limiteSuperior) {
    veli = limiteSuperior;
  }
  if ( veld > limiteSuperior) {
    veld = limiteSuperior;
  }

  //Se limita por abajo la velocidad de los motores
  if (veli < limiteInferior) {
    veli = limiteInferior;
  }
  if ( veld < limiteInferior) {
    veld = limiteInferior;
  }

  //Se ejecuta el movimiento del robot
  Motor(veli, veld);

  //Se imprimen las velocidades izquierda y derecha junto a la posicion
  /*Serial.print("izq: ");
    Serial.print(veli);
    Serial.print(" der: ");
    Serial.print(veld);
    Serial.print(" pos: ");
    Serial.println(error);*/


  //Se actualizan los errores para la integral
  error6 = error5;
  error5 = error4;
  error4 = error3;
  error3 = lastError;
  lastError = error;
}
