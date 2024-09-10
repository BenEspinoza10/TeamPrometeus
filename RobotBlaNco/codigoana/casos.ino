int verificarCaso () {
  int x;
  sigueLineas.read(sensorValues);
 //Que esta leyendo
  if (sensorValues[0] >= umbral and sensorValues[1] >= umbral and sensorValues[2] >= umbral and sensorValues[3] >= umbral and sensorValues[4] >= umbral and sensorValues[5] >= umbral and sensorValues[6] >= umbral and sensorValues[7] >= umbral) {
    x = 1;//negro
  } else if (sensorValues[0] < umbral and sensorValues[1] < umbral and sensorValues[2] < umbral and sensorValues[3] < umbral and sensorValues[4] < umbral and sensorValues[5] < umbral and sensorValues[6] < umbral and sensorValues[7] < umbral) {
    x = 2;//blanco
  } else if (sensorValues[0] < umbral and sensorValues[1]< umbral and sensorValues[2] < umbral  and sensorValues[3] > umbral and sensorValues[4] > umbral and sensorValues[5] > umbral and sensorValues[6] > umbral and sensorValues[7] > umbral) {
    x = 3; //detecta izquierda
  } else if (sensorValues[0] > umbral and sensorValues[1] > umbral and sensorValues[2] > umbral and sensorValues[3] > umbral and sensorValues[4] > umbral and sensorValues[5] < umbral and sensorValues[6] < umbral and sensorValues[7] < umbral) {
    x = 4; //detecta derecha 
  } else {
    x = 0;
  }
  return x;
}
