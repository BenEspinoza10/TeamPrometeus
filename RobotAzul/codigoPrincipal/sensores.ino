#include "pines.h"

//Funcion para inicializar el sensor Infrarrojo, el objeto debe estar creado de forma global
//Para crear el objeto se debe usar: QTRSensors sigueLineas;
void inicializarSensores() {
  sigueLineas.setTypeAnalog();
  sigueLineas.setSensorPins((const uint8_t[]) {
    26,25, 33, 32, 35, 34, 39,36
  },
  numeroSensores);
  sigueLineas.setEmitterPin(27);
}


//Funcion que calibra los sensores
void calibrarSensores() {
  //El límite del for define la duración de la calibración
  for (int i = 0; i < 150; i++) {
    digitalWrite(LED, HIGH);
    delay(10);
    sigueLineas.calibrate();
    digitalWrite(LED, LOW);
    delay(10);
  }
  //Calculo de umbrales por sensor en base a los máximos y minimos leídos en la calibración
  for (int i=0;i<numeroSensores;i++){
    valoresUmbrales[i] = ((sigueLineas.calibrationOn.minimum[i]+sigueLineas.calibrationOn.maximum[i])/2) + toleranciaUmbral;
  }

}

