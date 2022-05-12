/* 
LIGHT TO FRECUENCY SENSOR

SENSOR: TSL235R
*/

volatile unsigned long contador = 0;
unsigned long cuentasanteriores = 0;
unsigned long t = 0;
unsigned long tiempoanterior;


void setup() 
{
  Serial.begin(115200);
  //Serial.println("START");
  pinMode(2, INPUT);
  digitalWrite(2, HIGH);
  attachInterrupt(0, irq1, RISING);
}

///////////////////////////////////////////////////////////////////
//
// MAIN LOOP
//
void loop() 
{
  if (millis() - tiempoanterior >= 1000)
  {
    tiempoanterior = millis();
    t = contador;
    unsigned long hz = t - cuentasanteriores;
    //Serial.print("FREQ: "); 
    Serial.println(hz);
    //Serial.print("\t = "); 
    cuentasanteriores = t;
  }
}


void irq1()
{
  contador++;
}
