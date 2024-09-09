void setup() {
  //Se inicializan los motores
  inicializarMotores();
}

void loop() {
  //Para debugear esto es el siguiente orden:
  //Primero poner código de 50,50 para verificar que la dirección de las ruedas esté correcta
  //Luego poner 0,50 para verificar que la rueda derecha efectivamente sea la derecha
  Motor(50,50);

}
