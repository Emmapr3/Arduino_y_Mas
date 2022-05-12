/* Tarea 2: Destellos de LED en base al número de presiones
 
 * Este programa tiene como objetivo hacer que al apretar un botón/interruptor, un el un LED ( Arduino o externo) encienda una vez cada segundo,
 * y conforme el número de veces que se presione el botón, el LED encienda dicho número en un segundo.
 * 
 * Por :
 Jazmin G. Garduño Hernández
 José Emmanuel Paredes Rocha
  */

//Primero declaramos las variables que vamos a utilizar.
boolean sw;//La variable sw será utilizada para la lectura del botón.
bool presionado = false; //Variable utilizada para roconocer si el botón ya fue presionado y soltado.
long n = 0; //variable para determinar el número de veces qu ele botón es presionado
bool prendido = false; //variable utilizada para reconocer el encendido del LED.
float k = 0;

void setup() {
  
  pinMode(12,INPUT);  //pin del Botón. El botón está en el (Pin 12)
  pinMode(11,OUTPUT); //pin del LED. El LED está en el (Pin 11)
   Serial.begin(9600); //para iniciar el monitor Serial
   while(!Serial);    //para esperar hasta que inicie el monitor

}

void loop() {
sw = digitalRead(12); //Lee si el botón está presionado o no. 

//Mientras el botón esté presionado, vuelve a leer, y sale del loop hasta que se deje de presionar
while(sw == HIGH){
  digitalWrite(11,sw); //Se enciende el LED mientras el botón esté presionado
  sw = digitalRead(12); //Se vuelve a hacer la lectura del estado del botón, para notar cuando se deje de presionar
  prendido = true;//Se da la instrucción de que ya fue prendido el botón
}
//Una vez que se suelta el botón, se busca reconocer que mientras el botón este presionado no se avance en el contador que determina el númeor de veces de presionado.
if(prendido){ //Como ya fue prendido el botón, se busca reconocer que se quiere reconocer cuando se vuelva a presionar de nuevo
  presionado = true; //para indicar que el botón ya fue presionado una vez
 prendido = false; //se devuelve el valor del prendido para reconocer la siguiente vez que el botón se presione
}
//
if(presionado){ //Para contabilizar cuando el botón ya fue presionado
  n++; //agrega uno al número de presiones del botón
  presionado = false; //se cambia el valor para reconocer cuando sea presionado nuevamente el botón
  k = 1000/(2*n);
  }
else{ //mientras no se vuelva a presionar, que haga el número de destellos en un segundo
  //Lo siguiente hace que el LED se encienda y se apague 'n' veces en un segundo
 //lo que hace es dividir el segundo en '2*n' para dar tiempos iguales a que esté encendido y apagado.
  digitalWrite(11, HIGH); //para encender el LED
  delay(k); //se espere un tiempo encendido
  digitalWrite(11, LOW); //el LED se apaga
  delay(k); //se espera un tiempo apagado, para volver a encender
  }
}
 

