/* AJUSTE DE FECHA Y HORA MEDIANTES BOTONE Y SERIAL E INICIO DE TOMA DE DATOS PARA ALMACENAR EN SD
 *  
 *  Por: José Emmanuel Paredes Rocha
 *       Jazmpin G. Garduño Hernández
 *       (Equipo 1)
 *       
 * El siguiente programa es utilizado para modificar la fecha y hora mediante tres botones (selección, más y menos), y a su vez, desde el puerto Serial con indicaciones específicas;
 de igual manera, mediante un Swicht o mediante el monitor serial se da la indicación de que se inicie o pare en el instante deseado el almacenamiento de datos en la tajera SD, en un archivo
 con el nombre predetermiando "TEMP.txt". Se usa un sensor LM35 (ya calibrado) para medir la temperatura, y se utiliza un led que enciende mientras se le está metiendo información a la SD.
 Los datos almacenados tienen el formato: Temperatura   Fecha   Hora. Los datos de fecha, hora y temperatura se muestran en un LCD.

 Las indicaciones desde el monitor Serial que se deben utilizar, van como sigue:
 *Para asignar fecha: Insertar "fecha dd/mm/aaaa"
 *Para asignar hora: Insertar "hora hh:mm:ss"
 *Para indicar que abra el archivo y almacene datos en el archivo en la SD: "iniciar almacenamiento de datos"
 *Para indicar que deje de almacenar datos y cierre el archo en la SD: "detener toma de datos"
 NOTA: El monitor Serial debe de estar modo "Newline"
 
 La moificación mediante los botones se hace con la ayuda de tres pushbotton: uno para dar cambiar el valor que se quiere modificar (hh, mm, ss, dd, ms, aa), al que se llamó "sel",
 otro llamado "más" para aunmentar el valor y un último llamado "menos" para disminuir el valor de las variables del tiempo.
 Se usa un Swicth unipolar, el cual al estar encendido permite el almacenamiento de datos en la SD, y el estar apagado hace lo contrario.

 Recordar que se usa un LED para indicar cuando se están almacenando datos en el archivo de la SD.

 Para este programa se requiere de lo siguiente:
 1) Módulo SD/micro SD, con su respectiva tarjeta
 2) sensor ML35
 3) 3 pushbotton
 4) 1 swicth unipolar
 5) 1 LED
 6) Pantalla LCD 2x16
 7) 4 resistencias 10Kohms y 2 resistencias 220ohms
 8) Un potenciómetro 10kohms

 Conexión del Módulo SD al Arduino:
 *Pin SD CS al pin(10)
 *Pin SD MOSI al pin(11)
 *Pin SD MISO al pin(12)
 *Pin SD CLK/SCK al pin(13)
 *Pin SD 3.3V y GND a los correspondientes en el Arduino
 
 Conexión de los botones:
 *Botón "sel" al pin(6)
 *Botón "más" al pin(7)
 *Botón "menos" al pin(5)
 *Swicht unipolar al pin(9)
 
 *LED en el pin(8)
 *Sensor LM35 al pin(A5)

 Conexión de la LCD:
 *lcd RS al pin(4)
 *lcd EN al pin(A4)
 *lcd D4 al pin(A3)
 *lcd D3 al pin(A2)
 *lcd D2 al pin(A1)
 *lcd D1 al pin(A0)
 
 */

//Se usan la slibrerías para usar:
//LCD
#include <LiquidCrystal.h>
//tiempo: fecha y hora
#include <Time.h>
#include <TimeLib.h>
//módulo SD
#include <SD.h>

//Para LCD
const int rs = 4, en = A4, d4 = A3, d5 = A2, d6 = A1, d7 = A0; //pines de la LCD
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); //Iniciar LCD
//Para leer temperatura
int lecad; //variable para leer el estado analógico
float voltaje; //varibale para voltaje
float temp; //variable para temperatura
//Para SD Card
const int chipSelect = 10; //SD variable
File Temp; //Archivo para guardar información
//Para SerialEvent
String inputString = "";         // Cadena para contener los datos entrantes
boolean stringComplete = false;  // bandera para detenermiar cuando la cadena se envió
String valor1="", valor2="", valor3="";  //variables para extraer los valores de día, mes, año o hora, minuto, segundo
//Para fecha y hora
int hh = 18, mm = 00, ss=00, dd = 26, ms = 10, aa = 2017; //variables para asignar el tiempo
//Los botones
const int mas = 7, menos = 5, sel = 6, SDbotton = 9; //pines de los botones
int ledPin = 8; //pin del LED
int n=0; //Variable para el contador.
boolean seleccion;//Estado del botón "sel"
boolean arriba;//Estado del botón "más"
boolean abajo;//Estado del botón "menos"
boolean guardar;//para abrir y cerrar SD
boolean abierto = false;//bandera para determianr si el archivo en la SD está abierto o no.


void setup() {

  //Iniciar el serial
  Serial.begin(9600); //para iniciar el lector de los datos que recibe el puerto Serial
  while(!Serial); //Espera hasta que el puerto Serial reciba datos
  
  //utilizar la referencia interna de temperatura del Arduino
  analogReference(INTERNAL); //para usar el factor de corrección obtenido al trasformar lectura AD a voltaje
  
  lcd.begin(16, 2); //iniciar impresión en LCD
  setTime(hh,mm,ss,dd,ms,aa);//tiempo de inicio
  
   //Iniciar la SD
  pinMode(10, OUTPUT); //chipSelect de SD, define al pin de chipSelect como salida
  //Para identificar si la tarjeta puede utilizarse
  if (!SD.begin(chipSelect)) { //si no se inicia el chipSelect, no se puede utilizar la tarjeta SD
    Serial.println("La tarjeta falló, o no está presente");
    //para imprimir en la LCD que la tarjeta SD falló
    mensajeLCD("Tarjeta fallo o", "no esta presente",2000);
    // No hace algo más
    return;
  }
  //Si se inicia, se puede utilizar la tarjeta SD
  Serial.println("La tarjeta se inició correctamente");
  //para imprimir en LCD que la tarjeta se inició correctamente
  mensajeLCD("Tarjeta inicio"," correctamente",1500);
  //imprimir encabezados en Monitor Serial
  Serial.println("TEMP \t HORA \t FECHA");  

  //LED para indicar que se están escribiendo datos en archivo de tarjeta SD
  pinMode(ledPin, OUTPUT);
}

void loop() {
   medirtemperatura();//para medir la temperatura

   
 //modificación desde botones
 seleccion = digitalRead(sel); //lee el estado del botón sel
 //Si el botón "sel" es presionado, entonces entra en el estado de modificación mediante botones
 if(seleccion){
  AjusteBotones(); //Aumenta el contador a n=1; entonces entra al ciclo 'while' 
  while(n!= 0){//rutina para ajustar fecha y hora mediante los botones
    AjusteBotones();}
 }
 
 guardar = digitalRead(SDbotton); //lee el estado del swicht
 SDbotones();//función que abre y cierra el archivo la tarjeta LCD, si el Swicth está encendido o apagado, respectivamente.
 
 
 
  //modificación desde el Serial
  //se requiere que la cadena se complete para que pueda recibir instrucciones desde el monitor serial (véase función SerialEvent() )
 if(stringComplete){
  horaSerial(); //modifica hora desde el serial
  fechaSerial(); //modifica fecha desde el 
  iniciarSD(); //abre el archivo el la tarjeta SD
  cerrarSD(); //cierra el archivo abierto en la tarjeta SD
 }

 imprimirLCD(); //imprimir fecha, hora y temperatura en LCD

 //verifica que el archivo esté abierto, si es así, guarda en el archivo la cadena info() cada segundo
 if(Temp){
 Temp.println(info()); //almacena la cadena info() en el archivo de la SD
 Serial.println(info()); //imprime en el monitor serial lo que guarda en el archivo
 delay(1000); //lo hace cada segundo
 }

}
 //cadena de la forma temperatura \t hh:mm:ss \t dd/ms/aaaa
String info(){
  return String(temp) + "\t" + Digitos(hour(),1) + ":" + Digitos(minute(),0) + ":" + Digitos(second(),0) + "\t" + Digitos(day(),1) + "/" + Digitos(month(),0) + "/" + String(year());
}

void medirtemperatura(){ //mide la temperatura con el LM35
  //Primero el Arduino recibe la señal analógica y la convierte a digital con una memoria de 2^10 bits.
  lecad = analogRead(5); //lee la señal analógica en el Pin(A0) y la convierte a digital, arroja datos de 0 a 1023
  voltaje = lecad*(1.078/1024); //hace la conversión de la señal digital a voltaje con el factor de corrección (Por ello es necesario la línea 19).
  temp = (voltaje / 0.01); //convierte el voltaje obtenido en temperatura
  }

//imprime un mensaje en la LCD, de tal forma que primero limpia lo escrito en la LCD, imprime en los dos renglones, se espera un retraso (en milisegundos)
//y vuelve a limpiar la pantalla para dejarla disponible para que se vuelva a escribir sobre ésta
//la cadena 'renglon1' se escribe en el primer renglón de la LCD y la cadena 'renglon2' en el segundo renglón.
void mensajeLCD(String renglon1, String renglon2, int retraso){
    lcd.clear();
    lcd.print(renglon1);
    lcd.setCursor(0,1);
    lcd.print(renglon2);
    delay(retraso);
    lcd.clear();
}

//al recibir la cadena en el serial "hora hh:mm:ss", toma los valores numéricos de hh, mm y ss, y los asigna a la hora, minuto y segundo en el setTime
void horaSerial(){
  if(inputString.startsWith("hora")){
  valor1 = inputString.substring(5); //toma la subcadena hh:mm:ss
  valor2 = inputString.substring(8); //toma la subcadena mm:ss
  valor3 = inputString.substring(11); //toma la subcadena ss
  //al convertir una cadena a su valor numérico entero, la conversión límita hasta donde encuenta enteros, si hay números y símbolos, sólo hace la conversión de los números
  hh = valor1.toInt(); //obtiene el valor numérico de hh
  mm = valor2.toInt(); //obtiene el valor numérico de mm
  ss = valor3.toInt(); //obtiene el valor numérico de ss
  borrarcadenas(); //vacía las cadenas y cambia la bandera de StringComplete
  setTime(hh,mm,ss,day(),month(),year()); //asigna los valores numéricos de la hora al setTime
  Serial.println(info());//imprime una vez la cadena info(), para ver la hora YA actualizada
  }
}
//al recirnir la cadena en el serial "fecha dd/ms/aaaa", toma los valores ´numéricos de dd, ms y aaaa, y los asigna añ día, el mes y el año en el setTime
void fechaSerial(){
  if(inputString.startsWith("fecha")){
  valor1 = inputString.substring(6);//toma la subcadena dd/ms/aaaa
  valor2 = inputString.substring(9); //toma la subcadena ms/aaaa
  valor3 = inputString.substring(12); //toma la subcadena aaaa
  //al convertir una cadena a su valor numérico entero, la conversión límita hasta donde encuenta enteros, si hay números y símbolos, sólo hace la conversión de los números
  dd = valor1.toInt(); //obtiene el valor numérico de dd
  ms = valor2.toInt(); //obtiene el valor numérico de ms
  aa = valor3.toInt(); //obtiene el valor numérico de aaaa
  borrarcadenas(); //vacía las cadenas y cambia la bandera de StringComplete
  setTime(hour(),minute(),second(),dd,ms,aa); //asigna los valores numéricos a la fecha en el setTime
  Serial.println(info());//imprime una vez la cadena info(), para ver la fecha YA actualizada
  }
}

//iniciar SD desde el puerto serial: inicia o detiene el almacenamiento de información en el archivo de la tarjeta SD, acorde a la instrucción recibida

//si recibe la instrucción "iniciar almacenamiento de datos", abre el archivo "TEMP.txt" en la SD
void iniciarSD(){
  if(inputString.startsWith("iniciar")){
  Temp = SD.open("Temp.txt",FILE_WRITE);
  //si el archivo se abre correctamente, escribe un encabezado, si no, entonces envía un mensaje de advertencia
  if(Temp){
    Temp.println("TEMP \t HORA \t FECHA"); //escribe encabezado en archivo
    //manda mensaje de la apertura correcta del archivo en el monitor serial y la LCD
    Serial.println("Se abrió archivo en SD"); 
    mensajeLCD("Se abrio archivo"," en SD",1000);
    digitalWrite(ledPin, HIGH); //enciende el LED, para indicar que puede guardar información en la tarjeta SD
  } else{ //si no se abre, envia mensaje de error de la apertura del archivo, tantro en el monitor serial como en la LCD
    Serial.println("Error al abrir archivo en SD");
    mensajeLCD("Error al abrir", " archivo en SD",1500);
  }
  borrarcadenas(); //vacía las cadenas usadas y cambia la bandera de StringComplete
 }
}
//si recibe la instrucción "detener almacenamiento de datos", abre el archivo "TEMP.txt" en la SD
void cerrarSD(){
  if(inputString.startsWith("detener")){
  Temp.close(); //cierra el archivo en la tarjeta SD
  digitalWrite(ledPin,LOW);//apaga el LED
  //escribe mensaje de que se cerró el archivo en el monitor serial y en la LCD
  Serial.println("Se cerró archivo en SD");
  mensajeLCD("Se cerro archivo", " en SD",1000);
  borrarcadenas();//vacía las cadenas usadas y cambia la bandera de StringComplete
 }
}
//da la inidicación de inicio y termino de escritura de datos en el archivo de la tarjeta SD, con la acción del Swicht
//si el botón está encendido, entonces abre el archivo en la SD para almacenar datos y si se apaga, dicho archivo se cierra
void SDbotones(){
  //si guardar = HIGH (el botón está encendido), checa si ya está abierto el archivo (con bandera 'abierto')
  if(guardar){
  if(abierto==false){//si no está abierto, abre el archivo
    Temp = SD.open("Temp.txt",FILE_WRITE);
    if(Temp){//si el archivo se abrió correctamente, imprime encabezado en éste
      Temp.println("TEMP \t HORA \t FECHA");
      //manda mensaje de la correcta apertura del archivo en el monitor serial y la LCD
      Serial.println("Se abrió archivo en SD");
      mensajeLCD("Se abrio archivo"," en SD",1000);
      digitalWrite(ledPin, HIGH); //enciende el LED
    } else{//si no se abre, envia mensaje de error de la apertura del archivo, tantro en el monitor serial como en la LCD
      Serial.println("Error al abrir archivo en SD");
      mensajeLCD("Error al abrir", " archivo en SD",1500);
    }
  
  }
  //si ya se abrió, se cambia la bandera, para que no vuelva a pasar por el condicional 'if' anterior
  abierto = true;
 } 
 //si el botón estpa apagado
 if(guardar == LOW){//revisa si el archivo está abierto
  if (abierto == true){//si el archivo está abierto, lo cierra y manda mensaje de que éste se cerro en el monitor serial y en la LCD
    Temp.close();
    Serial.println("Se cerró archivo en SD");
    mensajeLCD("Se cerro archivo", " en SD",1000);
    digitalWrite(ledPin,LOW);//apaga el LED
  }
  //si el archivo se cerró, se cambia la bandera para indicarlo
  abierto = false;
 }
}


//Ajusta la fecha y hora mediante los botones
void AjusteBotones(){ //lee el estado de los tres botones
  seleccion = digitalRead(sel);
  if(seleccion){ //si el botón "sel" fue presionado, se espera hasta que se suelte para recibir la indicación del cambio
    esperar(seleccion,sel);
    n++; //aunmenta en uno al contador
    }
  arriba = digitalRead(mas);
  abajo = digitalRead(menos);

  if(n<7){ //mientras el contador está entre 0 y 7, cambia los valores de la hora y la fecha en el setTime 
    ajustarhora(); //cambia cada elemento de la fecha y hora, acorde al valor del contador
    imprimirLCD(); //imprime fecha, hora y temperatura en LCD
  }
  else{ n= 0; //cuando n=7, se devuelve al valor cero, para tener la posibilidad de volver a cmabiar el tiempo con los botones
  Serial.println("0"); //imprime '0' en el monitor serial, como indicio de que está nuevamente disponible para modificar mediante los botones
  }
}

//Las siguientes funciones son utilizadas para ajustar fecha y hora mediante la función ajustarhora()

//la función esperar() identifica que el botón 'pin' haya sido presionado y soltado para poder contar el puchado de ducho botón y cambiar el estado 'var' del botón
void esperar(boolean var, int pin){
  while(var == HIGH){ //mientras se mantenga presionado el botón, sigue leyendo el estado del botón y no sale del bucle 'while' hasta que se suelte el botón
    var = digitalRead(pin);
  }
}

//la función cambiar, determina los límites máximo y mínimo que puede tomar cada elemento del tiempo (hora, minuto, segundo, día, mes y año),
//y comienza a partir del valor del elemento en el instante que se cambia
 int cambiar(int elemento, int mn, int mx){
  int var = elemento; //cambia el valor a partir del valor anterior en curso
  if(arriba){// si se presiona el botón "más", se espera hasta que se suelte y aunmenta en uno al valor del elemento
    esperar(arriba,mas);
    var++;}
  if(abajo){//si se presiona el botón "menos", se espera hasta que se suelte y disminuye en uno al valor del elemento
    esperar(abajo,menos);
    var--;} 
  //verifica que el aumento o decremento esté dentro de los límites del elemento
  if(var > mx){ var = mn;}
  if(var < mn){ var = mx;}

  return var;//retorna el nuevo valor del elemento, ya sea aunmentado o disminuido
 }

 //setTime(hour(),minute(),second(),day(),month(),year());
void ajustarhora(){
  //se usa la función cambiar() para modificar el valor de cada elemento del tiempo, se reasigna y reinicia el tiempo con setTime a parit del valor actualizado.
  //se sabe cual valor se quiere actualizar, por el número que aparece a un lado de la hora, y sigue el orden de modificación como a continuación se presenta.
  switch(n){
    case 1: //si n=1, se está en la moficación de la hora
      hh = cambiar(hour(),0,23);
      setTime(hh,minute(),second(),day(),month(),year());
      break;
    case 2://si n=2, se modifica el valor de minuto
      mm = cambiar(minute(),0,59);
      setTime(hour(),mm,second(),day(),month(),year());
      break;
    case 3://si n=3, se modifica el valor de segundo
      ss = cambiar(second(),0,59);
      setTime(hour(),minute(),ss,day(),month(),year());
      break;
     case 4://si n=4, se modifica el valor de día    
      dd = cambiar(day(),1,diasmes()); //note que el límite superior de día, depende de una función, relacionada con los días que tiene el mes
      setTime(hour(),minute(),second(),dd,month(),year());
      break;
     case 5://si n=5, se modifica el valor de mes    
      ms = cambiar(month(),1,12);
      setTime(hour(),minute(),second(),day(),ms,year());
      break;
     case 6://si n=6, se modifica el valor de año    
      aa = cambiar(year(),2000,2090);
      setTime(hour(),minute(),second(),day(),month(),aa);
      break;
  }
}

int diasmes(){
  if(month()== 2){ //si el mes es febrero, se vefirica si es bisiesto o no
    if(year()%4  == 0){ //si es bisiesto, se retorna como límite superior 29, para el día
    return 29;
    }else { return 28;} //si no lo es, se retorna el valor 28
  }
  if(month() == 4 | 6 | 9 | 11) //si el mes es abril, junio, septiembre o noviembre, el límite superior de los días es 30
  return 30;

  if(month() == 1 | 3 | 5 | 7 | 10 | 12) //si el mes es enero, marzo, mayo, julio, octubre o diciembre, el límite superior de los días es 31 
  return 31;
}
//aquí termina la sección de funciones para ajustar la hora mediante los botones

//Se imprime la hora, fecha y temperatura de un a manera particular
void imprimirLCD(){
  //Se imprime la hora en el formato hh:mm:ss
  int poshora = 0;//indica desde que posición comienza la impresión de la hora, con el formato mencionado
 //lcd.setCursor(0, 0); lcd.print("h ");
 lcd.setCursor(poshora, 0); lcdDigits(hour(),1);
 lcd.setCursor(poshora + 2, 0); lcd.print(":");
 lcd.setCursor(poshora + 3, 0); lcdDigits(minute(),0);
 lcd.setCursor(poshora + 5, 0); lcd.print(":");
 lcd.setCursor(poshora + 6, 0); lcdDigits(second(),0);
 //indicador de la variable que se está editando
 lcd.setCursor(9,0);
 lcd.print(n);
 if(n == 0){ //para que quite el cero de la LCD
  lcd.setCursor(9,0);
  lcd.print(" ");
 }
 //se imprime la hora en el formato dd/ms/aaaa
 int posfecha = 0;//indica la posición donde se comienza a imprimir la fecha, con el formato mencionado
//impresión de fecha
 //lcd.setCursor(0, 1); lcd.print("f:");
 lcd.setCursor(posfecha, 1); lcdDigits(day(),1);
 lcd.setCursor(posfecha + 2, 1); lcd.print("/");
 lcd.setCursor(posfecha + 3, 1); lcdDigits(month(),0);
 lcd.setCursor(posfecha + 5, 1); lcd.print("/");
 lcd.setCursor(posfecha + 6, 1); lcd.print(year());

 //impresión de temperatura
 lcd.setCursor(11,0); lcd.print("Temp:"); //se imprime la etiqueta "Temp:" en la primera fila de la LCD, y debajo el valor de la temperatura
 //determina desde donde se comienza a imprimir la temperatura (con un sólo decimal), acorde al número de dígitos que tiene ésta, y así asegurar que siempre el decimal
 //se encuentre en el extremo derecho inferior de la pantalla
 if(temp <10){
  lcd.setCursor(13,1);
  lcd.print(temp,1);
 }
 if(temp <100 && temp > 10){
  lcd.setCursor(12,1);
  lcd.print(temp,1);
 }
 if(temp > 100){
  lcd.setCursor(11,1);
  lcd.print(temp,1);
 }
}

//la función lcdDigist, imprime en la pantalla un cero (option = 0)  o un espacio (option = 1) si un elemento del tiempo (hh, mm, ss, dd, ms, aaaa) tiene valor menor a 10
//esto se hace para que se vea bonito en la LCD y mueva la prosición de impresión en la pantalla por causa del valor del elemento temporal
 void lcdDigits(int digits, int option) {
 // utility function for digital clock display: prints preceding colon and leading 0
 if (digits < 10){
  if (option == 0){
    lcd.print('0');}
  if (option == 1){
    lcd.print(" ");}
  }
 lcd.print(digits);
}


//La función Digitos toma un número y si este es menor a 10 le agrega un cero (si opción = 0) o un espacio (si opcion = 1) y lo devuelve en forma de cadena
String Digitos(int elemento, int opcion){
  if (elemento < 10){ //si es menor a 10, agrega un cero o un espacio, según l opción
    if(opcion == 0)
      return "0" + String(elemento);
    if(opcion == 1)
      return " " + String(elemento);
  }
  else //si no es menor a 10, retorna el valor como tal, pero en cadena
    return String(elemento);
}

//la función serialEvent() es un auxiliar para poder dar indicaciones a través del monitor serial
void serialEvent() {
  while (Serial.available()) { //mientras el serial está disponible para ingresar información, lee cada caractér como char (no como ASCII)
    char inChar = (char)Serial.read(); //y lo junta todo en una cadena
    // Si el último carácter es un salto de línea (newline), establece una bandera para poder dar un a instrucción mediante una cadena
    //por ello es que se debe tener el monitor en 'newline', para que al ingresar la cadena, se dé el salto de línea
    if (inChar == '\n') {
      stringComplete = true; //establece la bandera
    }else{
      inputString += inChar;} //si no hay salto de línea, sigue formando la cadena 
    }
  }

//borra todas las cadenas que se han llenado con la propia cadena de entrada por el serial o por subcadenas extraídas de ésta
void borrarcadenas(){
  inputString = "";
  valor1 = "";
  valor2 = "";
  valor3 = "";
  stringComplete = false; //devuelve la bandera para que se pueda volver a introducir otra cadena
}

