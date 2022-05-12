const int dirX = A0, dirY = A1; //Pines analógicos que leerán las direcciones X y Y
const int Push = 7; //Pin digital para leer el estado del botón del Joystick
const int LedX = 11, LedY = 10; //Pines de los LEDs que tomarán el valor que arroje el Joystick en PWM
const int LedPush = 12; //LED que se activa con la presión del botón Push




void setup() {
  pinMode(dirX, INPUT);
  pinMode(dirY, INPUT);
  pinMode(Push, INPUT);
  pinMode(LedX, OUTPUT);
  pinMode(LedY, OUTPUT);
  pinMode(LedPush, OUTPUT);
  
  Serial.begin(9600);
  while(!Serial);

}

void loop() {
  int lecX = map(analogRead(dirX), 0, 1023, 0, 255);
  int lecY = map(analogRead(dirY), 0, 1023, 0, 255);
  analogWrite(LedX, lecX);
  analogWrite(LedY, lecY);

  if(digitalRead(Push)==0){
    digitalWrite(LedPush, HIGH);
  }else{
    digitalWrite(LedPush, LOW);
  }
//Serial.println(digitalRead(Push));
  

}
