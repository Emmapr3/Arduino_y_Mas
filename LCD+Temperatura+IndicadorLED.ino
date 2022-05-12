/* Por:
  * José Emmanuel Paredes Rocha
  * Jazmín G. Garduño Hernández
  
  El siguiente programa se utiliza para en una pantalla de cristal líquido (LCD) imprimir la temperatura en tiempo real que toma un sensor LM35 (conectado en el pin analógico A0),
  asignar a través del monitor serial la temperatura mínima y máxima, e imprimirlas en el LCD; además, utilizando tres LEDs (rojo, amarillo y verde), que estos determinen al encenderse
  si la temperatura que mide el LM35 esta por debajo de la mínima (LED verde), está por encima de la máxima asginada (LED rojo) o está entre las anteriores (LED amarillo).
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

// Se incluye la librería:
#include <LiquidCrystal.h>

// se inicializa la librería asociando los pines de la LCD con los números de pin a las que se conecta en el Arduino
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); //inicializa LCD
int lecad; //variable para leer el estado analógico
float voltaje; //varibale para voltaje
float temp; //variable para temperatura
float tempmax; //variable para temperatura máxima
float tempmin; //variable para la temperatura mínima
int ledRed = 8; // Pin LED Rojo
int ledGreen = 10; // Pin LED Verde
int ledYellow = 9; //Pin LED Amarillo
String inputString = "";         // cadena para almacenar los datos introducidos en el monitor serie
boolean stringComplete = false;  // variable para determinar si la cadena está completa
String indicacion = "";   //para guardar 'Mn' o 'Mx'
String temperatura = "";  //para guardar valor de temperatura máxima o mínima

void setup() {
  //Serial.begin(9600); //para iniciar el lector de los datos que recibe el puerto Serial
  //while(!Serial); //Espera hasta que el puerto Serial reciba datos
  analogReference(INTERNAL); //para usar el factor de corrección obtenido al trasformar lectura AD a voltaje
  //determinar que los pines de los LEDs son de salida
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledYellow, OUTPUT);

  Serial.begin(9600); //para iniciar el lector de los datos que recibe el puerto Serial
  while(!Serial); //Espera hasta que el puerto Serial reciba datos
  inputString.reserve(200); //guardar memoria (200) para la cadena que se introduce
  
  //Se configura el número de columnas y filas de la LCD:
  lcd.begin(16, 2);
  // se imprime el mensaje en el LCD.
  lcd.print("Temperatur: ");

}

void loop() {
  //cuando la cadena se itroduce en el monitor serial, se maneja para determinar si es la temperatura máxima o mínima, y el valor correspondiente
  if (stringComplete) {
    indicacion = inputString.substring(0,2); //toma los dos primeros caracteres de la cadena
    temperatura = inputString.substring(3); //toma el valor (número) asignado en la cadena
    
    if(indicacion == "Mn"){ //Si es la mínima
      tempmin = temperatura.toFloat(); //asigna el valor a la temperatura mínima como número flotante
      //se imprime la temperatura mínima en el monitor serial
      Serial.print("Temperatura mínima = ");
      Serial.println(tempmin);
      //se vacian las cadenas utilizadas, para que se puedan volver a llenar
      inputString = "";
      temperatura = "";
      indicacion= "";
    } 

    if(indicacion == "Mx"){ //Si es la máxima
      tempmax = temperatura.toFloat(); //asigna el valor a la temperatura máxima como número flotante
      //se imprime la temperatura máxima en el monitor serial
      Serial.print("Temperatura máxima = ");
      Serial.println(tempmax);
      //se vacian las cadenas utilizadas, para que se puedan volver a llenar
      inputString = "";
      temperatura = "";
      indicacion= "";
    }
    
  }
  lecad = analogRead(0); //lee la señal analógica en el Pin(A0) y la convierte a digital, arroja datos de 0 a 1023
  voltaje = lecad*(1.078/1024); //hace la conversión de la señal digital a voltaje con el factor de corrección.
  temp = (voltaje / 0.01); //convierte el voltaje obtenido en temperatura

  if( temp < tempmin){ //si la temperatura medida por el LM35 está por debajo de la mínima asignada
    //enciende sólo el LED verde
    digitalWrite(ledGreen, HIGH);
    digitalWrite(ledRed, LOW);
    digitalWrite(ledYellow, LOW);  
  } else{
    if(temp > tempmax){ //si la temperatura medida por el LM35 está por debajo de la máxima asignada
    //enciende sólo el LED rojo
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledYellow, LOW);
    } else { //si la temperatura medida por el LM35 está entre las temperaturas máxima y mínima asignadas
      //enciende sólo el LED amarillo
      digitalWrite(ledYellow, HIGH);
      digitalWrite(ledRed, LOW);
      digitalWrite(ledGreen, LOW);
    }
  }

 //se determina si el valor de la temperaura tiene uno o dos dígitos antes del punto, para que la impresión en el LCD no se "recorra".
  if (temp < 10){ //para las temperaturas con un sólo dígito antes del punto
  lcd.setCursor(13, 0); //se posiciona el cursor en el LCD
  lcd.print(temp, 1); //imprime el valor de la temperatura medida, con un sólo decimal
    delay(1000); //arroja una medición cada segundo
  } else{ //para las temperaturas con dos dígitos con después del punto
    lcd.setCursor(12, 0);
    lcd.print(temp, 1);
    delay(1000);
  }

  //Para colocar la temperatura mínima y máxima
  lcd.setCursor(0,1); //se posiciona cursor en LCD al inicio de segunda línea
  lcd.print("Mn:"); //indica la temperatura mínima como la abreviación 'Mn'
  lcd.setCursor(3,1);
  lcd.print(tempmin, 1); //imprime valor temperatura mínima
  lcd.setCursor(9,1); //posiciona cursor en LCD a la mitad de la segunda línea
  lcd.print("Mx:"); //indica la temperatura máxima como la abreviación 'Mx'
  lcd.setCursor(12,1); 
  lcd.print(tempmax,1); //imprime valor de temperatura máxima
}

//función tomada del ejemplo "SerialEvent"
void serialEvent() {
  while (Serial.available()) { //wait while the serial monitor does not have input
    char inChar = (char)Serial.read(); //read each character input
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') { // '\n' is new line in Monitor Serie
      stringComplete = true; //with new line the string is complete
    }else{
      inputString += inChar;} //add each character to string 'inputString'
    }
  }
