#include "pines.h"
#include <QTRSensors.h>
#include <BluetoothSerial.h>
#include <Wire.h>
#include <MPU6050_light.h>
#include <Adafruit_VL53L0X.h>

//bluetoth
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#erros Bluetooth is not enabled !Pleas run make menuconfig to and enable it
#endif
BluetoothSerial SerialBT;

//Seguidor de lineas central
QTRSensors sigueLineas;                    // Objeto
const uint8_t numeroSensores = 8;          //Constante para almacenar el Nº de sensores
uint16_t valoresSensor[numeroSensores];    //Almacenar los valores de los sensores
uint16_t valoresUmbrales[numeroSensores];  //Almacenar los valores de los umbrales de cada sensor
int toleranciaUmbral = 200;                //Valor que se suma a los umbrales para asegurar la correcta lectura

//frecuencia y resolucion motores
const int frecuencia = 15000;
const int resolucion = 8;

//Constantes PID FUNCIONAL FINAL
float kp = 0.5;  // Desviación del robot al respecto de la linea
// Mayor desviación == mayor corrección
float ki = 0;      // Elimina el error ocupandoce de errores pasados
float kd = 56.58;  // Reduce osilaciones
/*ultimo funcional
  float kp = 0.5;
  float ki = 0;
  float kd = 45;
*/
//variables para PID
int integral = 0;
int derivada = 0;  // Predice el comportamiento de un error a futuro basándoce en errores pasados

//Velocidad
float limiteSuperior = 230;   //Limite positivo
float limiteInferior = -140;  // Limite negativo
int ref = 0;                  // Referencia
int tp = 35;                  // Velocidad

int I = 0;  //Contador de interesecciones


//Errores para la integral
int error6 = 0;
int error5 = 0;
int error4 = 0;
int error3 = 0;
int error = 0;
int lastError = 0;
int posicion = 0;


//Variables para el movimiento dentro del PID
int giro;
int veld;  // Velocidad derecha
int veli;  // Velocidad izquierda

//Flags de decición
int flagMarcador = false;       //Flag que indica si hay que leer el marcador de dirección false: se considera giro true: se considera marcador
int flagGiroIzquierda = false;  //Flag que indica si hay que girar a la izquierda en el siguiente cuadrado
int flagGiroDerecha = false;    //Flag que indica si hay que girar a la derecha en el siguiente cuadrado
int estado;                     // Variable que indica el estado en el que se está respecto a la pista: normal, intersección, gap, etc.


int interseccionDinamica = 10;  // Variable que indica el número de intersección donde se tiene que realizar el giro en base a la decisión
int interseccionDecision = 9;   // Variable que indica el número de intersección donde se tiene que realizar la lectura de decisión
int interseccionFin = 12;       // Variable que indica el número de intersección donde el robot debe deteneres
// Giroscopio
MPU6050 mpu(Wire);  // Crea un objeto mpu

// Láser
Adafruit_VL53L0X lox = Adafruit_VL53L0X();  //Crea un objeto láser

void setup() {
  Serial.begin(115200);
  SerialBT.begin("estoyChato");
  inicializarMotores();   //Configuración motores
  inicializarSensores();  //Configuración sensores

  //Esta parta de código es necesaria para iniciar i2c
  Wire.begin();
  Wire.setClock(100000);  // Configura la velocidad del I2C a 100kHz (puedes probar también 400kHz)
  iniciarLaser();         //configuracion laser
  pinMode(LED, OUTPUT);   //Led interna
  //calibracion
  //Se espera a que se apriete el botón para inicializar los sensores
  while (true) {
    if (digitalRead(BOTON) == 1) {
      calibrarSensores();
      Serial.println("listo");
      break;
    }
  }
  //Se espera a que se apriete el boton para iniciar el programa
  while (digitalRead(BOTON) == 0) {
  }
}

void loop() {
  estado = verificarCaso();
  SerialBT.print(leerLaser());
  if(leerLaser()<100){
    obst();
  }
  else{ 
    Motor(50,50);

  }
}
