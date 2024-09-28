int verificarCaso () {
  int x;
  sigueLineas.read(valoresSensor);
 //Que esta leyendo
  if (valoresSensor[0] >= valoresUmbrales[0] and valoresSensor[1] >= valoresUmbrales[1] and valoresSensor[2] >= valoresUmbrales[2] and valoresSensor[3] >= valoresUmbrales[3] and valoresSensor[4] >= valoresUmbrales[4] and valoresSensor[5] >= valoresUmbrales[5] and valoresSensor[6] >= valoresUmbrales[6] and valoresSensor[7] >= valoresUmbrales[7]) {
    x = 1;//negro interseccion
  } else if (valoresSensor[0] < valoresUmbrales[0] and valoresSensor[1] < valoresUmbrales[1] and valoresSensor[2] < valoresUmbrales[2] and valoresSensor[3] < valoresUmbrales[3] and valoresSensor[4] < valoresUmbrales[4] and valoresSensor[5] < valoresUmbrales[5] and valoresSensor[6] < valoresUmbrales[6] and valoresSensor[7] < valoresUmbrales[7]) {
    x = 2;//blanco gap
  } else if (valoresSensor[0] < valoresUmbrales[0] and valoresSensor[1]< valoresUmbrales[1] and valoresSensor[2] < valoresUmbrales[2]  and valoresSensor[3] > valoresUmbrales[3] and valoresSensor[4] > valoresUmbrales[4] and valoresSensor[5] > valoresUmbrales[5] and valoresSensor[6] > valoresUmbrales[6] and valoresSensor[7] > valoresUmbrales[7]) {
    x = 3; //detecta izquierda
  } else if (valoresSensor[0] > valoresUmbrales[0] and valoresSensor[1] > valoresUmbrales[1] and valoresSensor[2] > valoresUmbrales[2] and valoresSensor[3] > valoresUmbrales[3] and valoresSensor[4] > valoresUmbrales[4] and valoresSensor[5] < valoresUmbrales[5] and valoresSensor[6] < valoresUmbrales[6] and valoresSensor[7] < valoresUmbrales[7]) {
    x = 4; //detecta derecha 
  } 

  else {
    x = 0;
  }
  return x;
}

