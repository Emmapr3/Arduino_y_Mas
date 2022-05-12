/*Paredes Roche José Emmanuel
 * Garduño hernández Jazmin G.
 * 
 * Control PID de temperatura
 * El siguiente programa implementa el uso de un algoritmo PID en el control de la temperatura. 
 * El usuario elige el setpoint que requiere su sistema, que en éste caso corresponde a la temperatura a la que se desea llegar; se ingresa el dato 
 * a través del monitor serial con el siguiente formato: Sp (valor), donde en el apartado (valor) coloca la temperatura esperada.
 * A partir del algoritmo PID se obtiene la salida para alimentar un ventilador de 12V y una resistencia de 1 Ohm y 10W (se hace un proceso PID distinto para cada uno), de forma que ambos componentes 
 * contribuyen a llegar a la temperatura que se introdujo como Sp. 
 * Para medir la temperatura en todo momento, se usó de un sensor LM35. 
 * 
 */

#include <PID_v1.h>//Librería utilizada para la implemetación del PID.
//#include <AutoPID.h>

double input, outputv,outputr, setpoint = 25   ;//Variables utilizadas en el PID, la variable outputv corresponde a la salida del ventilador y la variable outputr a la de las resistencias 

double kp=40,ki=0.00005,kd=0.7;//Constantes del PID obtenidas por el método de lazo abierto
unsigned long serialTime;//Para impresión en el serial

PID myPIDv(&input, &outputv, &setpoint,kp,ki,kd, DIRECT);//Función inicial del PID para el ventilador.
PID myPIDr(&input, &outputr, &setpoint,kp,ki,kd, DIRECT);//Función inicial del PID para las resistencias.

String inputString = "";         // Variable de cadena para ingresar valores del serial.
boolean stringComplete = false;  // Variable para reconocer si la cadena ingresada está completa o no. 
String valorsp= "";//Variable asignada para reconocer el valor de setup que se espera.

//Variables para la lectura de la temperatura con el sensor LM35.
int lecad; //Variable para leer el estado analógico.
float voltaje; //varibale para obtener la lectura de voltaje voltaje.
float Temperatura; //Variable de la temperatura



void setup()
{
  
  myPIDv.SetMode(AUTOMATIC);//Inicialización del PID del ventilador.
  myPIDr.SetMode(AUTOMATIC);//Inicialización del PID de las resistencias.
  serialTime = 0;
  Serial.begin(9600);//Inicialización del monitor serial.
myPIDv.SetOutputLimits(0, 255);//Se asignan los límites para el valor del outputv que se puede obtener.
myPIDv.SetControllerDirection(REVERSE);//Se  asigna la dirección del proceso PID para el ventilador. 
myPIDr.SetOutputLimits(0, 255);//Se asignan los límites para el valor del outputr que se puede obtener.
myPIDr.SetControllerDirection(DIRECT);//Se  asigna la dirección del proceso PID para las resistencias.
pinMode(9,OUTPUT);//Asignación del pin 9 como salida. 
pinMode(6,OUTPUT);//Asignación del pin 6 como salida.
}

void loop(){

if(stringComplete){ //Al recibir información por el monitor serial, se comienza con éste proceso. 
if(inputString.startsWith("Sp")){ // Si la cadena recibida comienza con las siglas Sp entra en el if.
  valorsp = inputString.substring(3); // A la variable valorsp le asgina la subcadena que se encuentra a partir del lugar 3 en el serial.
  setpoint=valorsp.toFloat();//Se convierte a entero flotante el valor de la constante "valorsp" y se lo asigna a el valor setpoint.   
  Serial.print("sp: "); Serial.println(setpoint);//Imprime el valor del setpoint asignado en el serial.
                                }
 borrarcadenas();//Borra la cadena recibida para poder volver a escribir indicacione en el serial.
                  } 

   lecad = analogRead(0); //Lee la señal analógica en el Pin(A0) obtenido del sensor LM35 y la convierte a digital, arroja datos de 0 a 1023.
   voltaje = lecad*(5./1024); //Hace la conversión de la señal digital a voltaje.
   Temperatura = (voltaje / 0.01);//Se hace la conversión del valor del voltaje recibido (en temperatura medida), y se le asigna al valor de la Temperatura.
  
   input=Temperatura;//El valor del input es el que se recibe como medición de la temperatura. 

   myPIDv.Compute();//Función Compute de la librería de PID que sirve para realizar el algoritmo PID y arroja el valor del output.
   myPIDr.Compute();
   analogWrite(9,outputv); //Salida del ventilador en la que la potencia de giro del mismo depende del valor que se arroje como output.
   analogWrite(6,outputr);//Salida de las resistencias en la que varía el tiempo encendido de las mismas de acuerdo a la salida output.

   if(millis()>serialTime){
    SerialSend();//Función para la impresión de datos en el Serial
    serialTime+=1000;//La impresión de datos será cada segundo
  }
   
}



void SerialSend()
{
  //Serial.print("setpoint: ");Serial.print(setpoint); Serial.print(" ");
  //Serial.print("temp: ");
  Serial.println(input);// Serial.println(" ");
  //Serial.print("outputv: ");Serial.print(outputv); Serial.print(" ");
  //Serial.print("outputr: ");Serial.print(outputr); Serial.println(" ");
}



void serialEvent() { //Función utilizada para la lectura de cadenas. 
  while (Serial.available()) { 
    char inChar = (char)Serial.read(); //Asignación a la variable inChar según la cadena recibida en el Serial. 
    if (inChar == '\n') {
      stringComplete = true; //Al percibir un enter como lectura (New Line), se le asigna el valor true a la variable stringComplete. 
    }else{
      inputString += inChar;}
    }
  }

void borrarcadenas() { //Función utilizada para borrar las cadenas, se les asigna un valor vacío a las variables de la función serialEvent y a los valores para modificar la fecha y hora.
  inputString = "";
  valorsp = "";  
  stringComplete = false;
}

String Digitos(int elemento, int opcion){//Esta función sirve para imprimir en forma de cadena un espacio o un cero antes de un dígito cuando se tiene un número menor a 10. 
  if (elemento < 10){
    if(opcion == 0)
      return "0" + String(elemento);
    if(opcion == 1)
      return " " + String(elemento);
  }
  else
    return String(elemento);
}


