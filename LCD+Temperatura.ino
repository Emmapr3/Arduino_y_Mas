/*
 * Por:
  * José Emmanuel Paredes Rocha
  * Jazmín G. Garduño Hernández
  
  El siguiente programa se utiliza para en una pantalla de cristal líquido (LCD) imprimir la temperatura en tiempo real que toma un sensor LM35 (conectado en el pin analógico A0),
  así como escribir la temperatura máxima y mínima que ha tomado.
  En la primera línea de la LCD se muestra la temperatura medida en tiempo real y en la segunda línea se muestran las temperaturas máximas y mínimas medidas por el LM35.

  Se utiliza un Display LCD de 16x2 y la librería existente "Liquid-Crystal". El circuito de conexión entre el LCD y el Arduino es el siguiente:
 
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
float tempmax = 0; //variable para temperatura máxima
float tempmin = 1000; //variable para la temperatura mínima

void setup() {
  Serial.begin(9600); //para iniciar el lector de los datos que recibe el puerto Serial
  while(!Serial); //Espera hasta que el puerto Serial reciba datos
  analogReference(INTERNAL); //para usar el factor de corrección obtenido (1.078) al trasformar lectura AD a voltaje
  
  //Se configura el número de columnas y filas de la LCD:
  lcd.begin(16, 2);
  // se imprime el mensaje en el LCD.
  lcd.print("Temperatur: ");

}

void loop() {
  
  lecad = analogRead(0); //lee la señal analógica en el Pin(A0) y la convierte a digital, arroja datos de 0 a 1023.
  voltaje = lecad*(1.078/1024); //hace la conversión de la señal digital a voltaje con el factor de corrección (Por ello es necesario la línea 44).
  temp = (voltaje / 0.01); //convierte el voltaje obtenido en temperatura

  //se determina si la temperatura que se mide es menor a la mínima registrada
  if( temp < tempmin){
    tempmin = temp; //se reasigna como temperatura mínima
  }
 //se determina si la temperatura que se mide es menor a la máxima registrada
  if(temp > tempmax){
    tempmax = temp; //se reasigna como temperatura máxima
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


