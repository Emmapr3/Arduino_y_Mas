/******************************************************************************
Force_Sensitive_Resistor_Example.ino
Example sketch for SparkFun's force sensitive resistors
  (https://www.sparkfun.com/products/9375)
Jim Lindblom @ SparkFun Electronics
April 28, 2016

Haciendo un circuito divisor de voltaje combinado con un FSR y una resistencia de 3.3K.
- La resistencia se conecta entre el pin del FSR (pin analógico) y tierra.
- El FSR se conecra entre el pin analógico y 5V
Como la resistencia del FSR decrece (es decir, la presión incrementa), el voltaje en el pin analógico debe incrementar.

El pin analógico del FSR utilizado es el A1.

vásea la imagen para conexión https://cdn.sparkfun.com/assets/learn_tutorials/5/1/0/fritzing_example_bb_2.png

******************************************************************************/
const int FSR_PIN = A1; // Pin del FSR/divisor de voltaje

// Medir el voltaje real de salida del Arduino y la resistencia real de 3.3K.
// Introducir los valores a continuación:
const float VCC = 4.50; // Voltaje de salida del Arduino
const float R_DIV = 6000.0; // Resistencia medida de la resistencia de 3.3K

void setup() 
{
  Serial.begin(9600);
  pinMode(FSR_PIN, INPUT);
}

void loop() 
{
  /*int fsrADC = analogRead(FSR_PIN); //lectura analógica del FSR
  // Si el FSR no está presionado, la resistencia debería tender a infinito, y por tanto el voltaje debería ser cercano a cero;
  //pero hay que recordar que hay una fuerza mínima de encendido (20-100 g), por lo que el voltaje cera pequeño, pero no muy cercano a cero
  //En este sentido, de manera ideal, si el voltaje es cero, indica que no hay presión; en cambio, si es distinto de cero, hay que convertir la
  //lectura analógica a presión, en referencia a la curva de calibración
  if (fsrADC != 0)
  {
    // Usando la lectura ADC, se calcula el voltaje de salida del FSR:
    float fsrV = fsrADC * VCC / 1023.0;
    // Usando el voltaje del FSR y la resistencia fija, se calcula la resistencia del FSR: 
    float fsrR = R_DIV * (VCC / fsrV - 1.0); //de la ecuación de división de voltaje
    //Serial.println("Resistance: " + String(fsrR) + " ohms");
    // Estimando la fuerza basada en la curva característica de conductancia contra fuerza
    //de la datasheet del FSR (https://www.sparkfun.com/datasheets/Sensors/Pressure/fsrguide.pdf)
    float force;
    float fsrG = 1.0 / fsrR; // Conductancia
    // La curva característica se parte en dos rectas de distinta pendiente, en 600g:
    //se asignan los parámetros de la curva característica, con ajuste C = m*F+b ->F = (C-b)/m 
    if (fsrR <= 600)
      force = (fsrG - 0.00075) / 0.00000032639;
    else
      force =  fsrG / 0.000000642857;
    Serial.println("Force: " + String(force) + " g");
    Serial.println();

    delay(500);
  }
  else
  {
    // No pressure detected
    //Serial.println("NoForce");
  }*/

  Serial.println(ForceVal() );
  delay(500);
}


/***************** Funcion para convertir voltaje en fuerza ******/
/******************************************************************************
Force_Sensitive_Resistor_Example.ino
Example sketch for SparkFun's force sensitive resistors
  (https://www.sparkfun.com/products/9375)
Jim Lindblom @ SparkFun Electronics
April 28, 2016

Haciendo un circuito divisor de voltaje combinado con un FSR y una resistencia de 3.3K.
- La resistencia se conecta entre el pin del FSR (pin analógico) y tierra.
- El FSR se conecra entre el pin analógico y 5V
Como la resistencia del FSR decrece (es decir, la presión incrementa), el voltaje en el pin analógico debe incrementar.

El pin analógico del FSR utilizado es el A1.

vásea la imagen para conexión https://cdn.sparkfun.com/assets/learn_tutorials/5/1/0/fritzing_example_bb_2.png

******************************************************************************/

float ForceVal(){
int fsrADC = analogRead(FSR_PIN); //lectura analógica del FSR
  // Si el FSR no está presionado, la resistencia debería tender a infinito, y por tanto el voltaje debería ser cercano a cero;
  //pero hay que recordar que hay una fuerza mínima de encendido (20-100 g), por lo que el voltaje cera pequeño, pero no muy cercano a cero
  //En este sentido, de manera ideal, si el voltaje es cero, indica que no hay presión; en cambio, si es distinto de cero, hay que convertir la
  //lectura analógica a presión, en referencia a la curva de calibración
  float force = 0; // valor que guarda la fuerza
  if (fsrADC != 0)
  {
    // Usando la lectura ADC, se calcula el voltaje de salida del FSR:
    float fsrV = fsrADC * VCC / 1023.0;
    // Usando el voltaje del FSR y la resistencia fija, se calcula la resistencia del FSR: 
    float fsrR = R_DIV * (VCC / fsrV - 1.0); //de la ecuación de división de voltaje
    //Serial.println("Resistance: " + String(fsrR) + " ohms");
    // Estimando la fuerza basada en la curva característica de conductancia contra fuerza
    //de la datasheet del FSR (https://www.sparkfun.com/datasheets/Sensors/Pressure/fsrguide.pdf)
    //float force;
    float fsrG = 1.0 / fsrR; // Conductancia
    // La curva característica se parte en dos rectas de distinta pendiente, en 600g:
    //se asignan los parámetros de la curva característica, con ajuste C = m*F+b ->F = (C-b)/m 
    if (fsrR <= 600)
      force = (fsrG - 0.00075) / 0.00000032639;
    else
      force =  fsrG / 0.000000642857;
    //Serial.println("Force: " + String(force) + " g");
    //Serial.println();
  }
    return force; // la función retorna el valor de la fuerza
}


