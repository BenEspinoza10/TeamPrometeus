#include "pines.h"

void inicializarMotores() {

  //Se inicializan los pines de dirección del motor izquierdo
  pinMode(pinAI1, OUTPUT);
  pinMode(pinAI2, OUTPUT);

  //Se incializan los pines de dirección del motor derecho
  pinMode(pinBI1, OUTPUT);
  pinMode(pinBI2, OUTPUT);

  //Se inicializan los canales pwm
  ledcSetup(1,8000,8);
  ledcSetup(2,8000,8);

  //Se enlaca el canal 1 con el pin de velocidad del motor izquierdo
  ledcAttachPin(pinPWMA, 1);

  //Se enlaca el canal 2 con el pin de velocidad del motor derecgo
  ledcAttachPin(pinPWMB, 2);
}
void Motoriz(int value) {

  //Se define la dirección en base al signo del valor
  if (value >= 0) {
    digitalWrite(pinAI1, HIGH);
    digitalWrite(pinAI2, LOW);
  } else {
    digitalWrite(pinAI1, LOW);
    digitalWrite(pinAI2, HIGH);
    value *= -1;
  }

  //Se asigna la velocidad pwm
  ledcWrite(1, value);
}

//accionamiento motor derecho
void Motorde(int value) {
  //Se define la dirección en base al signo del valor
  if (value >= 0) {
    digitalWrite(pinBI1, LOW);
    digitalWrite(pinBI2, HIGH);
  } else {
    digitalWrite(pinBI1, HIGH);
    digitalWrite(pinBI2, LOW);
    value *= -1;
  }
  //Se asigna la velocidad pwm
  ledcWrite(2, value);
}


//Accionamiento de motores
void Motor(int left, int right) {
  Motoriz(left);
  Motorde(right);
}
