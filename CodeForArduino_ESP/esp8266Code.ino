
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char *ssid = "ESP8266SoftAP";
const char *password = "";

ESP8266WebServer server(80);

void handleServ() {
  Serial.print(server.arg(0));

  //while(!Serial.available()){}
  //String aString=Serial.readString();
  //server.send(200, "text/html", server.arg(0));
}


void setup() {
  Serial.begin(115200);
  WiFi.softAP(ssid);
  server.on("/", handleServ);
  server.begin();
}

void loop() {
  server.handleClient();
}
