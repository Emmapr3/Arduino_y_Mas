/*
 * Las vueltas hacia la derecha del motor, generan que la posición del Encoder aumente, mientras que las vueltas hacía la izquierda generan que la posición disminuta,
 considerando en el Encoder PinA =CLK y Pinb = DT 
 */


#include <PID_v1.h>

//Encoder
int encoderPinA = 2; //CLK
int encoderPinB = 3; //DT
int encoderPos= 0;
int encoderPinALast = LOW;
int StatePinA = LOW;

//Motor
const int MotorIzq = 10;
const int MotorDer = 9;

//Potenciómetro
const int pinPot = A0;

//PID control
double Entrada, Salida, Setpoint;
/* Valores que funcionan más o menos bien: kp = 50, ki = 0.25, kd = .01 para [-10,10]*/
double kp= 50., ki = .25, kd= .01;
PID PIDM(&Entrada,&Salida,&Setpoint, kp, ki, kd, DIRECT);

//Limites de posición del motor
int liminf = -15;
int limsup = 15;



void setup() {
  //Modo de los pines del Encoder
  pinMode(encoderPinA, INPUT);
  pinMode(encoderPinB, INPUT);
  //Modo del pin del potenciómetro
  pinMode(pinPot, INPUT);
  //Modo de los pines del motor (los de salida)
  pinMode(MotorIzq, OUTPUT);
  pinMode(MotorDer, OUTPUT);
  //Inicializar puerto Serial
  Serial.begin(9600);
  //Para el PID
  PIDM.SetMode(AUTOMATIC); //Modo automático del control PID
  PIDM.SetOutputLimits(0,120); //Se establecen los límites de salida (para regular velocidad de giro del motor DC)
 
}

void loop() {
  Setpoint = map(analogRead(pinPot),0, 1018, liminf, limsup); //Se define el SetPoint del control PID, dado por la posición del potenciómetro, entre los valores liminf y limsup

  Entrada = EncoderPosition(); //La variable de entrada del control como la da la posición del Encoder
  //Impresión de los valores Setpoint y Entrada
  Serial.print(Setpoint);
  Serial.print("\t");
  Serial.println(Entrada);
  //Serial.print("\t");

/*** Hay dos situaciones, cuando la entrada es mayor al setpoint, por lo que el control debe ser inverso y se debe de rotar hacia la izquierda (para reducir la entrada), 
 y cuando la salida es menor que el setpoint, el control debe ser directo y se debe rotar a la derecha (para aumentar la salida ***/

  if( Entrada > Setpoint){
    PIDM.SetControllerDirection(REVERSE); //Se define la dirección del control como inverso (disminuir)
    PIDM.Compute(); //Se calcula el valor de la salida
    //Serial.print("INV \t");
    //Serial.println(Salida);
    //Se rota a la izquierda
    analogWrite(MotorIzq, Salida);
    analogWrite(MotorDer, 0);
    }
    else{
      PIDM.SetControllerDirection(DIRECT); //Se define la dirección del control como directo (aumentar)
      PIDM.Compute(); //Se calcula el valor de la salida
      //Serial.print("DIR \t");
      //Serial.println(Salida);
      //Se rota a la derecha
      analogWrite(MotorDer, Salida);
      analogWrite(MotorIzq, 0);
    }


//Serial.println(map(analogRead(pinPot),0,1018, liminf, limsup));

//Serial.println(EncoderPosition());
 
}

int EncoderPosition(){
  StatePinA = digitalRead(encoderPinA);
  if ((encoderPinALast == LOW) && (StatePinA == HIGH)) {
    if (digitalRead(encoderPinB) == LOW) {
      encoderPos--;
    } else {
      encoderPos++;
    }
  }
  encoderPinALast = StatePinA;
  return encoderPos;
}

