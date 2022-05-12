/* El siguiente programa cuenta con el factor de corrección para calibrar la medición real de la temperatura, con un sensor LM35.
 *  
 *  En primer instancia se comparó la temperatura del agua medida con el LM35 y con un termómetro real.
 *  
 *  Se usó la referencia análoga interna, y se ontuvo un factor de referencia de 1.078, obteniendo que cuando el sensor recibía 0.87 V, arrojaba en el monitor serial un a lectura de 380 (en promedio). 
 *  
 *  Por: Garduño Hernández Jazmín y Paredes Rocha J. Emmanuel 
 */

int lecad; //variable para leer el estado analógico
float voltaje; //varibale para voltaje
float temp; //variable para temperatura

void setup() {
  Serial.begin(9600); //para iniciar el lector de los datos que recibe el puerto Serial

  while(!Serial); //Espera hasta que el puerto Serial reciba datos

  analogReference(INTERNAL); //para usar el factor de corrección obtenido al trasformar lectura AD a voltaje

  

}

void loop() {
  //Primero el Arduino recibe la señal analógica y la convierte a digital con una memoria de 2^10 bits.
  lecad = analogRead(0); //lee la señal analógica en el Pin(A0) y la convierte a digital, arroja datos de 0 a 1023
  voltaje = lecad*(1.078/1024); //hace la conversión de la señal digital a voltaje con el factor de corrección (Por ello es necesario la línea 19).
  temp = (voltaje / 0.01); //convierte el voltaje obtenido en temperatura
  //Serial.println(lecad); //imprime los datos en pantalla recibidos del puerto Serial en voltaje
  //Serial.println(" V"); //para imprimir las unidades de voltaje en el monitor Serial
  Serial.print(temp + 0.5); //imprime los datos en pantalla recibidos del puerto Serial en temperatura    **Se corrige el medio grado, por incertidumbre del LM35**
  Serial.println(" °C"); //imprime las unidades temperatura después de los datos
  delay(1000); //controla que cada segundo arroje un dato
}
