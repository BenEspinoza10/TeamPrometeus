#include <Wire.h>
#include <Adafruit_VL53L0X.h>


// Láser
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void setup() {
  //Esta parta de código es necesaria para iniciar i2c
  Wire.begin();
  Wire.setClock(100000);  // Configura la velocidad del I2C a 100kHz (puedes probar también 400kHz)

  //Se inicia la comunicación serial
  Serial.begin(115200);  

  //Se inicia el laser
  iniciarLaser();
}

void loop() {  
  int distancia = leerLaser();
  Serial.println(distancia);
  delay(200);
}
