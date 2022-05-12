const int Pot1 = A0, Pot2 = A1;
int var1, var2;

void setup() {
  Serial.begin(9600);
  while(!Serial);
  pinMode(Pot1, INPUT);
  pinMode(Pot2, INPUT);
}

void loop() {
  var1 = analogRead(Pot1);
  var2 = analogRead(Pot2);
  Serial.print(var1);
  Serial.print("\t");
  Serial.println(var2); 
  delay(50); 

}
