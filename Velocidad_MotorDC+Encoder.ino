//#include <Encoder.h>

//Encoder Enc(2,3); // se define el objeto Enc que es un Encoder

//Para el motor DC
const int pinPot = A0;
const int pinIzq = 10;
const int pinDer = 9;
int lim1 = 400;
int lim2 = 550;

//Para el Encoder SIN libreria
int encoderPinA = 2; //CLK
int encoderPinB = 3; //DT
int encoderPos= 0;
int encoderPinALast = LOW;
int StatePinA = LOW;

void setup() {
  Serial.begin(9600);
  while(!Serial);
  pinMode(pinPot, INPUT);
  pinMode(pinIzq, OUTPUT);
  pinMode(pinDer, OUTPUT);

}

void loop() {
 int lec = analogRead(pinPot);
  //Serial.print(lec);
  //Serial.print("\t");

  if(lec > 0 && lec < lim1){
    int lec1 = map(lec, 0, lim1, 255, 0);
    analogWrite(pinIzq,lec1);
    analogWrite(pinDer, 0);
    Serial.print(lec1);
    Serial.print("\t");
  }
  else{ if(lec > lim2 && lec < 1023){
      int lec2 = map(lec, lim2, 1023, 0, 255);
      analogWrite(pinDer, lec2 );
      analogWrite(pinIzq, 0);
      Serial.print(lec2);
    Serial.print("\t");
      } 
  else{
        analogWrite(pinDer,0);
        analogWrite(pinIzq,0);
      }
      }
  Serial.println(EncoderPosition());
}

//función para leer posición de encoder SIN libreria
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
