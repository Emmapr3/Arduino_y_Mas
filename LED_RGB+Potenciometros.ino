
int Pot1 = A0;
int Pot2 = A1;
int Pot3 = A2;
int pinR = 11;
int pinG = 10;
int pinB = 9;
//int voltP1; //Para guardar la lectura del potenciómetro de 0 a 1023
 


void setup() {
  Serial.begin(9600);
  while(!Serial){}
  pinMode(Pot1, INPUT);
  pinMode(Pot2, INPUT);
  pinMode(Pot3, INPUT);
  pinMode(pinR, OUTPUT);
  pinMode(pinG, OUTPUT);
  pinMode(pinB, OUTPUT);

}

void loop() {
  //voltaje  = analogRead(pinPot);
  //Serial.println(voltaje/4); //voltaje/4 da valores de 0 a 255 (8 bits)
  //analogWrite(pinLed, voltaje/4);
 Serial.println(analogRead(Pot1));
 Serial.println(analogRead(Pot2));
 Serial.println(analogRead(Pot3));
 analogWrite(pinR, analogRead(Pot1) /4 );
 analogWrite(pinG, analogRead(Pot2) /4 );
 analogWrite(pinB, analogRead(Pot3) /4 );
 
 //delay(1000);

}
