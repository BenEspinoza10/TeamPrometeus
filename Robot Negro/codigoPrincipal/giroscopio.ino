//Funcion que inicializa el giroscopio, el objeto mpu debe estar creado de forma global
//Para inicializar mpu: MPU6050 mpu(Wire);  
void iniciarGiroscopio(){
  // Inicializar el MPU6050
  if (mpu.begin() != 0) {
    Serial.println(F("Error al inicializar el MPU6050"));
    while (1);
  }
  Serial.println(F("Calculando compensación MPU6050..."));
  //mpu.calcGyroOffsets();  // Calibrar giroscopio
  Serial.println("¡Listo!\n");
}

//Funcion que retorna el ángulo actual del mpu como int
int leerGiroscopio() {
  mpu.update();  //Obtención de valores de MPU
  int angulo = int(mpu.getAngleZ());
  return angulo;
}