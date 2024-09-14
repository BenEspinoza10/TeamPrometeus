#include "pines.h"
#include <QTRSensors.h>
#include <BluetoothSerial.h>
#include <Wire.h>
//bluetoth
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#erros Bluetooth is not enabled !Pleas run make menuconfig to and enable it
#endif
BluetoothSerial SerialBT;

//Seguidor de lineas central
QTRSensors sigueLineas; // Objeto
const uint8_t CEN = 8; //Constante para almacenar el Nº de sensores
uint16_t sensorValues[CEN]; //Almacenar los valores de los sensores

//frecuencia y resolucion motores
const int frecuencia = 15000;
const int resolucion = 8;

//Constantes PID FUNCIONAL FINAL
float kp = 0.5; // Desviación del robot al respecto de la linea
// Mayor desviación == mayor corrección
float ki = 0; // Elimina el error ocupandoce de errores pasados
float kd = 56.58; // Reduce osilaciones
/*ultimo funcional
  float kp = 0.5;
  float ki = 0;
  float kd = 45;
*/
//variables para PID
int integral = 0;
int derivada = 0;// Predice el comportamiento de un error a futuro basándoce en errores pasados

//Velocidad
float limipo = 230; //Limite positivo
float limine = -140; // Limite negativo
int ref = 0; // Referencia
int tp = 35; // Velocidad

int I = 0; //Contador de interesecciones
int umbral = 4000;

int error6 = 0; int error5 = 0; int error4 = 0; int error3 = 0; int error = 0; int lastError = 0; int posicion = 0;

int giro;
int veld; // Velocidad derecha
int veli; // Velocidad izquierda

//Flags de decición
int flag = true; //Marcador de dirección
int flagGiroIzquierda = true; //Toque izquierda?
int flagGiroDerecha = true;//Toque derecha?
int estado;// Que esta leyendo

void setup() {
  Serial.begin(9600);
  SerialBT.begin("NYXR");
  setMotor();     //Configuración motores
  setSensores();  //Configuración sensores
  Wire.begin();

  pinMode(2, OUTPUT);  //Led interna
  while (true) {       //Calibración
    if (digitalRead(BOTON) == 1) {
      calibra();
      SerialBT.print("Nyx");
      break;
    }
  }
  while (digitalRead(BOTON) == 0) {
  }
}

void loop() {
  estado = verificarCaso();

  if (estado == 0) {
    pid();
  }
  else if (estado == 1) {
    / Ttodo negro
    I++;
    //Que sume las interseccciones que lleva
    cuadrado();
    if (I == 10 && flagGiroIzquierda == false) { //Dirección de camino izquierda
      girarIzquierda();
    }
    else if (I == 6 && flagGiroDerecha == false) { //Dirección de camino derecha
      girarDerecha();
    }
  } else if (estado == 2) {//Todo blanco
    Motor(18, 18);
  }
  else if (estado == 4 && flag == false) {//Marcador derecha
    flagGiroDerecha = false;
    flag = true;
  }
  else if (estado == 3 && flag == false) {//Marcador izquierda
    flagGiroIzquierda = false;
    flag = true;
  }
  else if (estado == 3) {
    girarIzquierda();
  }
  else if (estado == 4) {
    girarDerecha();
  }
}
