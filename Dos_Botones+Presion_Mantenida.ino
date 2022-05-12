/*
 * Este programa implementa la lectura de dos botones (push bottons) distintos.
 * La ventaja aquí, es que se marca sólo una presión del botón hasta que se suelte, pues mientras
 * se mantenga presionado no registra ninguna acción adicional

 */

int seleccion = 8; int arriba = 10; int abajo = 9;
bool select; bool up; bool down; 
boolean swsel; boolean swar; boolean swab;
bool puchado = false; //Variable utilizada para roconocer si el botón ya fue presionado y soltado.
long n = 0; //variable para determinar el número de veces qu ele botón es presionado
bool prendido = false;

void setup() {
  Serial.begin(9600);
  while(!Serial) {}
  pinMode(seleccion, INPUT);
  pinMode(arriba, INPUT);
  pinMode(abajo, INPUT);
  Serial.println("a");
  

}

void loop() {
  swsel = digitalRead(seleccion);
  while(swsel == HIGH){
  swsel = digitalRead(seleccion); //Se vuelve a hacer la lectura del estado del botón, para notar cuando se deje de presionar
  prendido = true;//Se da la instrucción de que ya fue prendido el botón
}
//Una vez que se suelta el botón, se busca reconocer que mientras el botón este presionado no se avance en el contador que determina el númeor de veces de presionado.
if(prendido){ //Como ya fue prendido el botón, se busca reconocer que se quiere reconocer cuando se vuelva a presionar de nuevo
  puchado = true; //para indicar que el botón ya fue presionado una vez
 prendido = false; //se devuelve el valor del prendido para reconocer la siguiente vez que el botón se presione
}

if( puchado){
  Serial.println("Seleccion");
  puchado = false;
}

  /*
if( presionado(seleccion,swsel) == true ){
  Serial.println("Selección");
  puchado = false;
}

if( presionado(arriba, swar) == true ){
  Serial.println("Arriba");
  puchado = false;
}

if( presionado(abajo, swab) == true) {
  Serial.println("Abajo");
  puchado = false;
}

  */

}

boolean presionado(int swicht, boolean sw) {
 while(sw == HIGH){
  sw = digitalRead(swicht); //Se vuelve a hacer la lectura del estado del botón, para notar cuando se deje de presionar
  prendido = true;//Se da la instrucción de que ya fue prendido el botón
}
//Una vez que se suelta el botón, se busca reconocer que mientras el botón este presionado no se avance en el contador que determina el númeor de veces de presionado.
if(prendido){ //Como ya fue prendido el botón, se busca reconocer que se quiere reconocer cuando se vuelva a presionar de nuevo
  puchado = true; //para indicar que el botón ya fue presionado una vez
 prendido = false; //se devuelve el valor del prendido para reconocer la siguiente vez que el botón se presione
}
return true;
}
