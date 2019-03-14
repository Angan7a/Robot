#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
 
// Replace with your network credentials
const char* ssid = "Vectra-WiFi-260244";//type your ssid
const char* password = "vnet278750378";//type your password
 
ESP8266WebServer server(80);   //instantiate server at port 80 (http port)
 
String page = "";
int ledPin = 2; // onboard LED
int ledB = 12; // blue Led
int ledG = 13; // green Led
int ledR = 15; // red Led
//********************************************
int b2 = 16;
int b1 = 14;
int b0 = 5;

//*******************************************

void setup(void){
  //the HTML of the web page
  page = "<!DOCTYPE HTML>";
 page += "<html>";
 page += "<head>";
 page += "<style>";
 page += ".button {";
 page += "     background-color: #4CAF50;";
 page += "     border: none;";
 page += "     color: white;";
 page += "     padding: 60px 128px;";
 page += "     text-align: center;";
 page += "     text-decoration: none;";
 page += "     display: inline-block;";
 page += "     font-size: 16px;";
 page += "     margin: 4px 2px;";
 page += "    cursor: pointer;";
 page += "}";
 page += ".button3 {background-color: #f44336;} /* Red */";
 page += ".button4 {background-color: #f08CBA;} /* Blue */";
 page += "</style>";
 page += "</head>";
 page += "<body>";

 page += "<h1>Simple NodeMCU Web Server</h1>";
 page += "<p><a class=\"button4\" href=\"LEDOn\"><button>ON</button></a>&nbsp;<a class=\"button4\" href=\"LEDOff\"><button>OFF</button></a></p>";
 page += "<p><a class=\"button\" href=\"Drive\"><button>Drive</button></a>&nbsp;<a class=\"button\" href=\"Reverse\"><button>Reverse</button></a>&nbsp;<a class=\"button button3\" href=\"Stop\"><button>Stop</button></a></p>";
 page += "<p><a class=\"button\" href=\"Faster\"><button>Faster</button></a>&nbsp;<a class=\"button\" href=\"Slower\"><button>Slower</button></a></p>";
 page += "<p><a class=\"button\"href=\"Left\"><button>Left</button></a>&nbsp;<a class=\"button\" href=\"Right\"><button>Right</button></a></p>";

  //configure GPIO
  pinMode(b2, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(b0, OUTPUT);
  pinMode(ledR, OUTPUT);
 
  //stop all engines
  digitalWrite(b2, LOW);
  digitalWrite(b1, LOW);
  digitalWrite(b0, LOW);
   
  delay(1000);
  
  WiFi.begin(ssid, password); //begin WiFi connection
 
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
          analogWrite(ledPin, 1);
      delay(200);
      analogWrite(ledPin, 1024);
      delay(200);
  }
analogWrite(ledPin, 1010);

  server.on("/", [](){
    server.send(200, "tex t/html", page);
  });
  server.on("/Drive", [](){
    server.send(200, "text/html", page);
    digitalWrite(b2, HIGH);
    digitalWrite(b1, LOW);
    digitalWrite(b0, LOW);
    delay(1000);
  });
  server.on("/Reverse", [](){
    server.send(200, "text/html", page);
    digitalWrite(b2, HIGH);
    digitalWrite(b1, LOW);
    digitalWrite(b0, HIGH);
    delay(1000);
  });
  server.on("/Faster", [](){
    server.send(200, "text/html", page);
    digitalWrite(b2, LOW);
    digitalWrite(b1, HIGH);
    digitalWrite(b0, LOW);
    delay(1000);
  });
  server.on("/Slower", [](){
    server.send(200, "text/html", page);
    digitalWrite(b2, LOW);
    digitalWrite(b1, LOW);
    digitalWrite(b0, HIGH);
    delay(1000);
  });
  server.on("/Left", [](){
    server.send(200, "text/html", page);
    digitalWrite(b2, HIGH);
    digitalWrite(b1, HIGH);
    digitalWrite(b0, LOW);
    delay(1000);
  });
  server.on("/Right", [](){
    server.send(200, "text/html", page);
    digitalWrite(b2, LOW);
    digitalWrite(b1, HIGH);
    digitalWrite(b0, HIGH);
    delay(1000);
  });
  server.on("/Stop", [](){
    server.send(200, "text/html", page);
    digitalWrite(b2, LOW);
    digitalWrite(b1, LOW);
    digitalWrite(b0, LOW);
    delay(1000);
  });
  server.on("/LEDOn", [](){
    server.send(200, "text/html", page);
    digitalWrite(ledR, HIGH);
    delay(1000);
  });
  server.on("/LEDOff", [](){
    server.send(200, "text/html", page);
    digitalWrite(ledR, LOW);
    delay(1000); 
  });
  server.begin();
}
 
void loop(void){
  server.handleClient();
}

