// JSON POST requests: https://randomnerdtutorials.com/esp8266-nodemcu-http-get-post-arduino/#http-post
// HTTPS requests: https://randomnerdtutorials.com/esp8266-nodemcu-https-requests/
// WiFi
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>

// JSON
#include <ArduinoJson.h>

//        initialise temperature humidity sensor DHT11
#include "DHT.h"
#define DHTTYPE DHT11       // DHT 11 sensor
uint8_t DHTPin = D7;        // DHT Sensor data input
DHT dht(DHTPin, DHTTYPE);   // Initialize DHT sensor.    
float Temperature;          // temperature

int LDR_In =A0; //de spanningsdeler wordt aangesloten op A0
int lichtHoeveelheid;


// WiFi
const char* ssid = "A";
const char* password = "873Sheep";

// POST
String serverProtocol = "https://";
String serverIP = "35829.hosts2.ma-cloud.nl/"; // Ma cloud url or localhost IP
String serverDirectory = "IoT/post.php"; // path naar directory, bijvoorbeeld: "duurzaamhuis/post.php" 
String URL = ""; // URL om data naar te versturen, wordt automatisch aangemaakt.
const uint8_t fingerprint[20] = {0x1A, 0x48, 0xE9, 0x83, 0x9D, 0x49, 0x82, 0x92, 0xB1, 0xEC, 0x18, 0xCE, 0xBF, 0x5F, 0xFA, 0x54, 0xD8, 0x93, 0xFD, 0xA5}; // fingerprint van jou server

// JSON
const int capacity = JSON_OBJECT_SIZE(2);
StaticJsonDocument<capacity> doc;
char jsonOut[250];

// JSON testing

void readDHT11(){
  /* 
   *  read the sensor
   *  sampling rate DHT11 is max. 1Hz 
   *  the DHT11 is known for erroneous readings
   */
    float temperature =  round(dht.readTemperature()*10)/10; // Gets the values of the temperature

        
    if(isnan(temperature)){
        // sensor error
        Serial.println("DHT11 sensor error");
    }
    else{
        // the DHT11 readings look ok 
        Temperature = temperature;
        lichtHoeveelheid = analogRead(LDR_In);

        // show in Serial Monitor
        Serial.print("Temp. ");
        Serial.print(Temperature);

        Serial.print(" Licht: ");
        Serial.print(lichtHoeveelheid);
        Serial.println(" cd ");
      }
 }

void wifiConnect(){
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print("Connecting...");
  }
  Serial.print("\r\nConnected: SSID: "); 
  Serial.print(ssid);
  Serial.print("    IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("HTTP server started");
  Serial.println("\nSending POST data to: " + URL + "\n");
}

void CreateJSON() {
  doc["licht"] = lichtHoeveelheid;
  doc["temp"] = Temperature;
  serializeJson(doc, jsonOut);
}

void SendPOST() {
  //WiFiClient client;
  WiFiClientSecure client;
  client.setFingerprint(fingerprint);
  HTTPClient https;
  
  if( https.begin(client, URL) ){
    https.addHeader("Content-Type", "application/json");
    int responseCode = https.POST(jsonOut);
    String responseMsg = https.getString();
    Serial.print("[HTTPS] POST code: ");
    Serial.print(responseCode);
    Serial.print("\n[HTTPS] Response: ");
    Serial.println(responseMsg);
    https.end();  
  } else Serial.println("POST is not working, check the steps in the powerpoint again.");
}

void setup() {
  Serial.begin(115200);     

  // Maak de POST url op basis van protocol, serverIP & directory
  if(serverProtocol.length() > 0) URL += serverProtocol;
  URL += serverIP;
  if(serverDirectory.length() > 0) URL += "/" + serverDirectory;
}

void loop() {
  if(WiFi.status() != WL_CONNECTED) wifiConnect();
  delay(3000);    //Send a request every XXX ms  DHT11 needs at least 2 seconds
  readDHT11();
  CreateJSON();
  SendPOST();
  delay(7500);
 
}
