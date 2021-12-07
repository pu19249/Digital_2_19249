/*************************************************************************************************
  ESP32 Web Server
  Ejemplo de creación de Web server con acceso a SPIFFS
  Basándose en los ejemplos de:
  https://github.com/khoih-prog/WiFiWebServer
  https://lastminuteengineers.com/creating-esp32-web-server-arduino-ide/
  https://github.com/luisllamasbinaburo/ESP32-Examples
  https://www.luisllamas.es/esp8266-esp32/
**************************************************************************************************/
//************************************************************************************************
// Librerías
//************************************************************************************************
#include <WiFi.h>
//#include <SPIFFS.h>
#include <WebServer.h>
//************************************************************************************************
// Variables globales
//************************************************************************************************
// SSID & Password
const char* ssid = "ESP321";  // Enter SSID here
const char* password = "12345678";  //Enter Password here
IPAddress local_ip(193, 168, 1, 1);
IPAddress gateway(193, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

WebServer server(80);  // Object of WebServer(HTTP port, 80 is defult)

uint8_t LED1pin = 2;
bool LED1status = LOW;
int status1, status2, status3;
int go;
//************************************************************************************************
// Configuración
//************************************************************************************************
void setup() {
  Serial.begin(115200);
  Serial.setTimeout(50);
  delay(100);
  Serial2.begin(115200);
  Serial2.setTimeout(50);
  delay(100);
  pinMode(LED1pin, OUTPUT);
  /*if (!SPIFFS.begin()) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
    }*/
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);
  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.print("password: ");
  Serial.println(password);

  server.on("/", handle_OnConnect); // página de inicio
  server.on("/s1", handle_s1); // handler al haber uno ocupado
  server.on("/s2", handle_s2); //
  server.on("/s3", handle_s3); //
  server.on("/s4", handle_s4); //
  server.on("/s5", handle_s5); //
  server.on("/s6", handle_s6); //
  server.on("/s7", handle_s7); //
  server.on("/s8", handle_s8); //
  server.onNotFound([]() {                  // si el cliente solicita una uri desconocida
    //if (!HandleFileRead(server.uri()))      // enviar archivo desde SPIFF, si existe
    handleNotFound();             // sino responder con un error 404 (no existe)
  });
  //server.onNotFound(handle_NotFound); //si no se encuentra el uri, responder con error 404 (no existe)

  server.begin(); // iniciar servidor
  Serial.println("HTTP server started");
  delay(100);
  pinMode(12, OUTPUT); //e
  pinMode(14, OUTPUT); //d
  pinMode(27, OUTPUT); //c
  pinMode(26, OUTPUT); //g
  pinMode(25, OUTPUT); //f
  pinMode(33, OUTPUT); //a
  pinMode(32, OUTPUT); //b
}
//************************************************************************************************
// loop principal
//************************************************************************************************
void loop() {
  server.handleClient(); // escuchar solicitudes de clientes
  if(Serial2.available()) {
 
    status2 = Serial2.read();
    if(status2 == '0'){
      Serial.print("0");
      go = 0;
      server.send(200, "text/html", SendHTML(go));
    }
    if(status2 == '1'){
      Serial.print("1");
      go = 1;
      server.send(200, "text/html", SendHTML(go));
    }
    if(status2 == '2'){
      Serial.print("2");
      go = 2;
      server.send(200, "text/html", SendHTML(go));
    }
    if(status2 == '3'){
      Serial.print("3");
      go = 3;
      server.send(200, "text/html", SendHTML(go));
    }
    if(status2 == '4'){
      Serial.print("4");
      go = 4;
      server.send(200, "text/html", SendHTML(go));
    }

  }
}




//************************************************************************************************
// Handler de página de inicio
//************************************************************************************************
void handle_OnConnect() {
  //8
  digitalWrite(33, HIGH); //
  digitalWrite(32, HIGH); //
  digitalWrite(27, HIGH); //
  digitalWrite(14, HIGH); //
  digitalWrite(12, HIGH); //
  digitalWrite(25, HIGH); //
  digitalWrite(26, HIGH); //
  status1 = 0; // inicia todo libre, por defecto
  server.send(200, "text/html", SendHTML(status1)); //responde con un OK (200) y envía HTML
}
//************************************************************************************************
// Handler de 1 ocupado
//************************************************************************************************
void handle_s1() {
  //7
  digitalWrite(33, HIGH); //
  digitalWrite(32, HIGH); //
  digitalWrite(27, HIGH); //
  digitalWrite(14, LOW); //
  digitalWrite(12, LOW); //
  digitalWrite(25, LOW); //
  digitalWrite(26, LOW); //
  status1 = 1;
  server.send(200, "text/html", SendHTML(status1)); //responde con un OK (200) y envía HTML

}
//************************************************************************************************
// Handler de 2 ocupados
//************************************************************************************************
void handle_s2() {
  //6
  digitalWrite(33, LOW); //
  digitalWrite(32, LOW); //
  digitalWrite(27, HIGH); //
  digitalWrite(14, HIGH); //
  digitalWrite(12, HIGH); //
  digitalWrite(25, HIGH); //
  digitalWrite(26, HIGH); //
  status1 = 2;
  server.send(200, "text/html", SendHTML(status1)); //responde con un OK (200) y envía HTML
}

//************************************************************************************************
// Handler de 3 ocupado
//************************************************************************************************
void handle_s3() {
  //5
  digitalWrite(33, HIGH); //
  digitalWrite(32, LOW); //
  digitalWrite(27, HIGH); //
  digitalWrite(14, HIGH); //
  digitalWrite(12, LOW); //
  digitalWrite(25, HIGH); //
  digitalWrite(26, HIGH); //
  status1 = 3;
  server.send(200, "text/html", SendHTML(status1)); //responde con un OK (200) y envía HTML
}
//************************************************************************************************
// Handler de 4 ocupados
//************************************************************************************************
void handle_s4() {
  //4
  digitalWrite(33, LOW); //
  digitalWrite(32, HIGH); //
  digitalWrite(27, HIGH); //
  digitalWrite(14, LOW); //
  digitalWrite(12, LOW); //
  digitalWrite(25, HIGH); //
  digitalWrite(26, HIGH); //
  status1 = 4;
  server.send(200, "text/html", SendHTML(status1)); //responde con un OK (200) y envía HTML
}

//************************************************************************************************
// Handler de 5 ocupado
//************************************************************************************************
void handle_s5() {
  //3
  digitalWrite(33, HIGH); //
  digitalWrite(32, HIGH); //
  digitalWrite(27, HIGH); //
  digitalWrite(14, HIGH); //
  digitalWrite(12, LOW); //
  digitalWrite(25, LOW); //
  digitalWrite(26, HIGH); //
  status1 = 5;
  server.send(200, "text/html", SendHTML(status1)); //responde con un OK (200) y envía HTML
}
//************************************************************************************************
// Handler de 6 ocupados
//************************************************************************************************
void handle_s6() {
  //2
  digitalWrite(33, HIGH); //
  digitalWrite(32, HIGH); //
  digitalWrite(27, LOW); //
  digitalWrite(14, HIGH); //
  digitalWrite(12, HIGH); //
  digitalWrite(25, LOW); //
  digitalWrite(26, HIGH); //
  status1 = 6;
  server.send(200, "text/html", SendHTML(status1)); //responde con un OK (200) y envía HTML
}

//************************************************************************************************
// Handler de 7 ocupado
//************************************************************************************************
void handle_s7() {
  //1
  digitalWrite(33, LOW); //
  digitalWrite(32, HIGH); //
  digitalWrite(27, HIGH); //
  digitalWrite(14, LOW); //
  digitalWrite(12, LOW); //
  digitalWrite(25, LOW); //
  digitalWrite(26, LOW); //
  status1 = 7;
  server.send(200, "text/html", SendHTML(status1)); //responde con un OK (200) y envía HTML
}
//************************************************************************************************
// Handler de 8 ocupados
//************************************************************************************************
void handle_s8() {
  //0
  digitalWrite(33, HIGH); //
  digitalWrite(32, HIGH); //
  digitalWrite(27, HIGH); //
  digitalWrite(14, HIGH); //
  digitalWrite(12, HIGH); //
  digitalWrite(25, HIGH); //
  digitalWrite(26, LOW); //
  status1 = 8;
  server.send(200, "text/html", SendHTML(status1)); //responde con un OK (200) y envía HTML
}
//************************************************************************************************
// Procesador de HTML
//************************************************************************************************
String SendHTML(uint8_t led1stat) {
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<title>Parqueo-matic</title>\n";
  ptr += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr += "body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr += ".button {display: block;width: 80px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr += ".button-on {background-color: #3498db;}\n";
  ptr += ".button-on:active {background-color: #2980b9;}\n";
  ptr += ".button-off {background-color: #34495e;}\n";
  ptr += ".button-off:active {background-color: #2c3e50;}\n";
  ptr += "p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";

  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<h1>Parqueo-matic &#128664</h1>\n";
  ptr += "<h3>Web Server (AP)</h3>\n";

//  if (Serial2.available()) {
//        status2 = Serial2.read();
//        if (status2 == '0') {
//          Serial.print("0");
//          ptr += "<a class=\"button button-off\" href=\"/s1\">Update</a>\n";
//  
//        }
//        if (status2 == '1') {
//          Serial.print("1");
//          ptr += "<a class=\"button button-off\" href=\"/s2\">Update</a>\n";
//        }
//        if (status2 == '2') {
//          Serial.print("2");
//          ptr += "<a class=\"button button-off\" href=\"/s3\">Update</a>\n";
//        }
//        if (status2 == '3') {
//          Serial.print("3");
//          ptr += "<a class=\"button button-off\" href=\"/s4\">Update</a>\n";
//        }
//        if (status2 == '4') {
//          Serial.print("4");
//          ptr += "<a class=\"button button-off\" href=\"/s5\">Update</a>\n";
//        }
//        if (status2 == '5') {
//          Serial.print("5");
//          ptr += "<a class=\"button button-off\" href=\"/s6\">Update</a>\n";
//        }
//        if (status2 == '6') {
//          Serial.print("6");
//          ptr += "<a class=\"button button-off\" href=\"/s7\">Update</a>\n";
//        }
//        if (status2 == '7') {
//          Serial.print("7");
//          ptr += "<a class=\"button button-off\" href=\"/s8\">Update</a>\n";
//        }
//  
//      }
  if (led1stat == 0)
  {
    //ptr += "<a class=\"button button-off\" href=\"/s8\">Update</a>\n";
    //ptr += "<a href=\"/espacio_1\"></a>\n";
    //ptr += "<a href=\"/espacio_1\"></a>\n";
    ptr += "<a class=\"button button-off\" href=\"/\">Update</a>\n";
    ptr += "<style>\n";
    ptr += ".wrapper {display: grid;grid-template-columns: repeat(4, 1fr);gap: 10px;grid-auto-rows: minmax(100px, auto);}\n";
    ptr += ".one{margin-right: 10%;border-style: ridge;background-color: MediumSeaGreen;display: flex;align-items: center;justify-content: center;grid-column: 1;grid-row: 1;}\n";
    ptr += ".two{margin-right: 10%;border-style: ridge;background-color: MediumSeaGreen;display: flex;align-items: center;justify-content: center;grid-column: 2;grid-row: 1;}\n";
    ptr += ".three{margin-right: 10%;border-style: ridge;background-color: MediumSeaGreen;display: flex;align-items: center;justify-content: center;grid-column: 3;grid-row: 1;}\n";
    ptr += ".four{margin-right: 10%;border-style: ridge;background-color: MediumSeaGreen;display: flex;align-items: center;justify-content: center;grid-column: 4;grid-row: 1;}\n";
    ptr += ".five{margin-right: 10%;border-style: ridge;background-color: MediumSeaGreen;display: flex;align-items: center;justify-content: center;grid-column: 1;grid-row: 2;}\n";
    ptr += ".six{margin-right: 10%;border-style: ridge;background-color: MediumSeaGreen;display: flex;align-items: center;justify-content: center;grid-column: 2;grid-row: 2;}\n";
    ptr += ".seven{margin-right: 10%;border-style: ridge;background-color: MediumSeaGreen;display: flex;align-items: center;justify-content: center;grid-column: 3;grid-row: 2;}\n";
    ptr += ".eight{margin-right: 10%;border-style: ridge;background-color: MediumSeaGreen;display: flex;align-items: center;justify-content: center;grid-column: 4;grid-row: 2;}\n";


    ptr += "</style>\n";
    ptr += "<body>\n";
    ptr += "<h2>Parqueos disponibles</h2>\n";
    ptr += "<div class=wrapper><div class=one>1</div><div class=two>2</div><div class=three>3</div><div class=four>4</div><div class=five>5</div><div class=six>6</div><div class=seven>7</div><div class=eight>8</div></div>\n";
    ptr += "</body>";
  }
  if (led1stat == 1)
  {
    ptr += "<a class=\"button button-off\" href=\"/s1\">Update</a>\n";
    //ptr += "<a class=\"button button-off\" href=\"/espacio_2\"></a>\n";
    //ptr += "<a href=\"/espacio_1\"></a>\n";
    ptr += "<style>\n";
    ptr += ".wrapper {display: grid;grid-template-columns: repeat(4, 1fr);gap: 10px;grid-auto-rows: minmax(100px, auto);}\n";
    ptr += ".one{margin-right: 10%;border-style: ridge;background-color: Tomato;display: flex;align-items: center;justify-content: center;grid-column: 1;grid-row: 1;}\n";
    ptr += ".two{margin-right: 10%;border-style: ridge;background-color: MediumSeaGreen;display: flex;align-items: center;justify-content: center;grid-column: 2;grid-row: 1;}\n";
    ptr += ".three{margin-right: 10%;border-style: ridge;background-color: MediumSeaGreen;display: flex;align-items: center;justify-content: center;grid-column: 3;grid-row: 1;}\n";
    ptr += ".four{margin-right: 10%;border-style: ridge;background-color: MediumSeaGreen;display: flex;align-items: center;justify-content: center;grid-column: 4;grid-row: 1;}\n";
    ptr += ".five{margin-right: 10%;border-style: ridge;background-color: MediumSeaGreen;display: flex;align-items: center;justify-content: center;grid-column: 1;grid-row: 2;}\n";
    ptr += ".six{margin-right: 10%;border-style: ridge;background-color: MediumSeaGreen;display: flex;align-items: center;justify-content: center;grid-column: 2;grid-row: 2;}\n";
    ptr += ".seven{margin-right: 10%;border-style: ridge;background-color: MediumSeaGreen;display: flex;align-items: center;justify-content: center;grid-column: 3;grid-row: 2;}\n";
    ptr += ".eight{margin-right: 10%;border-style: ridge;background-color: MediumSeaGreen;display: flex;align-items: center;justify-content: center;grid-column: 4;grid-row: 2;}\n";


    ptr += "</style>\n";
    ptr += "<body>\n";
    ptr += "<h2>Parqueos disponibles</h2>\n";
    ptr += "<div class=wrapper><div class=one>1</div><div class=two>2</div><div class=three>3</div><div class=four>4</div><div class=five>5</div><div class=six>6</div><div class=seven>7</div><div class=eight>8</div></div>\n";
    ptr += "</body>";
  }
  else if (led1stat == 2)
  {
    ptr += "<a class=\"button button-off\" href=\"/s2\">Update</a>\n";
    ptr += "<style>\n";
    ptr += ".wrapper {display: grid;grid-template-columns: repeat(4, 1fr);gap: 10px;grid-auto-rows: minmax(100px, auto);}\n";
    ptr += ".one{margin-right: 10%;border-style: ridge;background-color: Tomato;display: flex;align-items: center;justify-content: center;grid-column: 1;grid-row: 1;}\n";
    ptr += ".two{margin-right: 10%;border-style: ridge;background-color: Tomato;display: flex;align-items: center;justify-content: center;grid-column: 2;grid-row: 1;}\n";
    ptr += ".three{margin-right: 10%;border-style: ridge;background-color: MediumSeaGreen;display: flex;align-items: center;justify-content: center;grid-column: 3;grid-row: 1;}\n";
    ptr += ".four{margin-right: 10%;border-style: ridge;background-color: MediumSeaGreen;display: flex;align-items: center;justify-content: center;grid-column: 4;grid-row: 1;}\n";
    ptr += ".five{margin-right: 10%;border-style: ridge;background-color: MediumSeaGreen;display: flex;align-items: center;justify-content: center;grid-column: 1;grid-row: 2;}\n";
    ptr += ".six{margin-right: 10%;border-style: ridge;background-color: MediumSeaGreen;display: flex;align-items: center;justify-content: center;grid-column: 2;grid-row: 2;}\n";
    ptr += ".seven{margin-right: 10%;border-style: ridge;background-color: MediumSeaGreen;display: flex;align-items: center;justify-content: center;grid-column: 3;grid-row: 2;}\n";
    ptr += ".eight{margin-right: 10%;border-style: ridge;background-color: MediumSeaGreen;display: flex;align-items: center;justify-content: center;grid-column: 4;grid-row: 2;}\n";


    ptr += "</style>\n";
    ptr += "<body>\n";
    ptr += "<h2>Parqueos disponibles</h2>\n";
    ptr += "<div class=wrapper><div class=one>1</div><div class=two>2</div><div class=three>3</div><div class=four>4</div><div class=five>5</div><div class=six>6</div><div class=seven>7</div><div class=eight>8</div></div>\n";
    ptr += "</body>";
  }
  else if (led1stat == 3)
  {
    ptr += "<a class=\"button button-off\" href=\"/s3\">Update</a>\n";
    ptr += "<style>\n";
    ptr += ".wrapper {display: grid;grid-template-columns: repeat(4, 1fr);gap: 10px;grid-auto-rows: minmax(100px, auto);}\n";
    ptr += ".one{margin-right: 10%;border-style: ridge;background-color: Tomato;display: flex;align-items: center;justify-content: center;grid-column: 1;grid-row: 1;}\n";
    ptr += ".two{margin-right: 10%;border-style: ridge;background-color: Tomato;display: flex;align-items: center;justify-content: center;grid-column: 2;grid-row: 1;}\n";
    ptr += ".three{margin-right: 10%;border-style: ridge;background-color: Tomato;display: flex;align-items: center;justify-content: center;grid-column: 3;grid-row: 1;}\n";
    ptr += ".four{margin-right: 10%;border-style: ridge;background-color: MediumSeaGreen;display: flex;align-items: center;justify-content: center;grid-column: 4;grid-row: 1;}\n";
    ptr += ".five{margin-right: 10%;border-style: ridge;background-color: MediumSeaGreen;display: flex;align-items: center;justify-content: center;grid-column: 1;grid-row: 2;}\n";
    ptr += ".six{margin-right: 10%;border-style: ridge;background-color: MediumSeaGreen;display: flex;align-items: center;justify-content: center;grid-column: 2;grid-row: 2;}\n";
    ptr += ".seven{margin-right: 10%;border-style: ridge;background-color: MediumSeaGreen;display: flex;align-items: center;justify-content: center;grid-column: 3;grid-row: 2;}\n";
    ptr += ".eight{margin-right: 10%;border-style: ridge;background-color: MediumSeaGreen;display: flex;align-items: center;justify-content: center;grid-column: 4;grid-row: 2;}\n";


    ptr += "</style>\n";
    ptr += "<body>\n";
    ptr += "<h2>Parqueos disponibles</h2>\n";
    ptr += "<div class=wrapper><div class=one>1</div><div class=two>2</div><div class=three>3</div><div class=four>4</div><div class=five>5</div><div class=six>6</div><div class=seven>7</div><div class=eight>8</div></div>\n";
    ptr += "</body>";
  }
  else if (led1stat == 4)
  {
    ptr += "<a class=\"button button-off\" href=\"/s4\">Update</a>\n";
    ptr += "<style>\n";
    ptr += ".wrapper {display: grid;grid-template-columns: repeat(4, 1fr);gap: 10px;grid-auto-rows: minmax(100px, auto);}\n";
    ptr += ".one{margin-right: 10%;border-style: ridge;background-color: Tomato;display: flex;align-items: center;justify-content: center;grid-column: 1;grid-row: 1;}\n";
    ptr += ".two{margin-right: 10%;border-style: ridge;background-color: Tomato;display: flex;align-items: center;justify-content: center;grid-column: 2;grid-row: 1;}\n";
    ptr += ".three{margin-right: 10%;border-style: ridge;background-color: Tomato;display: flex;align-items: center;justify-content: center;grid-column: 3;grid-row: 1;}\n";
    ptr += ".four{margin-right: 10%;border-style: ridge;background-color: Tomato;display: flex;align-items: center;justify-content: center;grid-column: 4;grid-row: 1;}\n";
    ptr += ".five{margin-right: 10%;border-style: ridge;background-color: MediumSeaGreen;display: flex;align-items: center;justify-content: center;grid-column: 1;grid-row: 2;}\n";
    ptr += ".six{margin-right: 10%;border-style: ridge;background-color: MediumSeaGreen;display: flex;align-items: center;justify-content: center;grid-column: 2;grid-row: 2;}\n";
    ptr += ".seven{margin-right: 10%;border-style: ridge;background-color: MediumSeaGreen;display: flex;align-items: center;justify-content: center;grid-column: 3;grid-row: 2;}\n";
    ptr += ".eight{margin-right: 10%;border-style: ridge;background-color: MediumSeaGreen;display: flex;align-items: center;justify-content: center;grid-column: 4;grid-row: 2;}\n";


    ptr += "</style>\n";
    ptr += "<body>\n";
    ptr += "<h2>Parqueos disponibles</h2>\n";
    ptr += "<div class=wrapper><div class=one>1</div><div class=two>2</div><div class=three>3</div><div class=four>4</div><div class=five>5</div><div class=six>6</div><div class=seven>7</div><div class=eight>8</div></div>\n";
    ptr += "</body>";
  }
  else if (led1stat == 5)
  {
    ptr += "<a class=\"button button-off\" href=\"/s5\">Update</a>\n";
    ptr += "<style>\n";
    ptr += ".wrapper {display: grid;grid-template-columns: repeat(4, 1fr);gap: 10px;grid-auto-rows: minmax(100px, auto);}\n";
    ptr += ".one{margin-right: 10%;border-style: ridge;background-color: Tomato;display: flex;align-items: center;justify-content: center;grid-column: 1;grid-row: 1;}\n";
    ptr += ".two{margin-right: 10%;border-style: ridge;background-color: Tomato;display: flex;align-items: center;justify-content: center;grid-column: 2;grid-row: 1;}\n";
    ptr += ".three{margin-right: 10%;border-style: ridge;background-color: Tomato;display: flex;align-items: center;justify-content: center;grid-column: 3;grid-row: 1;}\n";
    ptr += ".four{margin-right: 10%;border-style: ridge;background-color: Tomato;display: flex;align-items: center;justify-content: center;grid-column: 4;grid-row: 1;}\n";
    ptr += ".five{margin-right: 10%;border-style: ridge;background-color: Tomato;display: flex;align-items: center;justify-content: center;grid-column: 1;grid-row: 2;}\n";
    ptr += ".six{margin-right: 10%;border-style: ridge;background-color: MediumSeaGreen;display: flex;align-items: center;justify-content: center;grid-column: 2;grid-row: 2;}\n";
    ptr += ".seven{margin-right: 10%;border-style: ridge;background-color: MediumSeaGreen;display: flex;align-items: center;justify-content: center;grid-column: 3;grid-row: 2;}\n";
    ptr += ".eight{margin-right: 10%;border-style: ridge;background-color: MediumSeaGreen;display: flex;align-items: center;justify-content: center;grid-column: 4;grid-row: 2;}\n";


    ptr += "</style>\n";
    ptr += "<body>\n";
    ptr += "<h2>Parqueos disponibles</h2>\n";
    ptr += "<div class=wrapper><div class=one>1</div><div class=two>2</div><div class=three>3</div><div class=four>4</div><div class=five>5</div><div class=six>6</div><div class=seven>7</div><div class=eight>8</div></div>\n";
    ptr += "</body>";
  }
  else if (led1stat == 6)
  {

    ptr += "<a class=\"button button-off\" href=\"/s6\">Update</a>\n";
    ptr += "<style>\n";
    ptr += ".wrapper {display: grid;grid-template-columns: repeat(4, 1fr);gap: 10px;grid-auto-rows: minmax(100px, auto);}\n";
    ptr += ".one{margin-right: 10%;border-style: ridge;background-color: Tomato;display: flex;align-items: center;justify-content: center;grid-column: 1;grid-row: 1;}\n";
    ptr += ".two{margin-right: 10%;border-style: ridge;background-color: Tomato;display: flex;align-items: center;justify-content: center;grid-column: 2;grid-row: 1;}\n";
    ptr += ".three{margin-right: 10%;border-style: ridge;background-color: Tomato;display: flex;align-items: center;justify-content: center;grid-column: 3;grid-row: 1;}\n";
    ptr += ".four{margin-right: 10%;border-style: ridge;background-color: Tomato;display: flex;align-items: center;justify-content: center;grid-column: 4;grid-row: 1;}\n";
    ptr += ".five{margin-right: 10%;border-style: ridge;background-color: Tomato;display: flex;align-items: center;justify-content: center;grid-column: 1;grid-row: 2;}\n";
    ptr += ".six{margin-right: 10%;border-style: ridge;background-color: Tomato;display: flex;align-items: center;justify-content: center;grid-column: 2;grid-row: 2;}\n";
    ptr += ".seven{margin-right: 10%;border-style: ridge;background-color: MediumSeaGreen;display: flex;align-items: center;justify-content: center;grid-column: 3;grid-row: 2;}\n";
    ptr += ".eight{margin-right: 10%;border-style: ridge;background-color: MediumSeaGreen;display: flex;align-items: center;justify-content: center;grid-column: 4;grid-row: 2;}\n";


    ptr += "</style>\n";
    ptr += "<body>\n";
    ptr += "<h2>Parqueos disponibles</h2>\n";
    ptr += "<div class=wrapper><div class=one>1</div><div class=two>2</div><div class=three>3</div><div class=four>4</div><div class=five>5</div><div class=six>6</div><div class=seven>7</div><div class=eight>8</div></div>\n";
    ptr += "</body>";
  }
  else if (led1stat == 7)
  {
    ptr += "<a class=\"button button-off\" href=\"/s7\">Update</a>\n";
    ptr += "<style>\n";
    ptr += ".wrapper {display: grid;grid-template-columns: repeat(4, 1fr);gap: 10px;grid-auto-rows: minmax(100px, auto);}\n";
    ptr += ".one{margin-right: 10%;border-style: ridge;background-color: Tomato;display: flex;align-items: center;justify-content: center;grid-column: 1;grid-row: 1;}\n";
    ptr += ".two{margin-right: 10%;border-style: ridge;background-color: Tomato;display: flex;align-items: center;justify-content: center;grid-column: 2;grid-row: 1;}\n";
    ptr += ".three{margin-right: 10%;border-style: ridge;background-color: Tomato;display: flex;align-items: center;justify-content: center;grid-column: 3;grid-row: 1;}\n";
    ptr += ".four{margin-right: 10%;border-style: ridge;background-color: Tomato;display: flex;align-items: center;justify-content: center;grid-column: 4;grid-row: 1;}\n";
    ptr += ".five{margin-right: 10%;border-style: ridge;background-color: Tomato;display: flex;align-items: center;justify-content: center;grid-column: 1;grid-row: 2;}\n";
    ptr += ".six{margin-right: 10%;border-style: ridge;background-color: Tomato;display: flex;align-items: center;justify-content: center;grid-column: 2;grid-row: 2;}\n";
    ptr += ".seven{margin-right: 10%;border-style: ridge;background-color: Tomato;display: flex;align-items: center;justify-content: center;grid-column: 3;grid-row: 2;}\n";
    ptr += ".eight{margin-right: 10%;border-style: ridge;background-color: MediumSeaGreen;display: flex;align-items: center;justify-content: center;grid-column: 4;grid-row: 2;}\n";


    ptr += "</style>\n";
    ptr += "<body>\n";
    ptr += "<h2>Parqueos disponibles</h2>\n";
    ptr += "<div class=wrapper><div class=one>1</div><div class=two>2</div><div class=three>3</div><div class=four>4</div><div class=five>5</div><div class=six>6</div><div class=seven>7</div><div class=eight>8</div></div>\n";
    ptr += "</body>";
  }
  else if (led1stat == 8)
  {
    ptr += "<a class=\"button button-off\" href=\"/s8\">Update</a>\n";
    ptr += "<style>\n";
    ptr += ".wrapper {display: grid;grid-template-columns: repeat(4, 1fr);gap: 10px;grid-auto-rows: minmax(100px, auto);}\n";
    ptr += ".one{margin-right: 10%;border-style: ridge;background-color: Tomato;display: flex;align-items: center;justify-content: center;grid-column: 1;grid-row: 1;}\n";
    ptr += ".two{margin-right: 10%;border-style: ridge;background-color: Tomato;display: flex;align-items: center;justify-content: center;grid-column: 2;grid-row: 1;}\n";
    ptr += ".three{margin-right: 10%;border-style: ridge;background-color: Tomato;display: flex;align-items: center;justify-content: center;grid-column: 3;grid-row: 1;}\n";
    ptr += ".four{margin-right: 10%;border-style: ridge;background-color: Tomato;display: flex;align-items: center;justify-content: center;grid-column: 4;grid-row: 1;}\n";
    ptr += ".five{margin-right: 10%;border-style: ridge;background-color: Tomato;display: flex;align-items: center;justify-content: center;grid-column: 1;grid-row: 2;}\n";
    ptr += ".six{margin-right: 10%;border-style: ridge;background-color: Tomato;display: flex;align-items: center;justify-content: center;grid-column: 2;grid-row: 2;}\n";
    ptr += ".seven{margin-right: 10%;border-style: ridge;background-color: Tomato;display: flex;align-items: center;justify-content: center;grid-column: 3;grid-row: 2;}\n";
    ptr += ".eight{margin-right: 10%;border-style: ridge;background-color: Tomato;display: flex;align-items: center;justify-content: center;grid-column: 4;grid-row: 2;}\n";


    ptr += "</style>\n";
    ptr += "<body>\n";
    ptr += "<h2>Parqueos disponibles</h2>\n";
    ptr += "<div class=wrapper><div class=one>1</div><div class=two>2</div><div class=three>3</div><div class=four>4</div><div class=five>5</div><div class=six>6</div><div class=seven>7</div><div class=eight>8</div></div>\n";
    ptr += "</body>";
  }


  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}
//************************************************************************************************
// Handler de not found
//************************************************************************************************
void handleNotFound() {
  server.send(404, "text/plain", "Not found");
}
//************************************************************************************************
// Obtener el tipo de contenido del archivo
//************************************************************************************************
String GetContentType(String filename)
{
  if (filename.endsWith(".htm")) return "text/html";
  else if (filename.endsWith(".html")) return "text/html";
  else if (filename.endsWith(".css")) return "text/css";
  else if (filename.endsWith(".js")) return "application/javascript";
  else if (filename.endsWith(".png")) return "image/png";
  else if (filename.endsWith(".gif")) return "image/gif";
  else if (filename.endsWith(".jpg")) return "image/jpeg";
  else if (filename.endsWith(".ico")) return "image/x-icon";
  else if (filename.endsWith(".xml")) return "text/xml";
  else if (filename.endsWith(".pdf")) return "application/x-pdf";
  else if (filename.endsWith(".zip")) return "application/x-zip";
  else if (filename.endsWith(".gz")) return "application/x-gzip";
  return "text/plain";
}
//************************************************************************************************
// Enviar al servidor el archivo desde SPIFFS
//************************************************************************************************
/*void ServeFile(String path)
  {
  File file = SPIFFS.open(path, "r");
  size_t sent = server.streamFile(file, GetContentType(path));
  file.close();
  }*/
//************************************************************************************************
// Enviar al servidor el archivo desde SPIFFS
//************************************************************************************************
//void ServeFile(String path, String contentType)
//{
//File file = SPIFFS.open(path, "r");
//size_t sent = server.streamFile(file, contentType);
//file.close();
//}
//************************************************************************************************
// Handler de not found
//************************************************************************************************
bool HandleFileRead(String path)
{
  if (path.endsWith("/")) path += "index.html";
  Serial.println("handleFileRead: " + path);

  //  if (SPIFFS.exists(path))
  //  {
  //    ServeFile(path);
  //    return true;
  //  }
  Serial.println("\tFile Not Found");
  return false;
}
