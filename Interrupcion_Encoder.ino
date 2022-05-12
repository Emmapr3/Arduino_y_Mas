#include <Stepper.h>

#include <Encoder.h>

#define PASOS 200

Encoder Enc(2,3); // se define el objeto Enc que es un Encoder

Stepper MaP(PASOS, A0,A1,A2,A3); //se define el motor a Pasos

const int Boton = 4;

long newposition;
long oldposition = 0;

void setup() {
  Serial.begin(9600);
  while(!Serial);
  MaP.setSpeed(100);
  

}

void loop() {
  newposition = Enc.read();
  Serial.println(newposition);

  if(newposition != oldposition){

    if(newposition > oldposition){
      MaP.step( newposition - oldposition);
    }
    else{
      MaP.step( newposition - oldposition);
    }
  }

  oldposition = newposition;
  
}
