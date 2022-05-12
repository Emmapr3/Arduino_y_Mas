/* AJUSTE DE FECHA Y HORA MEDIANTES BOTONES Y VISUALIZARLOS EN UNA PANTALLA LCD
 *  
 *  Por: José Emmanuel Paredes Rocha
 *       Jazmpin G. Garduño Hernández
 *       (Equipo 1)
 *       
 * El siguiente programa es utilizado para modificar la fecha y hora mediante tres botones (selección, más y menos), y mostrar las mismas en una pantalla LCD.

 La moificación mediante los botones se hace con la ayuda de tres pushbotton: uno para dar cambiar el valor que se quiere modificar (hh, mm, ss, dd, ms, aa), al que se llamó "sel",
 otro llamado "más" para aunmentar el valor y un último llamado "menos" para disminuir el valor de las variables del tiempo.
 Para saber cual variable de tiempo se está modificando, en la esqiuina superior derecha de la LCd aparecerá un número, de tal forma que indicara la variable que se está cambiando,
 donde dicho número representa como sigue:
 1 : hora
 2 : minutos
 3 : segundos
 4 : día
 5 : mes
 6 : año
 
 Para este programa se requiere de lo siguiente:
 1) Pantalla LCD 2x16
 2) 3 pushbotton
 3) 3 resistencias 10Kohms y 1 resistencias 220ohms
 4) Un potenciómetro 10kohms

 
 Conexión de los botones:
 *Botón "sel" al pin(6)
 *Botón "más" al pin(7)
 *Botón "menos" al pin(5)

 Conexión de la LCD:
 *lcd RS al pin(A5)
 *lcd EN al pin(A4)
 *lcd D4 al pin(A3)
 *lcd D3 al pin(A2)
 *lcd D2 al pin(A1)
 *lcd D1 al pin(A0)
 
 */
//Se usan la slibrerías para usar:
//LCD
#include <LiquidCrystal.h>
//tiempo
#include <Time.h>
#include <TimeLib.h>
int n=0; //Variable para el contador.
boolean seleccion;//Valor del presionado del botón sel.
boolean arriba;//Valor del presionado del botón mas.
boolean abajo;//Valor del presionado del botón menos.
//variables para la hora y la fecha
int hh=0;
int mn=0;
int ss=0;
int dd=17;
int ms=10;
int aa=2017;
//para la LCD
const int rs = A5, en = A4, d4 = A3, d5 = A2, d6 = A1, d7 = A0;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
//Pines de los botones
const int mas = 7, menos = 5, sel = 6;

void setup() {
 Serial.begin(9600); //para iniciar el lector de los datos que recibe el puerto Serial
  while(!Serial); //Espera hasta que el puerto Serial reciba datos
 //se asigna el modos de los pines de los botones
 pinMode(menos,INPUT);
 pinMode(mas,INPUT); 
 pinMode(sel,INPUT); 
 //se inicia la LCD
 lcd.begin(16, 2);
 //se asigna un tiempo inicial
 setTime(hh,mn,ss,dd,ms,aa);
 
}

void loop() {
  
  seleccion = digitalRead(sel); //se lee el botón de selección, que es el que da pauta para que los demás botones entren en juego
  //se verifica el estado del botón, si ya fue presionado, se aumenta en uno al contador, para poder comenzar a cambiar las variables de tiempo
  if(seleccion){
    esperar(seleccion,sel);
    n++;
    Serial.println(n); //imprime el valor del contador
    }
    \\lee el botón de más o de menos
  arriba = digitalRead(mas);
  abajo = digitalRead(menos);
 //mientras el contador sea de 1 a 6, se podrán modificar botones, cuando el contador llegue a 7, se vuelve el valor a cero
  if(n<7){  
    ajustarhora(); //ajusta la fecha y hora
    imprimirLCD(); //lo imprime en la pantalla
  }
  else{ n= 0; //se vuelve el valor del contador a cero
  Serial.println("0"); //imprime '0' en el monitor serial, como indicio de que está nuevamente disponible para modificar mediante los botones
  }

  imprimirLCD(); //imprime en la pantalla si no se hace modificación de alguna variable temporal


}

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

//Se imprime la hora, fecha de manera particular en la LCD
//en la primera linea se imprime: "Hora: hh:mm:ss
//en la segunda linea se imprime: "Fecha:dd/ms/aaaa
void imprimirLCD(){
 lcd.setCursor(0, 0); lcd.print("Hora");
 lcd.setCursor(6, 0); lcdDigits(hour(),1);
 lcd.setCursor(8, 0); lcd.print(":");
 lcd.setCursor(9, 0); lcdDigits(minute(),0);
 lcd.setCursor(11, 0); lcd.print(":");
 lcd.setCursor(12, 0); lcdDigits(second(),0);
 //indicador, que se imprime en la esquina superior derecha, indicando que variable se está actualizando
 lcd.setCursor(15,0);
 lcd.print(n);
 if(n == 0){ //para que quite el cero de la LCD
  lcd.setCursor(15,0);
  lcd.print(" ");
 }
//impresión de fecha
 lcd.setCursor(0, 1); lcd.print("Fecha:");
 lcd.setCursor(6, 1); lcdDigits(day(),1);
 lcd.setCursor(8, 1); lcd.print("/");
 lcd.setCursor(9, 1); lcdDigits(month(),0);
 lcd.setCursor(11, 1); lcd.print("/");
 lcd.setCursor(12, 1); lcd.print(year());
}

/*void SerialDigits(int digits, int option) {
 // utility function for digital clock display: prints preceding colon and leading 0
 if (digits < 10){
  if (option == 0){
    Serial.print('0');}
  if (option == 1){
    Serial.print(" ");}
  }
 Serial.print(digits);
}*/

//para imprimir en la LCD, si el número es menor que 10, un '0' (option=0) o un espacio (option = 1), dependiendo de la opción
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


