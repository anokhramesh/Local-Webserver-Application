//In this Project we will control 4 Relays connected to GPIO Pins D1,D2,D3 and D4 of esp8266 via local webbrowser .
// Go to tools -Boards: select the NodeMCU 1.0(esp-12E MODULE)
//Upload the sketch to ESP8266
// After Done uploading-Open Serial monitor and set baud rate 115200
// Press the boot button on the ESP8266 board 
 // Copy the IP address and past it on web browser or type the IP address on your mobile webpage -192.168.0.113
const int relayCount = 4; //total number of relays
int relayPin[relayCount] = {D1, D2, D3, D4}; //connect relays to GPIO PIns D1,D2,D3 and D4
int relayState[relayCount] = {1, 1, 1, 1}; //initial state . 1 OFF, 0 ON
String buttonTitle1[relayCount] = {"DEVICE 1 ON", "DEVICE 2 ON", "DEVICE 3 ON", "DEVICE 4 ON"};
String buttonTitle2[relayCount] = {"DEVICE 1 OFF", "DEVICE 2 OFF", "DEVICE 3 OFF", "DEVICE 4 OFF"};
String argId[relayCount] = {"r1", "r2", "r3", "r4"};
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#ifndef STASSID
#define STASSID "dewa406"// enter the wifi name(SSID)
#define STAPSK  "Ramesh16384"//enter the password
#endif
const char *ssid = STASSID;
const char *password = STAPSK;
ESP8266WebServer server(80);
void handleRoot() {
  String HTML = "<!DOCTYPE html>\
  <html>\
  <head>\
  \t\n<title>AnokhautomationESP8266 Relay Control</title>\
  \t\n<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\
  \n<style>\
 \nhtml,body{\t\nwidth:100%\;\nheight:100%\;\nmargin:0}\n*{box-sizing:border-box}\n.colorAll{\n\tbackground-color:#90ee90}\n.colorBtn{\n\tbackground-color:#add8e6}\n.angleButtdon,a{\n\tfont-size:30px\;\nborder:1px solid #ccc\;\ndisplay:table-caption\;\npadding:7px 10px\;\ntext-decoration:none\;\ncursor:pointer\;\npadding:5px 6px 7px 10px}a{\n\tdisplay:block}\n.btn{\n\tmargin:5px\;\nborder:none\;\ndisplay:inline-block\;\nvertical-align:middle\;\ntext-align:center\;\nwhite-space:nowrap}\n";

  HTML += "</style>\n\n</head>\n\n<body>\n<h1>ANOKHAUTOMATION</h1>\n";

  for (int i = 0; i < relayCount; i++) {
    if (relayState[i]) {
      HTML += "\t<div class=\"btn\">\n\t\t<a class=\"angleButton\" style=\"background-color:#90ee90\"  href=\"/relay?";
      HTML += argId[i];
      HTML += "=on\">";
      HTML += buttonTitle1[i]; //Light ON title
    } else {
      HTML += "\t<div class=\"btn\">\n\t\t<a class=\"angleButton \" style=\"background-color:#f56464\"  href=\"/relay?";
      HTML += argId[i];
      HTML += "=off\">";
      HTML += buttonTitle2[i]; //Light OFF title
    }
    HTML += "</a>\t\n\t</div>\n\n";
  }
  HTML += "\t\n</body>\n</html>\n";
  server.send(200, "text/html", HTML);
}//handleRoot()

void handleNotFound() {
 
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }

  server.send(404, "text/plain", message);
 
}//end of handleNotFound()

void setup(void) {
 

  for (int i = 0; i < relayCount; i++) {
    pinMode(relayPin[i], OUTPUT);// define a pin as output for relay
    digitalWrite(relayPin[i], relayState[i]);//initial state either ON or OFF
  }

  Serial.begin(115200);//initialize the serial monitor
  Serial.println("Anokhautomation-ESP8266 Relay Control");

  

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: http://");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("ESP8266")) {
    Serial.println("MDNS responder started");
    Serial.println("access via http://ESP8266");
  }

  server.on("/", handleRoot);
  server.on("/relay", HTTP_GET, relayControl);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");

}//end of setup

void loop(void) {
  
  server.handleClient();
  MDNS.update();

  for (int i = 0; i < relayCount; i++) {
    if (relayState[i] == 1)
    {
      digitalWrite(relayPin[i], HIGH);
    } else {
      digitalWrite(relayPin[i], LOW);
    }
    //printRelayState(i);//prints for debugging purpose. Slows respons of WebServer.
  }


  delay(100);

}
void relayControl() {

  for (int i = 0; i < relayCount; i++) {
    if (server.arg(argId[i]) == "on")
    {
      relayState[i] = 0;// set state of relay to ON
    } else if (server.arg(argId[i]) == "off") {
      relayState[i] = 1;  // set state of relay to OFF
    }
  }
  handleRoot();
}
void printRelayState(int id)
{
  Serial.print("Relay ");
  Serial.print(id);
  Serial.print(" at GPIO ");
  Serial.print(relayPin[id]);
  Serial.print(" : ");
  Serial.println (relayState[id]);
  delay(500);
}
