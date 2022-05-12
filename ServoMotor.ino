#include <Servo.h>

const int pinPot = A0, pinSer = 9; // el pin dle potenciómetro es analógico, y el del Servomootor es pin PW

Servo servo; //definición del onjeto servo de la clase Servo

void setup() {
  pinMode(pinPot, INPUT);
  pinMode(pinSer, OUTPUT);

  servo.attach(pinSer); //se ancla el servo al pin pinSer
  

}

void loop() {
  int lec = analogRead(pinPot);
  lec = map(lec, 0, 1023, 0, 180);

  servo.write(lec);
  delay(15);

}
