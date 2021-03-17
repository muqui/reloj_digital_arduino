//RELOJ DIGITAL 
// https://github.com/muqui/reloj_digital_arduino/blob/master/reloj_esp8266_neopixel.ino
//Libreria usadas neopixel
//placa esp8266
//Version ESP8266 community version 2.7.3
//NOTAS:
//Para suber el codigo es necesario desconecar el moduo bluetooth, de lo contrario es imposible cargar el codigo

#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Adafruit_NeoPixel.h>    // importa libreria
#include <TimeLib.h>
#include <time.h>
#include <Timezone.h>    // https://github.com/JChristensen/Timezone

int hora; 
int minuto; 
int digito_1 = -1;
  int digito_2 = -1;
  int digito_3 = -1;
  int digito_4 = -1;
const char *ssid     = "arduino";
const char *password = "123456789";



//const long utcOffsetInSeconds = -21600;
const long utcOffsetInSeconds = 0;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
static tm getDateTimeByParams(long time){
    struct tm *newtime;
    const time_t tim = time;
    newtime = localtime(&tim);
    return *newtime;
}

static String getDateTimeStringByParamsHora(tm *newtime, char* pattern = (char *)"%H"){
    char buffer[30];
    strftime(buffer, 30, pattern, newtime);
    return buffer;
}

static String getDateTimeStringByParamsMinuto(tm *newtime, char* pattern = (char *)"%H"){
    char buffer[30];
    strftime(buffer, 30, pattern, newtime);
    return buffer;
}
 

static String getEpochStringHora(long time, char* pattern = (char *)"%H"){
//    struct tm *newtime;
    tm newtime;
    newtime = getDateTimeByParams(time);
    return getDateTimeStringByParamsHora(&newtime, pattern);
}

static String getEpochStringMinuto(long time, char* pattern = (char *)"%M"){
//    struct tm *newtime;
    tm newtime;
    newtime = getDateTimeByParams(time);
    return getDateTimeStringByParamsMinuto(&newtime, pattern);
}

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);
// Central European Time (Frankfurt, Paris)
TimeChangeRule CDT = { "CDT", First, Sun, Apr, 2, -300 };    //Daylight time = UTC - 5 hours
TimeChangeRule CST = { "CST", Last, Sun, Oct, 2, -360 };     //Standard time = UTC - 6 hours
Timezone CE(CDT, CST);
Adafruit_NeoPixel tira = Adafruit_NeoPixel(32, 2, NEO_GRB + NEO_KHZ800); // creacion de objeto "tira"  // pin 2 es D4
//COLORES
uint32_t magenta = tira.Color(255, 0, 255);   // cada pixel en color azul (R,G,B)
uint32_t rojo = tira.Color(255, 0, 0);
uint32_t verde = tira.Color(0, 255, 0);
uint32_t azul = tira.Color(0, 0, 255);
uint32_t blanco = tira.Color(255, 255, 255);
uint32_t color = rojo;
char dato; // Carácter que recibimos por bluetooth
String comando; // Comando que generamos con los caracteres
void setup(){
  Serial.begin(9600);
   tira.begin();       // inicializacion de la tira
  tira.show();        // muestra datos en pixel
  
 

  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }
 
  timeClient.begin();
   delay ( 1000 );
   if (timeClient.update()){
     Serial.print ( "Adjust local clock" );
     unsigned long epoch = timeClient.getEpochTime();
     // HERE I'M UPDATE LOCAL CLOCK
     setTime(epoch);
  }else{
     Serial.print ( "NTP Update not WORK!!" );
  }
}
// Lee el puerto serie hasta recibir el último carácter
void LeerPuertoSerie() {
 comando = "";
 while(Serial.available()){
    delay(10);
    if(Serial.available() > 0) {
     dato = Serial.read();
     comando += dato;
    }
 }  
}
void actualizar(){
   numero(digito_1, 0);
   numero(digito_2, 7);
   numero(digito_3, 14);
   numero(digito_4, 21);
  }
void loop() {
   // lee los comandos por el puerto serie
 LeerPuertoSerie();
 if (comando.length() > 0) {
  if(comando == "blanco") { //Accion
    color = blanco;
    actualizar();
     Serial.println("rojo");
    }
    if(comando == "rojo") { //Accion
    color = rojo;
    actualizar();
     Serial.println("rojo");
    }
    if(comando == "verde") { //Accion
       color = verde;
        actualizar();
       Serial.println("verde");
    }
     if(comando == "azul") { //Accion
        color = azul;
         actualizar();
         Serial.println("azul");
    }
    if(comando == "60") { //Accion
        tira.setBrightness(60);
        
    }
    if(comando == "80") { //Accion
        tira.setBrightness(80);
        
    }
     if(comando == "100") { //Accion
        tira.setBrightness(100);
        
    }
     if(comando == "120") { //Accion
        tira.setBrightness(120);
        
    }
     if(comando == "140") { //Accion
        tira.setBrightness(140);
        
    }
     if(comando == "160") { //Accion
        tira.setBrightness(160);
        
    }
    if(comando == "180") { //Accion
        tira.setBrightness(180);
        
    }
     if(comando == "200") { //Accion
        tira.setBrightness(200);
        
    }
     if(comando == "220") { //Accion
        tira.setBrightness(220);
        
    }
     if(comando == "250") { //Accion
        tira.setBrightness(250);
        
    }
 }
 // s = millis()/200;  
 //  timeClient.update();

              // iniciado el programa y pasa a segundos
//  hora =  timeClient.getHours(); 
//  minuto =  timeClient.getMinutes(); 
  hora = getEpochStringHora(CE.toLocal(now())).toInt();
  minuto = getEpochStringMinuto(CE.toLocal(now())).toInt();

   int d_1 = minuto % 10;  
   int d_2 = (minuto/10) % 10;
  
 
  if (hora > 12){
      hora = hora - 12;  
     
  }    
   int d_3 = hora % 10;
   int d_4 = (hora/10) % 10;

   
          if(digito_1 != d_1){
             apagar_digito(0);
           digito_1 = minuto % 10;
            numero(digito_1, 0);
        }
       // numero(digito_1, 0);

        if(digito_2 != d_2){
          apagar_digito(7);
          digito_2 = (minuto/10) % 10;
          numero(digito_2, 7);
        }
        //numero(digito_2, 7);
         if(digito_3 != d_3){
          apagar_digito(14);
          digito_3 =  hora % 10;
         numero(digito_3, 14);
        }
       //  numero(digito_3, 14);
         if(hora > 9){
           if(digito_4 != d_4){
          apagar_digito(21);
          digito_4 = (hora/10) % 10;
         numero(digito_4, 21);
        }
          //numero(digito_4, 21);
         }

         else  
         apagar_digito(21);
        
    // led separador hora y minuto 
  tira.setPixelColor(28, color);   // cada pixel en color azul (posicion,R,G,B)
  tira.setPixelColor(29, color);   // cada pixel en color azul (posicion,R,G,B)
    tira.show();      // muestra datos en pixel 
   delay ( 1000 );
    tira.setPixelColor(28, 0, 0, 0);   // cada pixel en color azul (posicion,R,G,B)
  tira.setPixelColor(29, 0, 0, 0);   // cada pixel en color azul (posicion,R,G,B)
    tira.show();      // muestra datos en pixel 
   delay ( 1000 );
  Serial.print(hora);
   Serial.print(" : " );
 Serial.println(minuto);
 Serial.println(color);

}

void num_0(int digito){
   for(int i = 1; i < 7; i++){   // bucle para recorrer posiciones 0 a 7
    tira.setPixelColor(i+digito,color);   // cada pixel en color azul (posicion,R,G,B)
    tira.show();      // muestra datos en pixel 
   
  }
}

void num_1(int digito){
    tira.setPixelColor(3+digito,color);   // cada pixel en color azul (posicion,R,G,B)
     tira.setPixelColor(4+digito,color);   // cada pixel en color azul (posicion,R,G,B)
    tira.show();      // muestra datos en pixel 
   
}
void num_2(int digito){
  tira.setPixelColor(2+digito,color);   // cada pixel en color azul (posicion,R,G,B)
     tira.setPixelColor(3+digito,color);   // cada pixel en color azul (posicion,R,G,B)
      tira.setPixelColor(0+digito, color);
       tira.setPixelColor(6+digito, color);   // cada pixel en color azul (posicion,R,G,B)
      tira.setPixelColor(5+digito,color);
    tira.show();      // muestra datos en pixel 
   
}
void num_3(int digito){
   tira.setPixelColor(2+digito, color);   // cada pixel en color azul (posicion,R,G,B)
     tira.setPixelColor(3+digito, color);   // cada pixel en color azul (posicion,R,G,B)
      tira.setPixelColor(0+digito, color);
       tira.setPixelColor(4+digito, color);   // cada pixel en color azul (posicion,R,G,B)
      tira.setPixelColor(5+digito, color);
    tira.show();      // muestra datos en pixel 
   
}
void num_4(int digito){
   tira.setPixelColor(0+digito,color);   // cada pixel en color azul (posicion,R,G,B)
     tira.setPixelColor(1+digito, color);   // cada pixel en color azul (posicion,R,G,B)
      tira.setPixelColor(3+digito, color);
       tira.setPixelColor(4+digito, color);   // cada pixel en color azul (posicion,R,G,B)
      
    tira.show();      // muestra datos en pixel 
   
}
void num_5(int digito){
    tira.setPixelColor(2+digito,color);   // cada pixel en color azul (posicion,R,G,B)
     tira.setPixelColor(1+digito, color);   // cada pixel en color azul (posicion,R,G,B)
      tira.setPixelColor(0+digito, color);
       tira.setPixelColor(4+digito, color);   // cada pixel en color azul (posicion,R,G,B)
      tira.setPixelColor(5+digito, color);
    tira.show();      // muestra datos en pixel 
}
void num_6(int digito){
     tira.setPixelColor(0+digito,color);   // cada pixel en color azul (posicion,R,G,B)
     tira.setPixelColor(1+digito, color);   // cada pixel en color azul (posicion,R,G,B)
      tira.setPixelColor(2+digito, color);
       tira.setPixelColor(4+digito, color);   // cada pixel en color azul (posicion,R,G,B)
      tira.setPixelColor(5+digito, color);
       tira.setPixelColor(6+digito,color);   // cada pixel en color azul (posicion,R,G,B)
     // tira.setPixelColor(7+digito, color);
      
    tira.show();      // muestra datos en pixel 
   
}
void num_7(int digito){
      tira.setPixelColor(2+digito,color);   // cada pixel en color azul (posicion,R,G,B)
     tira.setPixelColor(3+digito, color);   // cada pixel en color azul (posicion,R,G,B)
      tira.setPixelColor(4+digito, color);
      tira.show();      // muestra datos en pixel 
}
void num_8(int digito){
       for(int i = 0; i < 7; i++){   // bucle para recorrer posiciones 0 a 7
    tira.setPixelColor(i+digito,color);   // cada pixel en color azul (posicion,R,G,B)
    tira.show();      // muestra datos en pixel 
   
  }
}
void num_9(int digito){
     for(int i = 0; i < 6; i++){   // bucle para recorrer posiciones 0 a 7
    tira.setPixelColor(i+digito, color);   // cada pixel en color azul (posicion,R,G,B)
    tira.show();      // muestra datos en pixel 
}

}


void apagar_digito(int digito){
     for(int i = 0; i < 7; i++){   // bucle para recorrer posiciones 0 a 7
    tira.setPixelColor(i+digito, 0, 0, 0);   // cada pixel en color azul (posicion,R,G,B)
    tira.show();      // muestra datos en pixel 
    }
}

void apagar(){
   for(int i = 0; i < 32; i++){   // bucle para recorrer posiciones 0 a 7
    tira.setPixelColor(i, 0, 0, 0);   // cada pixel en color azul (posicion,R,G,B)
    tira.show();      // muestra datos en pixel 
   
  }
}
void numero(int numero, int digito){  //numero: numero a dibujar, digito: posicion del digito digito 1 = 0 , digito 2 = 7 digito 3 = 14, digito 4 = 21
  switch (numero){
    case 0:
    num_0(digito);
    break;
     case 1:
     num_1(digito);
    break;
     case 2:
     num_2(digito);
    break;
     case 3:
     num_3(digito);
    break;
     case 4:
     num_4(digito);
    break;
     case 5:
     num_5(digito);
    break;
     case 6:
     num_6(digito);
    break;
     case 7:
     num_7(digito);
    break;
     case 8:
     num_8(digito);
    break;
     case 9:
     num_9(digito);
    break;
    
    
  }
 
}
