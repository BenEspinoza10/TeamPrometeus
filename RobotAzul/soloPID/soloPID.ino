#include "pines.h"
#include <QTRSensors.h>
#include <BluetoothSerial.h>
#include <Wire.h>

//bluetoth
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#erros Bluetooth is not enabled !Pleas run make menuconfig to and enable it
#endif
BluetoothSerial SerialBT;

//seguidor de lineas central
QTRSensors sigueLineas;                    // Objeto
const uint8_t numeroSensores = 8;          //Constante para almacenar el Nº de sensores
uint16_t valoresSensor[numeroSensores];    //Almacenar los valores de los sensores
uint16_t valoresUmbrales[numeroSensores];  //Almacenar los valores de los umbrales de cada sensor
int toleranciaUmbral = 400;                //Valor que se suma a los umbrales para asegurar la correcta lectura

//frecuencia y resolucion motores
const int frecuencia = 15000;
const int resolucion = 8;

//constantes PID
float kp;
float ki;
float kd;

/*
//ULTIMOS VALORES BUENOS NEGRO
float kp = 0.392;
float ki = 0.0003;
float kd = 30.2;
*/
//variables para PID
int integral = 0;
int derivada = 0;

//Velocidad
float limiteSuperior = 230;
float limiteInferior = -140;
int ref = 0;
//Velocidad Base
int tp = 40;

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
int veld;
int veli;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("Prometeus");
  inicializarMotores();   //configuracion motores
  inicializarSensores();  //configuracion sensores

  pinMode(LED, OUTPUT);  //led interna

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
  pid();
}
