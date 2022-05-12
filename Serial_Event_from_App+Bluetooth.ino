/*Prueba Bluetooth
 * 
 * Por Emmanuel Paredes Rocha y Jazmín Garduño Hernández
 * 
 * Este programa está diseñado, basándose fuertemente en el programa Serial Event (ejemplo el Arduino) para que reciba información por el monitor serial, del mismo modo que imprima dicha información
 * en una LCD. Esto para que pueda recibir cadenas desde la aplicación diseñada en App Inventor, donde en dicha aplicación debe de mandar un salto de línea ("\n") para que el Arduino pueda recibir la información 
 * (esto por el diseño de la función serialEvent()
 */

#include <LiquidCrystal.h>

const int rs = A0, en = A1, d4 =A2 , d5 = A3, d6 = A4, d7 = A5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); //inicializa LCD

int n=0;
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is 
int state = 0;
int caracter = 0;
float num;
int pinled = 10;

void setup() {
  Serial.begin(9600);
  while(!Serial){};
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(pinled, OUTPUT);

  lcd.begin(16, 2);
  // se imprime el mensaje en el LCD.

}

void loop() {

    num = random(5,110);
    Serial.println(num,2);
  if (stringComplete) {
    Serial.println(inputString);
    //lcd.setCursor(0,0);
    lcd.print(inputString);
    
    
    if(inputString.startsWith("ON") ){
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(pinled, HIGH);
      delay(1000);          
      // wait for a second
      digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
      digitalWrite(pinled, LOW);
      delay(1000);
    }
    // clear the string:
    inputString = "";
    stringComplete = false;
  }

  delay(1000);

}
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    //inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;    
    } else{
      inputString +=inChar;
    }
  }
}
