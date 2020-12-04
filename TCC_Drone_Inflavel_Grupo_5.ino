#define LV   14          // liga ventoinha                    GPIO14(D5)
#define OUT_1  0           // saída 1                         GPIO0(D3)
#define OUT_2  13          // saída 2                         GPIO13(D7)

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <Servo.h>
#include <ESP8266WebServer.h>

String command;             //String to store app command state.
int vel = 800;         // 400 - 800.
int angle;
Servo Eixo;

const char* ssid = "TCC - Grupo 5 - Mecatrônica - Turma 4L - 2020";
ESP8266WebServer server(80);

void setup() {
 
 pinMode(LV, OUTPUT); //ventoinha
 pinMode(OUT_2, OUTPUT); //null
 Eixo.attach(OUT_1); //servo
 
  Serial.begin(115200);
  
// Conectando no WiFi

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid);

  IPAddress meuIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(meuIP);
 
 // Iniciando WEB-server 
     server.on ( "/", HTTP_handleRoot );
     server.onNotFound ( HTTP_handleRoot );
     server.begin();    
}

void frente(){ 
      analogWrite(LV, vel);

  }
void direita(){ 
      angle += 10;
      Eixo.write(angle);

  }

void esquerda(){
      angle -= 10;
      Eixo.write(angle);

  }


void direitaFrente(){ 
      angle += 10;
      Eixo.write(angle);
      analogWrite(LV, vel);

  }

void esquerdaFrente(){
      angle -= 10;
      Eixo.write(angle);
      analogWrite(LV, vel);


  }

void parar(){  
      analogWrite(LV, 0);
 }

void loop() {
    server.handleClient();
    
      command = server.arg("State");
      if (command == "F") frente();
      else if (command == "L") esquerda();
      else if (command == "R") direita();
      else if (command == "T") direitaFrente();
      else if (command == "U") esquerdaFrente();
      else if (command == "0") vel = 400;
      else if (command == "1") vel = 600;
      else if (command == "2") vel = 800;
      else if (command == "S") parar();
}

void HTTP_handleRoot(void) {

if( server.hasArg("State") ){
       Serial.println(server.arg("State"));
  }
  server.send ( 200, "text/html", "" );
  delay(1);
}
