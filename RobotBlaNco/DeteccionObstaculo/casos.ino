int verificarCaso() {
  int x;
  sigueLineas.read(valoresSensor);

      x = 0;


  return x;
}
void obst(){

girarIzquierda();
Motor(0,0);
Motor(50,50);
delay(1200);
girarDerecha();
Motor(0,0);
Motor(50,50);
delay(3000);
girarDerecha();
Motor(0,0);
Motor(50,50);
delay(1200);
girarIzquierda();

}