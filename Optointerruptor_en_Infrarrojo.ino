/* Optointerruptor IR
 *  
 *  Un led IR siempre encendido está frente a un fototransistor (FT); cuando el FT detecta la señal del led IR, enciende un LED visible, mientras que cuando no detecta la señal, el LED visible está apagado.
 */


const int pinled = 10, pinFT = 7; //se definen los pines, tanto de led visible como del fototransiostor
int state; //guarda el estado, encendido o apagado, del fototransistor


void setup() {
  pinMode(pinled, OUTPUT);
  pinMode(pinFT, INPUT);
  Serial.begin(9600);
  while(!Serial);

}

void loop() {
  state = digitalRead(pinFT); //lee el estado del fototransistor, 0 o 1
  Serial.println(state);
  digitalWrite(pinled, state); //escribe el estado en el LED: 0 (apagado) o 1 (encendido)

}
