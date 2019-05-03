
#include "time.h" // libreria para obtener la hora 
#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
//#include <Preferences.h> // leer y grabar en la EPROM
#include "images.h"
#include "conexion_wifi.h"
////
//Preferences preferences;
//OLED pins to ESP32 GPIOs via this connecthin:
//OLED_SDA -- GPIO5
//OLED_SCL -- GPIO4
//OLED_RST -- GPIO16

// SSD1306  display(0x3c, 5, 4);
//typedef void (*Demo)(void);
//const char* ssid1 = "MOVISTAR_792F";        //Indicamos el nombre de la red WiFi (SSID) a la que queremos conectarnos.
//const char* password = "4927Jesus";    //Indicamos la contraseña de de red WiFi
// ESP32WebServer server(80);                  //Definimos el puerto de comunicaciones


int PinLED = 16; // GPIO2                  //Definimos el pin de salida - GPIO2 / D4
int estado = LOW; 
String peticion ="";

////// pagina web //////                      


        
            /*//// funciones ////

 /* 
void pagina_inicio() {
String menssage = pagina + mensaje + paginafin;
server.send(200,"Pagina de INCIO", menssage); 
}*/
 /////pagina configuracion/////
void paginaconf() {
  server.on("/", pagina_inicio);
  server.on("/escanear", escanear);
  server.on("/guardar", wifi_conf);
  server.on("/bomba", bomba_datos);
 // server.on("/SSID", pagina_inicio1);
}
void bomba_datos(){
//int tiempo_bomba=0;	
String gettiempo_bomba="";
String getcantidad_bomba="";
preferences.begin("my-app",false);
for (uint8_t i=0; i<server.args(); i++){
    if (server.argName(i)=="tiempo_bomba1"){ 
	// argumento nombre String que recivimos de la pagina por el metodo GET
	gettiempo_bomba = server.arg(i);
	// cadena Strin que recivimos de la pagina por el metodo GET
	gettiempo_bomba = arregla_simbolos(gettiempo_bomba); 
	  //Reemplazamos los simbolos que aparecen cun UTF8 por el simbolo correcto
	
	preferences.putString("EEtiempo_bomba1", gettiempo_bomba);
	 // guardamos el valor en la memoria no volatil
	 Serial.println(" valor guardado tiemp 1");
	 	Serial.println(gettiempo_bomba);
	//tiempo_bomba =(gettiempo_bomba.toInt());
	// convertimos cadena Strin recivida en entero
}
if (server.argName(i)=="tiempo_bomba2"){ 
		gettiempo_bomba = server.arg(i);
		gettiempo_bomba = arregla_simbolos(gettiempo_bomba); 
		preferences.putString("EEtiempo_bomba2", gettiempo_bomba);
	}
if (server.argName(i)=="tiempo_bomba3"){ 
		gettiempo_bomba = server.arg(i);
		gettiempo_bomba = arregla_simbolos(gettiempo_bomba);
		preferences.putString("EEtiempo_bomba3", gettiempo_bomba);
	}
if (server.argName(i)=="tiempo_bomba4"){ 
		gettiempo_bomba = server.arg(i);
		gettiempo_bomba = arregla_simbolos(gettiempo_bomba);
		preferences.putString("EEtiempo_bomba4", gettiempo_bomba);
	}	

if (server.argName(i)=="cantidad_bomba1"){
	getcantidad_bomba = server.arg(i);
	getcantidad_bomba = arregla_simbolos(getcantidad_bomba);
	preferences.putString("EEcant_bomba1", getcantidad_bomba);
	Serial.println(" valor guardado catidad bomba1");
	 	Serial.println(getcantidad_bomba);
	
	}
if (server.argName(i)=="cantidad_bomba2"){
	getcantidad_bomba = server.arg(i);
	getcantidad_bomba = arregla_simbolos(getcantidad_bomba);
	preferences.putString("EEcant_bomba2", getcantidad_bomba);
	Serial.println(" valor guardado catidad bomba2");
	Serial.println(getcantidad_bomba);
	}
if (server.argName(i)=="cantidad_bomba3"){
	getcantidad_bomba = server.arg(i);
	getcantidad_bomba = arregla_simbolos(getcantidad_bomba);
	preferences.putString("EEcant_bomba3", getcantidad_bomba);
	}
	if (server.argName(i)=="cantidad_bomba4"){
	getcantidad_bomba = server.arg(i);
	getcantidad_bomba = arregla_simbolos(getcantidad_bomba);
	preferences.putString("EEcant_bomba4", getcantidad_bomba);
	}
  }
   
  preferences.end();
 
  //Serial.println(tiempo_bomba, DEC);
  pagina_inicio();
}

void setup() {
  pinMode(PinLED,OUTPUT);
  digitalWrite(PinLED, LOW);    // set GPIO16 low to reset OLED
  delay(50); 
  digitalWrite(PinLED, HIGH); // while OLED is running, must set GPIO16 in high
  
  Serial.begin(115200);
  WiFi.softAP("ESP32" , "12345678");
  
 Serial.println(" inicio setup");

  // Initialising the UI will init the display too.
  display.init();
  display.flipScreenVertically(); // posicion de la panatalla
  display.setFont(ArialMT_Plain_16); // letra por defecto 
 
 server.begin();
  paginaconf();
  intento_conexion();
 // Serial.println("retorno al setup de intento de conexion");
  }



void loop() {
  
 
  digitalWrite(PinLED, LOW);    // set GPIO16 low to reset OLED
  delay(50); 
  digitalWrite(PinLED, HIGH);
  delay(950); 
    
 //Serial.println("paso por el loop");
  //paginaconf();
 server.handleClient();
}
