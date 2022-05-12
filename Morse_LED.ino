//Clave Morse con Arduino
//Por Jazmín G. Garduño Hernández y J. Emmanuel Paredes Rocha
//Laboratioro de Electrónica

//se define la función punto, que es una señal de 200ms y un tiempo de espera de 200ms 
void p() {         
  digitalWrite(LED_BUILTIN,HIGH);  //prende el LED
    delay(200);              //tiempo de encendido de cada pulso
    digitalWrite(LED_BUILTIN,LOW);   //apaga el LED
    delay(200);              //tiempo de espera entre pulsos
}

//se define la función linea, que es una señal de 600ms y un tiempo de espera de 200ms
void l() {        //señal raya
  digitalWrite(LED_BUILTIN,HIGH);  //prende el LED
    delay(600);              //tiempo de encendido de cada pulso
    digitalWrite(LED_BUILTIN,LOW);   //apaga el LED
    delay(200);   
}

//se definen las letras, según el código Morse

void E() {    //la letra E es sólo punto
   p();
  delay(200);
}

void G() {    //la letra G son dos líneas y un punto
  l();
  l();
  p();
  delay(200);
}

void H() {    //la letra H son cuatro puntos
  for(int i=1;i<=4;i++){
    p();
  }
  delay(200);
}

void J() {    //la letra J es un punto seguido de tres líneas
    p();
    l();
    l();
    l();
  delay(200);
}

void P() {    //la letra P es un punto, seguido de dos líneas y terminando con un punto
  p();
  l();
  l();
  p();
  delay(200);
}

void R() {    //la letra R es un punto, seguido de una línea y finalizando con un punto
  p();
  l();
  p();
  delay(200);
}



void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

}

void loop() {
  J();    //iniciales de Jazmín
  G();
  G();
  H();
  delay(600);

  J();    //iniciales de Emmanuel
  E();
  P();
  R();
  delay(600);

}
