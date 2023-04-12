int LDR_In =A0; //de spanningsdeler wordt aangesloten op A0
int lichtHoeveelheid;

#include "DHT.h"
#define DHTTYPE DHT11       // DHT 11 sensor
uint8_t DHTPin = D7;        // DHT Sensor data input
DHT dht(DHTPin, DHTTYPE);   // Initialize DHT sensor.  

#include <ArduinoJson.h>
const int capacity = JSON_OBJECT_SIZE(7);
StaticJsonDocument<capacity> doc;
 
//      web server
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
ESP8266WebServer server(35829); // maak een instantie van de webserver op poort 80

const char* ssid = "MediaLab";
const char* password = "Mediacollege";

void readDHT11() {
  if(isnan(lichtHoeveelheid)){
    Serial.println("DHT11 sensor error");
  }
  else{
    lichtHoeveelheid = analogRead(LDR_In);
    Serial.print(" Licht: ");
    Serial.print(lichtHoeveelheid);
    Serial.println(" cd ");
  }
}

void wifiConnect(){
  WiFi.begin(ssid, password); // connect to wifi ssid with password 
  while (WiFi.status() != WL_CONNECTED) {
      delay(1000); // wait 1 sec
      Serial.print("Connecting..");
      }
  //if connected
  Serial.print("\r\nConnected: SSID: "); 
  Serial.print(ssid);
  Serial.print("    IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
  Serial.println("HTTP server started");
 }

 void handleRoot() {
   server.send(200, "text/html", "<h3>Duurzaam Huis DHT11 sensor. " 
   + 
   "</h3><form action=\"/sensor\" method=\"GET\"><input type=\"submit\" value=\"Sensor Read\"></form>" );
   }

void handleNotFound(){
  String message = "I'm sorry, I don't know what to do\n\n";
  server.send(404, "text/plain", message);
}

void handleSensor(){
  server.send(200, "text/html", "<h3>Duurzaam Huis: " 
   "</h3>Lichthoeveelheid: " +String(lichtHoeveelheid) + " Candela (cd)");
  }

void gegevens(){
  doc["licht"] = lichthoeveelheid;
  char jsonOut[128];
  serializeJson(doc, jsonOut);
  server.send(200, "application/json", jsonOut);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  server.enableCORS(true);
  server.onNotFound(handleNotFound);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (WiFi.status() != WL_CONNECTED) wifiConnect();// reconnect Wifi if necessary 
  server.handleClient();
  delay(3000);    //Send a request every XXX ms  DHT11 needs at least 2 seconds
  readDHT11();
}
