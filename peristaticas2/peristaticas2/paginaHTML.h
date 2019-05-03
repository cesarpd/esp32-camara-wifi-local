String pagina_conexion ="off"; //variable para detrminar la pagina que muestra con conexion wifi o sin conexion wifi
//String tiempo_bomba1_leido="123";

//////////////////////////////pagina web/////////////
String pagina = "<!DOCTYPE html>"
"<html>"
"<head>"
"<title>Bombas Peristaticas</title>"
"<meta charset='UTF-8'>"
"<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"
"<link rel=\"icon\" href=\"data:,\">"
"<style> html { font-family: Helvetica;"
    "display: inline-block;"
    "margin: 0px auto;"
    "text-align: center;}</style>"
"</head>"
"<body>";
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
////////////////////////cuando hay conexion wifi//////////////////////////////
String pagina_on = "<h1>Bombas peristatica </h1>"
"<p> - Bomba 1  </p>"
"<form action='bomba' method='get'>"
"<p>Tiempo(min) : <input class='input1' name='tiempo_bomba1' type='text' size='4' maxlength='4'></p>"
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
////////////////////////////////////////////////////////
String paginafin = "</body>"
"</html>";
String mensaje = "";
/////////////////////////////////////