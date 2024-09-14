void pid() {
  posicion = sigueLineas.readLineBlack(sensorValues);
  posicion = map(posicion, 0, 7000, -255, 255);

  error = posicion - ref;
  integral = integral + lastError + error3 + error4 + error5 + error6;
  derivada = error - lastError;
  giro = (kp * integral) + (kd * derivada);
  veli = tp + giro;
  veld = tp - giro;
  if (veli > limipo) {
    veli = limipo;
  }
  if (veld > limipo) {
    veld = limipo;
  }
  if (veli < limine) {
    veli = limine;
  }
  if (veld < limine) {
    veld < limine;
  }
  Motor(veld, veli);
  error6 = error5;
  error5 = error4;
  error4 = error3;
  error3 = lastError;
  lastError = error;
}
