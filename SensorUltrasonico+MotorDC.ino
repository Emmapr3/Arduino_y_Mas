
//Para el sensor ultrasónico
long distancia;
long tiempo;
/** Pines del sensor **/
const int Echo = 2, Trigger = 3; 

//Para el motor DC
const int MotorIzq = 10;
const int MotorDer = 9;
const int DistPot = A0; //Potenciómetro que simula la distancia
const int RefDistPot = A1; //Potenciómetro que determina la distancia máxima a la que se acerca
int RefDistancia; //Para determinar la distancia máxima a la que se acerca la prensa al FSR


void setup(){
  //Definición de los pines del motor (Salida)
  pinMode(MotorIzq, OUTPUT);
  pinMode(MotorDer, OUTPUT);
  //Definicipon de los pines de los pot (Entrada)
  pinMode(DistPot, INPUT);
  pinMode(RefDistPot, INPUT);
  /****/
  Serial.begin(9600);
  /*activación del pin 2 como salida: para el pulso ultrasónico*/
pinMode(Echo, OUTPUT); 
/*activación del pin 3 como entrada: tiempo del rebote del ultrasonido*/
 pinMode(Trigger, INPUT); 
}
void loop(){
  digitalWrite(2,LOW); 
/* Por cuestión de estabilización del sensor*/
  delayMicroseconds(5);
digitalWrite(2, HIGH); 
/* envío del    pulso ultrasónico*/  
delayMicroseconds(10);
  tiempo=pulseIn(3, HIGH); 
/* Función para medir la longitud del pulso entrante.*/
  //distancia= int(0.017*tiempo);
  RefDistancia= map(analogRead(RefDistPot), 0, 1023, 0, 8);
  distancia = mapfloat(analogRead(DistPot), 0., 1023., 0., 15.);
/*fórmula para calcular la distancia obteniendo un valor entero*/
  /*Monitorización en centímetros por el monitor serial*/
  //Serial.println("Ref "+ String(RefDistancia)+" cm\t Distancia " + String(distancia)+ " cm");
  Serial.print(RefDistancia);
  Serial.print("\t");
  Serial.println(distancia);
  if(distancia > RefDistancia){
    AcercarMotor();
    }else DetenerMotor();
    
  delay(50);
}

void AcercarMotor(){
  digitalWrite(MotorDer, HIGH);
  digitalWrite(MotorIzq, LOW);
}

void AlejarMotor(){
  digitalWrite(MotorDer, LOW);
  digitalWrite(MotorIzq, HIGH);
}
void DetenerMotor(){
  digitalWrite(MotorDer, LOW);
  digitalWrite(MotorIzq, LOW);
}

//Mapeo con números flotantes
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


