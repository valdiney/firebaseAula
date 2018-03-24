#include <ESP8266WiFi.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiType.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>

#include <Firebase.h>
#include <FirebaseArduino.h>
#include <FirebaseCloudMessaging.h>
#include <FirebaseError.h>
#include <FirebaseHttpClient.h>
#include <FirebaseObject.h>

#define FIREBASE_HOST "iotssa-28bc8.firebaseio.com"
#define FIREBASE_AUTH "AIzaSyB19kLxLsgrUtfFK48J74H1y982XCw0wm8"

const char* WIFI_SSID = "Ransomware-Infra";
const char* WIFI_PASSWORD = "*Xl0g1cm@st3r*";

int pin = 13;

void setup() {
  Serial.begin(9600);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  
  Serial.println();
  Serial.print("connected: ");

  pinMode(pin, OUTPUT);
  
  Firebase.begin(FIREBASE_HOST);
}

void loop() {
  //Firebase.setFloat("led/status", 3.0);
  if (Firebase.getFloat("led/status") == 1) {
       digitalWrite(pin, HIGH);
       Serial.println("LIGADO");
   } else {
      digitalWrite(pin, LOW);
      Serial.println("DESLIGADO");
   }
 
  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  } else {
      Serial.println("deu certo");
  }
}