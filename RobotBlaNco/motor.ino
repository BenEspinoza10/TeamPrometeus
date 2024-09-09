void setMotor() {// Seteo de pines motores
  pinMode(pinAI1, OUTPUT);
  pinMode(pinAI2, OUTPUT);
  pinMode(pinBI1, OUTPUT);
  pinMode(pinBI2, OUTPUT);
  ledcSetup(1, 8000, 8);
  ledcSetup(2, 8000, 8);
  ledcAttachPin(pinPWMA, 1);
  ledcAttachPin(pinPWMB, 2);
}
void Motoriz(int value) {// Motor izquierdo
  if (value >= 0) {
    digitalWrite(pinAI1, HIGH);
    digitalWrite(pinAI2, LOW);
  } else {
    digitalWrite(pinAI1, LOW);
    digitalWrite(pinAI2, HIGH);
    value *= -1;
  }
  ledcWrite(1, value);
}

void Motorde(int value) {//Motor derecho
  if (value >= 0) {
    digitalWrite(pinBI1, LOW);
    digitalWrite(pinBI2, HIGH);
  } else {
    digitalWrite(pinBI1, HIGH);
    digitalWrite(pinBI2, LOW);
    value *= -1;
  }
  ledcWrite(2, value);
}


//Accionamiento de motores
void Motor(int left, int right) {
  Motoriz(left);
  Motorde(right);
}
