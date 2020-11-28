//RELOJ DIGITAL
//Libreria usadas neopixel
//placa esp8266

#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Adafruit_NeoPixel.h>    // importa libreria


int hora; 
int minuto; 
int digito_1 = -1;
  int digito_2 = -1;
  int digito_3 = -1;
  int digito_4 = -1;
const char *ssid     = "arduino";
const char *password = "123456789";

const long utcOffsetInSeconds = -21600;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);
Adafruit_NeoPixel tira = Adafruit_NeoPixel(32, 2, NEO_GRB + NEO_KHZ800); // creacion de objeto "tira"  // pin 2 es D4
void setup(){
  Serial.begin(115200);
   tira.begin();       // inicializacion de la tira
  tira.show();        // muestra datos en pixel
  
 

  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }
 
  timeClient.begin();
}

void loop() {
 // s = millis()/200;  
   timeClient.update();

              // iniciado el programa y pasa a segundos
  hora =  timeClient.getHours(); 
  minuto =  timeClient.getMinutes(); 
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
        
      delay(2000);
  
 Serial.println (   hora );
     

}

void num_0(int digito){
   for(int i = 1; i < 7; i++){   // bucle para recorrer posiciones 0 a 7
    tira.setPixelColor(i+digito, 0, 255, 0);   // cada pixel en color azul (posicion,R,G,B)
    tira.show();      // muestra datos en pixel 
   
  }
}

void num_1(int digito){
    tira.setPixelColor(3+digito, 255, 0, 0);   // cada pixel en color azul (posicion,R,G,B)
     tira.setPixelColor(4+digito, 255, 0, 0);   // cada pixel en color azul (posicion,R,G,B)
    tira.show();      // muestra datos en pixel 
   
}
void num_2(int digito){
  tira.setPixelColor(2+digito, 0, 255, 0);   // cada pixel en color azul (posicion,R,G,B)
     tira.setPixelColor(3+digito, 0, 255, 0);   // cada pixel en color azul (posicion,R,G,B)
      tira.setPixelColor(0+digito, 0, 255, 0);
       tira.setPixelColor(6+digito, 0, 255, 0);   // cada pixel en color azul (posicion,R,G,B)
      tira.setPixelColor(5+digito, 0, 255, 0);
    tira.show();      // muestra datos en pixel 
   
}
void num_3(int digito){
   tira.setPixelColor(2+digito, 255, 0,0 );   // cada pixel en color azul (posicion,R,G,B)
     tira.setPixelColor(3+digito, 255, 0, 0);   // cada pixel en color azul (posicion,R,G,B)
      tira.setPixelColor(0+digito, 255, 0, 0);
       tira.setPixelColor(4+digito, 255, 0, 0);   // cada pixel en color azul (posicion,R,G,B)
      tira.setPixelColor(5+digito, 255, 0, 0);
    tira.show();      // muestra datos en pixel 
   
}
void num_4(int digito){
   tira.setPixelColor(0+digito, 255, 0, 0);   // cada pixel en color azul (posicion,R,G,B)
     tira.setPixelColor(1+digito, 255, 0, 0);   // cada pixel en color azul (posicion,R,G,B)
      tira.setPixelColor(3+digito, 255, 0, 0);
       tira.setPixelColor(4+digito, 255, 0, 0);   // cada pixel en color azul (posicion,R,G,B)
      
    tira.show();      // muestra datos en pixel 
   
}
void num_5(int digito){
    tira.setPixelColor(2+digito, 255, 0, 0);   // cada pixel en color azul (posicion,R,G,B)
     tira.setPixelColor(1+digito, 255, 0, 0);   // cada pixel en color azul (posicion,R,G,B)
      tira.setPixelColor(0+digito, 255, 0, 0);
       tira.setPixelColor(4+digito, 255, 0, 0);   // cada pixel en color azul (posicion,R,G,B)
      tira.setPixelColor(5+digito, 255, 0, 0);
    tira.show();      // muestra datos en pixel 
}
void num_6(int digito){
     tira.setPixelColor(0+digito, 255, 0, 0);   // cada pixel en color azul (posicion,R,G,B)
     tira.setPixelColor(1+digito, 255, 0, 0);   // cada pixel en color azul (posicion,R,G,B)
      tira.setPixelColor(2+digito, 255, 0, 0);
       tira.setPixelColor(4+digito, 255, 0, 0);   // cada pixel en color azul (posicion,R,G,B)
      tira.setPixelColor(5+digito, 255, 0, 0);
       tira.setPixelColor(6+digito, 255, 0, 0);   // cada pixel en color azul (posicion,R,G,B)
     // tira.setPixelColor(7+digito, 255, 0, 0);
      
    tira.show();      // muestra datos en pixel 
   
}
void num_7(int digito){
      tira.setPixelColor(2+digito, 255, 0, 0);   // cada pixel en color azul (posicion,R,G,B)
     tira.setPixelColor(3+digito, 255, 0, 0);   // cada pixel en color azul (posicion,R,G,B)
      tira.setPixelColor(4+digito, 255, 0, 0);
      tira.show();      // muestra datos en pixel 
}
void num_8(int digito){
       for(int i = 0; i < 7; i++){   // bucle para recorrer posiciones 0 a 7
    tira.setPixelColor(i+digito, 0, 0, 255);   // cada pixel en color azul (posicion,R,G,B)
    tira.show();      // muestra datos en pixel 
   
  }
}
void num_9(int digito){
     for(int i = 0; i < 6; i++){   // bucle para recorrer posiciones 0 a 7
    tira.setPixelColor(i+digito, 0, 0, 255);   // cada pixel en color azul (posicion,R,G,B)
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
