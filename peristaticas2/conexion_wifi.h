 #include <WiFi.h>  
 #include "SSD1306.h" // alias for `#include "SSD1306Wire.h"` //Incluye la librería ESP8266WiFi
 #include <ESP32WebServer.h>
#include <Preferences.h> // leer y grabar en la EPROM

#include "FS.h"
#include "SPIFFS.h"

// #include "paginaHTML.h" //donde se encuentra la pagine HTML
ESP32WebServer server(80); 
SSD1306  display(0x3c, 5, 4);
Preferences preferences;

File htmlFile;
const char* myFilePath = "/index.html";

/////////////
char ssid[20];
char pass[20];
String ssid_leido;
String pass_leido;
int ssid_tamano = 0;
int pass_tamano = 0;
int counter = 1;
String pagina_conexion ="off"; //variable para detrminar la pagina que muestra con conexion wifi o sin conexion wifi

////////////////// 
String tiempo_bomba1_leido;
String cantidad_bomba1_leido;
String tiempo_bomba2_leido;
String cantidad_bomba2_leido;
String tiempo_bomba3_leido;
String cantidad_bomba3_leido;
String tiempo_bomba4_leido;
String cantidad_bomba4_leido;
//////////
String pagina_on ="";
//////////////////////////////pagina web/////////////
//String pagina = "<!DOCTYPE html>"
//"<html>"
//"<head>"
//"<title>Bombas Peristaticas</title>"
//"<meta charset='UTF-8'>"
//"<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"
//"<link rel=\"icon\" href=\"data:,\">"
//"<style> html { font-family: Helvetica;"
//    "display: inline-block;"
//    "margin: 0px auto;"
//    "text-align: center;}</style>"
//"</head>"
//"<body>";
htmlFile = SPIFFS.open(myFilePath, FILE_READ);
while(htmlFile.available()) {
  String pagina = Serial.write(myFile.read());
}
///////////////cuando no hay conexion Wifi/////////////////////
String pagina_off = "</form>"
"<form action='guardar' method='get'>"
"SSID:<br><br>"
"<input class='input1' name='ssid' type='text'><br>"
"PASSWORD:<br><br>"
"<input class='input1' name='pass' type='password'><br><br>"
"<input class='boton' type='submit' value='GUARDAR'/><br><br>"
"</form>"
"<a href='escanear '><button class='boton'>ESCANEAR</button></a><br><br>";
/*///////////////////////cuando hay conexion wifi//////////////////////////////
String pagina_on = "<h1>Bombas peristatica </h1>"
"<p> - Bomba 1  </p>"
"<form action='bomba' method='get'>"
"<p>Tiempo(min) : <input class='input1' name='tiempo_bomba1' type='text' size='4' maxlength='4' value="+ tiempo_bomba1_leido +"></p>"

"<p> Cantidad ( ml) : <input class='input1' name='cantidad_bomba1' type='text' size='4' maxlength='4' value=" + tiempo_bomba1_leido + "></p> "
"<p><input class='boton' type='submit' value='GUARDAR'/></p>"
"<p> Bomba 2 - Tiempo -  Cantidad </p>"
"<p><button> + </button> </p>" 
"<p><button> - </button> </p>" 
"<p> Bomba 3 - Tiempo -  Cantidad </p>"
"<p><button> + </button> </p>"
"<p><button> - </button> </p>" 
"<p> Bomba 4 - Tiempo -  Cantidad </p>"
"<p><button> + </button> </p>" 
"<p><button> - </button> </p>"
"</form>";
///////////////////////////////////////////////////////*/
String paginafin = "</body>"
"</html>";
String mensaje = "";
/////////////////////////////////////

//////////////////////////////
String arregla_simbolos(String a) {
  a.replace("%C3%A1", "á");
  a.replace("%C3%A9", "é");
  a.replace("%C3%A", "i");
  a.replace("%C3%B3", "ó");
  a.replace("%C3%BA", "ú");
  a.replace("%21", "!");
  a.replace("%23", "#");
  a.replace("%24", "$");
  a.replace("%25", "%");
  a.replace("%26", "&");
  a.replace("%27", "/");
  a.replace("%28", "(");
  a.replace("%29", ")");
  a.replace("%3D", "=");
  a.replace("%3F", "?");
  a.replace("%27", "'");
  a.replace("%C2%BF", "¿");
  a.replace("%C2%A1", "¡");
  a.replace("%C3%B1", "ñ");
  a.replace("%C3%91", "Ñ");
  a.replace("+", " ");
  a.replace("%2B", "+");
  a.replace("%22", "\"");
  return a;
}
           ///// funciones  logos de la pantalla////
void drawImageWifi() {
    // see https://www.online-utility.org/image/convert/to/XBM, programa LCDAssistant 
    // on how to create xbm files
    display.drawXbm(34, 0, WiFi_Logo_width, WiFi_Logo_height,  WiFi_Logo_bits); // primer digito ancho y segundo alto

  }
void drawProgressBar() {
  int progress = (counter / 5) % 100;
   // draw the progress bar
  display.drawProgressBar(0, 32, 120, 10, progress); 
  // primer digito posicion derecha , sengundo altura 
  // tercero longitud de la barra y cuarto ancho 
  // draw the percentage as String
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 15, String(progress) + "%"); // primer digito ancho y segundo alto
    }

////////////////FUNCIONES///////////

void pagina_inicio() {
	String menssage ="";
if (pagina_conexion =="off"){	
menssage = pagina + pagina_off+ mensaje + paginafin;
}
if (pagina_conexion =="on") {
// leer datos de la memoria no volatil
preferences.begin("my-app",false);	
tiempo_bomba1_leido= preferences.getString("EEtiempo_bomba1");
cantidad_bomba1_leido= preferences.getString("EEcant_bomba1");
////

/////
tiempo_bomba2_leido= preferences.getString("EEtiempo_bomba2");
cantidad_bomba2_leido= preferences.getString("EEcant_bomba2");
tiempo_bomba3_leido= preferences.getString("EEtiempo_bomba3");
cantidad_bomba3_leido= preferences.getString("EEcant_bomba3");
tiempo_bomba4_leido= preferences.getString("EEtiempo_bomba4");
cantidad_bomba4_leido= preferences.getString("EEcant_bomba4");
preferences.end();

Serial.println(" valor leido");
	 	Serial.println(cantidad_bomba1_leido);
////////////
pagina_on = "<h1>Bombas peristatica </h1>"
"<p><form action='bomba' method='get'>"
" - Bomba 1 - - Tiempo(min) : <input class='input1' name='tiempo_bomba1' type='text' size='4' maxlength='4' value="+ tiempo_bomba1_leido +">"
" - Cantidad ( ml) : <input class='input1' name='cantidad_bomba1' type='text' size='4' maxlength='4' value=" + cantidad_bomba1_leido + ">"
" -- <input class='boton' type='submit' value='GUARDAR'/></p>"
"</form>"
"<p> <form action='bomba' method='get'>"

" - Bomba 2 - - Tiempo(min) : <input class='input1' name='tiempo_bomba2' type='text' size='4' maxlength='4' value="+ tiempo_bomba2_leido +"> "
" - Cantidad ( ml) : <input class='input1' name='cantidad_bomba2' type='text' size='4' maxlength='4' value=" + cantidad_bomba2_leido + ">  "
" -- <input class='boton' type='submit' value='GUARDAR'/></p>"
"</form>"
"<p> <form action='bomba' method='get'>"
" - Bomba 3 -  - Tiempo(min) : <input class='input1' name='tiempo_bomba3' type='text' size='4' maxlength='4' value="+ tiempo_bomba3_leido +"> "
" - Cantidad ( ml) : <input class='input1' name='cantidad_bomba3' type='text' size='4' maxlength='4' value=" + cantidad_bomba3_leido + ">  "
" -- <input class='boton' type='submit' value='GUARDAR'/></p>"
"</form>"
"<p> <form action='bomba' method='get'>"
" - Bomba 4 - - Tiempo(min) : <input class='input1' name='tiempo_bomba4' type='text' size='4' maxlength='4' value="+ tiempo_bomba4_leido +"> "
" -  Cantidad ( ml) : <input class='input1' name='cantidad_bomba4' type='text' size='4' maxlength='4' value=" + cantidad_bomba4_leido + "> "
" -- <input class='boton' type='submit' value='GUARDAR'/></p>"
"</form>";
//////////
 menssage = pagina + pagina_on+ mensaje + paginafin;
Serial.println("despues de pagina");
Serial.println(tiempo_bomba1_leido);
}	
server.send(200,"Pagina de INCIO", menssage); 
}
//void pagina_inicio1() {
//	String menssage = pagina + mensaje + paginafin;
//	server.send(200,"Pagina de INCIO", menssage); 
//}

//**** CONFIGURACION WIFI llamada desde boton Grabar *******
void wifi_conf() {
String getssid="";
String getpass="";
for (uint8_t i=0; i<server.args(); i++){
    if (server.argName(i)=="ssid"){ 
	// argumento nombre Strin que recivimos de la pagina por el metodo GET
	getssid = server.arg(i);
	// cadena Strin que recivimos de la pagina por el metodo GET
}
if (server.argName(i)=="pass"){
	getpass = server.arg(i);
}
  }
  getssid = arregla_simbolos(getssid); //Reemplazamos los simbolos que aparecen cun UTF8 por el simbolo correcto
  getpass = arregla_simbolos(getpass);
  ssid_tamano = getssid.length() + 1;  //Calculamos la cantidad de caracteres que tiene el ssid y la clave
  pass_tamano = getpass.length() + 1;

getssid.toCharArray(ssid, ssid_tamano); //Transformamos el string en un char array ya que es lo que nos pide WIFI.begin()
getpass.toCharArray(pass, pass_tamano);

// Iniciando conexion Wifi //////
  WiFi.begin(ssid, pass);     //Intentamos conectar el ESP32 con la wifi
  counter=0;
while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    	display.clear();
        drawProgressBar();
	 display.display();
	 counter=counter+10;
	 
	if (counter > 500) {
	 preferences.begin("my-app",false);
  preferences.putString("configura", "noconfigurado");
   preferences.end();
     server.send(200, "text/html", String("<h2>No se pudo realizar la conexion<br>no se guardaron los datos.</h2>"));
     display.clear();
	 display.setTextAlignment(TEXT_ALIGN_LEFT);
		display.drawString(0, 0, "192.168.4.1");
		display.drawString(0, 16, "SSID1: ESP32");
		display.drawString(0, 33, "clave: 12345678");
		display.drawString(0, 50, "access point configu");
		display.display();
		pagina_conexion="off";
      return;  
    }
	
   }
  while (WiFi.status() == WL_CONNECTED)
  {
  display.clear();
  drawImageWifi();
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 45, WiFi.localIP().toString().c_str());
  display.display();
  /////////GRABA LOS DATOS CORRECTOS///////
  preferences.begin("my-app",false);
  preferences.putString("configura", "configurado");
  preferences.putString("EEssid", getssid);
  preferences.putString("EEpass", getpass);
  preferences.end();
   //server.send(200, "text/html", String("<h2>Conexion exitosa a: "
                          //            + getssid + "<br> El pass ingresado es: " + getpass + "<br>Datos correctamente guardados." + "<br>IP LOCAL asignada" + WiFi.localIP()));
  mensaje = "<h2>Conexion exitosa a: " + getssid + "<br>Datos correctamente guardados." + "<br>IP LOCAL asignada" + WiFi.localIP().toString().c_str();
  pagina_conexion="on";
  pagina_inicio();
  }
  } 
//*********  INTENTO DE CONEXION cuando se inicia  *********************
void intento_conexion() {
preferences.begin("my-app",false);
 if (preferences.getString("configura")="configurado") {
 ssid_leido= preferences.getString("EEssid");
 pass_leido= preferences.getString("EEpass");
 // preferences.end();
    ssid_tamano = ssid_leido.length() + 1;  //Calculamos la cantidad de caracteres que tiene el ssid y la clave
    pass_tamano = pass_leido.length() + 1;
	ssid_leido.toCharArray(ssid, ssid_tamano); //Transf. el String en un char array ya que es lo que nos pide WiFi.begin()
    pass_leido.toCharArray(pass, pass_tamano);
    counter = 0;
    WiFi.begin(ssid, pass);      //Intentamos conectar
		    
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
	   display.clear();
        drawProgressBar();
	 display.display();
	  counter=counter+10;
	    if (counter > 500) {
        display.clear();
		display.setTextAlignment(TEXT_ALIGN_LEFT);
		display.drawString(0, 0, "192.168.4.1");
		display.drawString(0, 16, "SSID1: ESP32");
		display.drawString(0, 33, "clave: 12345678");
		display.drawString(0, 50, "access point configu");
		display.display();
		pagina_conexion ="off";
        return;
      }
	  
    }
 if (WiFi.status() == WL_CONNECTED) {
    display.clear();
  drawImageWifi();
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 45, WiFi.localIP().toString().c_str());
  display.display();
  pagina_conexion ="on";
 }
 }
 preferences.end();
 }

//////////////////////////////

//---------------------------ESCANEAR----------------------------
void escanear() {  
  int n = WiFi.scanNetworks(); //devuelve el número de redes encontradas
  Serial.println("escaneo terminado");
  if (n == 0) { //si no encuentra ninguna red
    Serial.println("no se encontraron redes");
    mensaje = "no se encontraron redes";
  }  
  else
  {
    Serial.print(n);
    Serial.println(" redes encontradas");
    mensaje = "";
    for (int i = 0; i < n; ++i)
    {
      // agrega al STRING "mensaje" la información de las redes encontradas 
      mensaje = (mensaje) + "<p>" + String(i + 1) + ": " + WiFi.SSID(i) + " (" + WiFi.RSSI(i) + ") Ch: " + WiFi.channel(i) + " Enc: " + WiFi.encryptionType(i) + " </p>\r\n";
      //WiFi.encryptionType 5:WEP 2:WPA/PSK 4:WPA2/PSK 7:open network 8:WPA/WPA2/PSK
      delay(10);
    }
    //Serial.println(mensaje);
	pagina_conexion ="off";
    pagina_inicio();
  }
}   
