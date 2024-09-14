#include <Wire.h>
#include <MPU6050_light.h>
#include <Adafruit_VL53L0X.h>

// Giroscopio
MPU6050 mpu(Wire);  // Crea un objeto mpu


// Láser
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void setup() {
  //Esta parta de código es necesaria para iniciar i2c
  Wire.begin();
  Wire.setClock(100000);  // Configura la velocidad del I2C a 100kHz (puedes probar también 400kHz)

  //Se inicia la comunicación serial
  Serial.begin(115200);  

  //Se inician los sensores
  iniciarGiroscopio();
  iniciarLaser();
}

void loop() {
  int angulo = leerGiroscopio();
  Serial.print(angulo);
  Serial.print('\t');
  int distancia = leerLaser();
  Serial.println(distancia);
  delay(200);
}
