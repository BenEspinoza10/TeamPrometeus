#include <Wire.h>
#include <MPU6050_light.h>

// Giroscopio
MPU6050 mpu(Wire);  // Crea un objeto mpu

void setup() {
  //Esta parta de código es necesaria para iniciar i2c
  Wire.begin();
  Wire.setClock(100000);  // Configura la velocidad del I2C a 100kHz (puedes probar también 400kHz)

  //Se inicia la comunicación serial
  Serial.begin(115200);  

  //Se inicia el giroscopio
  iniciarGiroscopio();  
}

void loop() {
  int angulo = leerGiroscopio();
  Serial.println(angulo);  
  delay(200);
}
