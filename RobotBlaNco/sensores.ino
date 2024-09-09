void setSensores() {//Definir los sensores en su variable
  calibra();
  sigueLineas.setTypeAnalog();
  sigueLineas.setSensorPins((const uint8_t[]) {
    26, 25, 33, 32, 35, 34, 39, 36
  },
  CEN);
  sigueLineas.setEmitterPin(27);
}
void calibra() {//Calibración de todos los sensores
  for (int i = 0; i < 150; i++) {

    digitalWrite(2, HIGH);
    delay(10);
    sigueLineas.calibrate();
    digitalWrite(2, LOW);
    delay(10);
  }
 /* for (uint8_t i = 0; i < HNE; i++)
  {
    Serial.print(qtr.calibrationOn.minimum[i]);
    Serial.print(' ');
  }
  Serial.println();

  // print the calibration maximum values measured when emitters were on
  for (uint8_t i = 0; i < HNE; i++)
  {
    Serial.print(qtr.calibrationOn.maximum[i]);
    Serial.print(' ');
  }*/
}
