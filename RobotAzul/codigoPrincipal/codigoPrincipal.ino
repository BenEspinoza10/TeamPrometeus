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
float kp;  // Desviación del robot al respecto de la linea
// Mayor desviación == mayor corrección
float ki;  // Elimina el error ocupandoce de errores pasados
float kd;  // Reduce osilaciones
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
int flagGiroDerecha = false;
//Flag que indica si hay que leer el marcador de dirección false: se considera giro true: se considera marcador

int flagMarcador2 = false;
int flagGiroIzquierda2 = false;  //Flag que indica si hay que girar a la izquierda en el siguiente cuadrado
int flagGiroDerecha2 = false;    //Flag que indica si hay que girar a la derecha en el siguiente cuadrado
int estado;                      // Variable que indica el estado en el que se está respecto a la pista: normal, intersección, gap, etc.
bool pasitoD = false;
bool pasitoI = false;


int interseccionDinamica = 6;
int interseccionDinamica2 = 7;  // Variable que indica el número de intersección donde se tiene que realizar el giro en base a la decisión
int interseccionDecision = 5;   // Variable que indica el número de intersección donde se tiene que realizar la lectura de decisión
int interseccionFin = 8;        // Variable que indica el número de intersección donde el robot debe deteneres
// Giroscopio
MPU6050 mpu(Wire);  // Crea un objeto mpu
int XInicial;
int cambiosX = 0;
int anguloX;
// Láser
Adafruit_VL53L0X lox = Adafruit_VL53L0X();  //Crea un objeto láser

void setup() {
  Serial.begin(115200);
  SerialBT.begin("Prometeus");
  inicializarMotores();   //Configuración motores
  inicializarSensores();  //Configuración sensores


  //Esta parta de código es necesaria para iniciar i2c
  Wire.begin();
  Wire.setClock(100000);  // Configura la velocidad del I2C a 100kHz (puedes probar también 400kHz)

  iniciarGiroscopio();

  pinMode(LED, OUTPUT);  //Led interna
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
  if (estado == 0) {  //Valor por defecto
    pid();
  } else if (estado == 1) {  // Todo negro
    I++;
    SerialBT.print("Contador es: ");
    SerialBT.println(I);
    //Que sume las interseccciones que lleva
    cuadrado();
  } else if (estado == 2 && pasitoI == false && pasitoD == false) {  //Todo blanco
    Motor(18, 18);

  } else if (estado == 2 && flagMarcador == false && pasitoI == true && flagMarcador2 == false) {
    girarIzquierdaGiroscopio();
    pasitoI = false;

  }
  /////// repetir el código para la segunda marca, para el segundo robot
  else if (estado == 2 && flagMarcador == false && pasitoD == true && flagMarcador2 == false) {
    girarDerechaGiroscopio();
    pasitoD = false;
  }

  else if (estado == 2 && flagMarcador == false && pasitoD == true && flagMarcador2 == false) {
    girarDerechaGiroscopio();
    pasitoD = false;
  }

  else if (estado == 3 && flagMarcador == false && pasitoI == false && flagMarcador2 == false) {
    Motor(50, 50);
    delay(180);
    pasitoI = true;
    Motor(0, 0);
    delay(800);
  }

  else if (estado == 3 && flagMarcador == true && flagMarcador2 == false) {  //Marcador izquierda
    flagGiroIzquierda = true;
    flagMarcador = false;
    Motor(50, 50);
    delay(180);

  } else if (estado == 3 && flagMarcador == false && flagMarcador2 == true) {  //Marcador izquierda
    flagGiroIzquierda2 = true;
    flagMarcador2 = false;
    Motor(50, 50);
    delay(180);

  }

  else if (estado == 4 && flagMarcador == false && pasitoD == false) {
    Motor(50, 50);
    delay(180);
    pasitoD = true;
    Motor(0, 0);
    delay(800);
  }

  else if (estado == 4 && flagMarcador == false && flagMarcador2 == true) {  //Marcador derecha
    flagGiroDerecha2 = true;
    flagMarcador2 = false;
    Motor(50, 50);
    delay(500);

  }

  else if (estado == 4 && flagMarcador == false && pasitoD == false && flagMarcador2 == false) {
    Motor(50, 50);
    delay(150);
    pasitoD = true;
    Motor(0, 0);
    delay(500);


  } else if (estado == 4 && flagMarcador2 == false && flagMarcador == true) {  //Marcador derecha
    flagGiroDerecha = true;
    flagMarcador = false;
    Motor(50, 50);
    delay(500);
  }
  SerialBT.println(I);
  SerialBT.println(estado);
}
