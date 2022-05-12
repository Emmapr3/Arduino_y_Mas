/* Por:
  * José Emmanuel Paredes Rocha
  * Jazmín G. Garduño Hernández
  
  El siguiente programa se utiliza para en una pantalla de cristal líquido (LCD) imprimir la temperatura en tiempo real que toma un sensor LM35 (conectado en el pin analógico A0),
  asignar a través del monitor serial la temperatura mínima y máxima, e imprimirlas en el LCD; además, utilizando tres LEDs (rojo, amarillo y verde), que estos determinen al encenderse
  si la temperatura que mide el LM35 esta por debajo de la mínima (LED verde), está por encima de la máxima asginada (LED rojo) o está entre las anteriores (LED amarillo).
  Se utiliza un 
  En la primera línea de la LCD se muestra la temperatura medida en tiempo real y en la segunda línea se muestran las temperaturas máximas y mínimas medidas por el LM35.
  
  **IMPORTANTE: el Monitor Serie debe estar en modo "NEW LINE"/"NUEVA LINEA"**
  *En el Monitor Serial, la temperatura mínima se introduce como una cadena "Mn_valor" y la máxima con la cadena "Mx_valor#, donde '_' es un espacio (o cualquier otro caracter).
  Se imprime en el monitor Serial la temperatura mínima y máxima asignadas.

  Se utiliza un Display LCD de 16x2 y la librería existente "Liquid-Crystal".
  El circuito de conexión entre el LCD y el Arduino es el siguiente:
 
 * LCD VSS/GND pin to pin GND
 * LCD VCC pin to pin 5V
 * LCD VE pin to resistor 10K
 * LCD RS pin to digital pin 12
 * LCD R/W pin to pin GND
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * 10K resistor: ends to +5V and ground 
 * wiper to LCD VO pin (pin 3)
 * LCD Intenal LED: LCD LED+ pin to pin 5V (with resistence 220) | LCD LED- pin to pin GND
 Véase para más detalle: https://www.arduino.cc/en/uploads/Tutorial/LCD_Base_bb_Schem.png
 
*/


// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int lecad; //variable para leer el estado analógico
float voltaje; //varibale para voltaje
float temp; //variable para temperatura
float tempmax; //variable para temperatura máxima
float tempmin; //variable para la temperatura mínima
int ledRed = 8; // Pin LED Rojo
int ledGreen = 10; // Pin LED Verde
int ledYellow = 9; //Pin LED Amarillo
int Foco = 13; //Pin del Foco
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
String indicacion = "";   //para guardar máx o min
String temperatura = "";  //para guardar valor de temperatura max o min

void setup() {
  //Serial.begin(9600); //para iniciar el lector de los datos que recibe el puerto Serial
  //while(!Serial); //Espera hasta que el puerto Serial reciba datos
  analogReference(INTERNAL); //para usar el factor de corrección obtenido al trasformar lectura AD a voltaje
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(Foco, OUTPUT);
    // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial)
  inputString.reserve(200);
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
//  Print a message to the LCD.
  lcd.print("Temperatur: ");

}

void loop() {
  if (stringComplete) {
    indicacion = inputString.substring(0,2);
    temperatura = inputString.substring(3);
    
    if(indicacion == "Mn"){
      tempmin = temperatura.toFloat();
      Serial.print("Temperatura mínima = ");
      Serial.println(tempmin);
      inputString = "";
      temperatura = "";
      indicacion= "";
    } 
    if(indicacion == "Mx"){
      tempmax = temperatura.toFloat();
      Serial.print("Temperatura máxima = ");
      Serial.println(tempmax);
      inputString = "";
      temperatura = "";
      indicacion= "";
    }
    
  }
  lecad = analogRead(0); //lee la señal analógica en el Pin(A0) y la convierte a digital, arroja datos de 0 a 1023
  voltaje = lecad*(1.078/1024); //hace la conversión de la señal digital a voltaje con el factor de corrección (Por ello es necesario la línea 19).
  temp = (voltaje / 0.01); //convierte el voltaje obtenido en temperatura

  if( temp < tempmin){
    digitalWrite(ledGreen, HIGH);
    digitalWrite(ledRed, LOW);
    digitalWrite(ledYellow, LOW);
    digitalWrite(Foco, LOW); 
  } else{
    if(temp > tempmax){
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledYellow, LOW);
    digitalWrite(Foco, HIGH); 
    } else {
      digitalWrite(ledYellow, HIGH);
      digitalWrite(ledRed, LOW);
      digitalWrite(ledGreen, LOW);
    }
  }


  if (temp < 10){
  lcd.setCursor(13, 0);
  lcd.print(temp, 1); //imprime el valor de la temperatura medida
    delay(1000);
  } else{
    lcd.setCursor(12, 0);
    lcd.print(temp, 1); //imprime el valor de la temperatura medida
    delay(1000);
  }

  //Para colocar la temperatura mínima y máxima
  lcd.setCursor(0,1);
  lcd.print("Mn:");
  lcd.setCursor(3,1);
  lcd.print(tempmin, 1);
  lcd.setCursor(9,1);
  lcd.print("Mx:");
  lcd.setCursor(12,1);
  lcd.print(tempmax,1);
}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }else{
      inputString += inChar;}
    }
  }
/* void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}*/
