/*
 * 
 * Voltaje real que da el Arduino = 4.884 V
 */

int PotUno = A1;
int PotDos = A2;
int Voltaje;
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
while(!Serial)
pinMode(PotUno, INPUT);
pinMode(PotDos, INPUT);
inputString.reserve(200);
}
void loop() {

   if (stringComplete) {

     if (inputString == "UNO"){
          Voltaje = analogRead(PotUno) / 4;
          Serial.print( "Voltaje del potenciómetro UNO = ");
          Serial.println(Voltaje);
          inputString = "";
          stringComplete = false;
     }else {
      if(inputString == "DOS"){
        Voltaje = analogRead(PotDos) / 4;
          Serial.print( "Voltaje del potenciómetro DOS = ");
          Serial.println(Voltaje);
          inputString = "";
    stringComplete = false;
        }else {
          Serial.println("Error");
          inputString = "";
    stringComplete = false;
        }
      }
     }
   }
  

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    //inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }else{
      inputString += inChar;}
    }
  }

