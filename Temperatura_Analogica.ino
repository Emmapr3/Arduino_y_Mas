/* El siguiente programa es utilizado para medir la temperatura con un sensor de temperatura LM35.
 * Dado que el sensor es analógico, se utiliza las entradas analógicas del Arduino que la convierten a señal digital de 2^10 bits.
 * Se utiliza la alimentación de 5V que proporciona el Arduino, y la entrada analógica A0 del mismo.
 * 
 * Puesto que el voltaje va de 0 a 5V (variado por un potenciometro/resistencia variable), y la señal digital de 0 a 1023 (2^10 bit),
 se hace determina el voltaje al que equivale cada bit, de tal forma que cada bit es (5/1024) volts.
 *
 *Al colocar el sensor LM35, este trasductor determina varia el voltaje en función de la temperatura de su cubierta, como V(T)=0.01T (T en °C);
 así se puede convertir de voltaje a temperatura como T(V)=100*V
 *
 *Por: Garduño Hernández Jazmín y Paredes Rocha José Emmanuel.
 */

int lecad; //variable para leer el estado analógico
float voltaje; //varibale para voltaje
float temp; //variable para temperatura

void setup() {
  Serial.begin(9600); //para iniciar el lector de los datos que recibe el puerto Serial

  while(!Serial); //Espera hasta que el puerto Serial reciba datos

}

void loop() {
  //Primero el Arduino recibe la señal analógica y la convierte a digital con una memoria de 2^10 bits.
  lecad = analogRead(0); //lee la señal analógica en el Pin(A0) y la convierte a digital, arroja datos de 0 a 1023
  voltaje = lecad*(5./1024); //hace la conversión de la señal digital a voltaje
  temp = (voltaje / 0.01); //convierte el voltaje leído en temperatura
  //Serial.print(voltaje); //imprime los datos en pantalla recibidos del puerto Serial en voltaje
  //Serial.println(" V"); //para imprimir las unidades de voltaje en el monitor Serial
  Serial.print(temp); //imprime los datos en pantalla recibidos del puerto Serial en temperatura
  Serial.println(" °C"); //imprime las unidades temperatura después de los datos
  delay(1000); //controla que cada segundo arroje un dato
}

/*Comentarios de la gráfica de temperatura
 * Se dejó pasar un tiempo antes de comnezar a graficar, con el propósito que se estabilizara a la temperatura ambiente (~26°C).
 * En el primer valle, se tocó la parte superior del LM35, después se dejó estabilizar a la ambiente.
 * En la barrera más pronunciada, se dejó tomó con la mano por un tiempo LM35 (en la g´rafica se observa como sube hasta estabilizarse a ~32°C), y después se soltó.
 * Termina a en la temperatura del laboratiorio.
 * /
 */
