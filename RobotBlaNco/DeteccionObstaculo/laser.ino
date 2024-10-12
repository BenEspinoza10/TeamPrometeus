//Funcion que inicializa el láser, el objeto láser debe estar creado de forma global
//Para inicializar láser: Adafruit_VL53L0X lox = Adafruit_VL53L0X();
void iniciarLaser() {
  if (!lox.begin()) {
    Serial.println(F("Error al inicializar el VL53L0X"));
    while (1);
  }
}

//Funcion que retorna la distancia detectada por el sensor de distancia láser
//En caso de que la lectura sea inválida, retorna un -1
int leerLaser() {
  VL53L0X_RangingMeasurementData_t measure;

  lox.rangingTest(&measure, false);

  if (measure.RangeStatus != 4) {
    return measure.RangeMilliMeter;
  } else {
    return -1;
  }
}


