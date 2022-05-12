int pinBS = A0; //Pin Bottons
bool state= false; //Estado del botón
bool presion = false; //siel botón fue presionado o no
int lec; //valor que lee el puerto analógico

void setup() {
  pinMode(pinBS, INPUT);
  Serial.begin(9600);
  while(!Serial);
}

void loop() {
  int lec = analogRead(pinBS);

 /* if( lec == 0){
    state = false;
  }else state = true;

  while(state == true){
    lec = analogRead(pinBS);
     if( lec == 0){
      state = false;
      }else state = true;
  }*/
  
  Serial.println( MBotton(lec) );
  delay(500);

}

int MBotton(int var){
  int lim1 = 250;
  int lim2 = 400;
  int lim3 = 800;

  if( var == 0)
  return 0;
  
  if(0 < var && var < lim1)
  return 1;

  if( lim1 < var && var < lim2 )
  return 2;

  if( lim2 <  var && var < lim3)
  return 3;

  if( lim3 < var && var < 1023)
  return 4;
}

//la función esperar() identifica que el botón 'pin' haya sido presionado y soltado para poder contar el puchado de ducho botón y cambiar el estado 'var' del botón
void esperar(int lec, boolean var, int pin){
  while(var == HIGH){ //mientras se mantenga presionado el botón, sigue leyendo el estado del botón y no sale del bucle 'while' hasta que se suelte el botón
    var = digitalRead(pin);
  }
}

