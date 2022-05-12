#include <PID_v1.h> //Libreria PID


/*****Para el sensor de presión SEN-09375********/
const int FSR_PIN = A1; // Pin del FSR/divisor de voltaje

// Medir el voltaje real de salida del Arduino y la resistencia real de 3.3K.
// Introducir los valores a continuación:
const float VCC = 4.50; // Voltaje de salida del Arduino
const float R_DIV = 6000.0; // Resistencia medida de la resistencia de 3.3K


/************Para el motor DC **************/
const int MotorIzq = 10; //pin del motor DC para girar a la izquierda ----- Hacia adelante
const int MotorDer = 9; //pin del motor DC para girar a la derecha ----- Hacia atrás
int pinPot = A0; //pin del potenciómetro, para determinar la velocidad y dirección de giro del motor DC
int MotorLim1 = 400; //valor para separar la dirección de giro del motor DC, izquierda
int MotorLim2 = 550; //valor para separar la dirección de giro del motor DC, derecha

/************ tiempo de presion *********/
float tiempoPresion =2.2 ; //tiempo de presion en segundos segundos
float tiempoAnterior; //variable para reiniciar el tiempo
float tiempoActual; //variable que guarda el tiempo en curso

/************* cantidad de presión ******/
float fuerzaPromedio = 300; // fuerza promedio en gramos
float incertidumbreFuerza = 50; //incertidumbre de la fuerza (más, menos) en gramos

 /****** variables para el control ******/
 
 boolean EstadoControl = false; //determina si el control está en función o no está en función
double Entrada, Salida, Setpoint = fuerzaPromedio;
/* Valores que funcionan más o menos bien: kp = 50, ki = 0.25, kd = .01 para [-10,10]*/
double kp= .5, ki = .005, kd= 0.0001;
PID PIDM(&Entrada,&Salida,&Setpoint, kp, ki, kd, DIRECT);

float valorminimoControl = 50.; //valor a partir de el cual el control se comienza a activar


void setup() {
  //definición del modo de los pines, Entrada y Salida
  pinMode(MotorIzq, OUTPUT);
  pinMode(MotorDer, OUTPUT);
  pinMode(pinPot, INPUT);
  // definición de pin para el FSR
  pinMode(FSR_PIN, INPUT);
  //se inicial la comunicación Serial
  Serial.begin(9600);
  while(!Serial);
  //control PID
  PIDM.SetMode(AUTOMATIC); //Modo automático del control PID

}

void loop() {
  /*int lecSenPres = analogRead(SenPres); //lectura analógica del sensor de presión 0-1023
  Serial.println(lecSenPres); //imprimir el valor*/
  float ForceValue = ForceVal(); //valor de la fuerza conforme la lectura analógica del FSR, tomando en cuenta el divisor de voltaje y la curva de ccalibración del sensor
  //Serial.println(ForceValue); 

  //Activar el control a partir de un valor un valor mínimo de fuerza (pues el FSR tiene un valor mínimo en el cual funciona)
  if(ForceValue < valorminimoControl){
    EstadoControl = false;
  } else{
    EstadoControl = true;
  }

 /* Se mueve el motor con el potenciómetro cuando no está en proceso el control */
 if( EstadoControl == false){
  movimientoMotorPot(); //se llama la función que mueve el motor con el potenciometro
 } /*Cuando el control está encendido, actual el control PID*/
 /*********** Control ******/
 else{
  Serial.print(Setpoint);
  Serial.print("\t");
  Entrada = ForceValue; //Se asigna la variable de entrada como el valor de la fuerza que regisgtra el FSR
  Serial.print(Entrada);
  Serial.print("\t");

  if(Entrada < Setpoint){ //Si la entrada está por debajo de la fuerza promedio, entonces el control es directo (aumenta valor de entrada)
    PIDM.SetControllerDirection(DIRECT);
    PIDM.Compute(); //se calcula el valor de la salida del PID
    MotorAdelante(Salida); //se hace hacia adelante el motor para aumentar la entrada
    Serial.println( Salida); //se imprime el valor de salida
  } else{ //si la entrada es mayor que el Setpoint, entonces el control es inverso para disminuir la entrada
    PIDM.SetControllerDirection(REVERSE);
    PIDM.Compute(); //calcula el valor de la salida para disminuir la entrada
    MotorAtras(Salida); // el motor se hace hacia atras para disminuir el valor de la 
    Serial.println(Salida);
  }
 }

  

}


/********* Para mover el motor con potenciómetro *******/
/* La función mueve el motor hacía adelante o hacia atrás, dependiendo del valor que mida el potenciómetro */
void movimientoMotorPot(){
  int lec = analogRead(pinPot); //lee el valor del pot 0-1023
  //Serial.print(lec); //se imprime el valor en la pantalla
  //Serial.print("\t");
  //si el valor del Pot está entre 0 y MotorLim1, gira a la izquierda; si está entre MotorLim2 y 1023 gira a la derecha
  //ambos casos, entre más se aleje del valor ValorDivision, más rápido girara, acorde a la dirección establecida
  //si se encuentra entre MotorLim1 y MotorLim, el motor no gira
  
  if(lec > 0 && lec < MotorLim1){ //Para girar a la izquieda
    int lec1 = map(lec, 0, MotorLim1, 255, 0);
    analogWrite(MotorIzq,lec1);
    analogWrite(MotorDer, 0);
    //Serial.println(lec1);
  }
  else if(lec > MotorLim2 && lec < 1023){ //Para girar a la derecha
    int lec2 = map(lec, MotorLim1, 1023, 0, 255);
      analogWrite(MotorDer, lec2);
      analogWrite(MotorIzq, 0);
      //Serial.println(lec2);
      } 
  else{ //No gira
        analogWrite(MotorDer,0);
        analogWrite(MotorIzq,0);
      }
 }

/***********Función para mover el motor hacía el frente ***********/
void MotorAdelante(int PWM){
  analogWrite(MotorIzq, PWM );
  analogWrite(MotorDer,0);
}

void MotorAtras(int PWM){
   analogWrite(MotorIzq, 0 );
   analogWrite(MotorDer,PWM);
}
/***************** Funcion para convertir voltaje en fuerza ******/
/******************************************************************************
Force_Sensitive_Resistor_Example.ino
Example sketch for SparkFun's force sensitive resistors
  (https://www.sparkfun.com/products/9375)
Jim Lindblom @ SparkFun Electronics
April 28, 2016

Haciendo un circuito divisor de voltaje combinado con un FSR y una resistencia de 3.3K.
- La resistencia se conecta entre el pin del FSR (pin analógico) y tierra.
- El FSR se conecra entre el pin analógico y 5V
Como la resistencia del FSR decrece (es decir, la presión incrementa), el voltaje en el pin analógico debe incrementar.

El pin analógico del FSR utilizado es el A1.

vásea la imagen para conexión https://cdn.sparkfun.com/assets/learn_tutorials/5/1/0/fritzing_example_bb_2.png

******************************************************************************/

float ForceVal(){
int fsrADC = analogRead(FSR_PIN); //lectura analógica del FSR
  // Si el FSR no está presionado, la resistencia debería tender a infinito, y por tanto el voltaje debería ser cercano a cero;
  //pero hay que recordar que hay una fuerza mínima de encendido (20-100 g), por lo que el voltaje cera pequeño, pero no muy cercano a cero
  //En este sentido, de manera ideal, si el voltaje es cero, indica que no hay presión; en cambio, si es distinto de cero, hay que convertir la
  //lectura analógica a presión, en referencia a la curva de calibración
  float force = 0; // valor que guarda la fuerza
  if (fsrADC != 0)
  {
    // Usando la lectura ADC, se calcula el voltaje de salida del FSR:
    float fsrV = fsrADC * VCC / 1023.0;
    // Usando el voltaje del FSR y la resistencia fija, se calcula la resistencia del FSR: 
    float fsrR = R_DIV * (VCC / fsrV - 1.0); //de la ecuación de división de voltaje
    //Serial.println("Resistance: " + String(fsrR) + " ohms");
    // Estimando la fuerza basada en la curva característica de conductancia contra fuerza
    //de la datasheet del FSR (https://www.sparkfun.com/datasheets/Sensors/Pressure/fsrguide.pdf)
    //float force;
    float fsrG = 1.0 / fsrR; // Conductancia
    // La curva característica se parte en dos rectas de distinta pendiente, en 600g:
    //se asignan los parámetros de la curva característica, con ajuste C = m*F+b ->F = (C-b)/m 
    if (fsrR <= 600)
      force = (fsrG - 0.00075) / 0.00000032639;
    else
      force =  fsrG / 0.000000642857;
    //Serial.println("Force: " + String(force) + " g");
    //Serial.println();
  }
    return force; // la función retorna el valor de la fuerza
}

