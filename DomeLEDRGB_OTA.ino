#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "your firebase host"
#define FIREBASE_AUTH "your firebase auth"
#define red  0
#define green  2
#define blue  3
int t = 10; // Time for delay


const char* ssid = "your ssid";
const char* password = "your wifi password";

void setup()
{
    pinMode(red, OUTPUT);
    pinMode(green, OUTPUT);
    pinMode(blue, OUTPUT);
  digitalWrite(red,LOW);
  digitalWrite(blue, LOW);
  digitalWrite(green, LOW);
  ArduinoOTA.setHostname("ESP-DOMELED"); // name for OTA in arduinoIDE
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
  Serial.println("Connection Failed! Rebooting...");
  delay(5000);
  ESP.restart();
  }
  ArduinoOTA.begin();
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop()
{
  ArduinoOTA.handle();
  boolean Fadebool = Firebase.getBool("DomeLED/Fade");
  boolean R = Firebase.getBool("DomeLED/R");
  boolean G = Firebase.getBool("DomeLED/G");
  boolean B = Firebase.getBool("DomeLED/B");
  int Lux = Firebase.getInt("DomeLED/Lux");
  if(Fadebool == 0 && R == 0 && G == 0 && B == 0){
    analogWrite(red, 0);
    analogWrite(blue, 0);
    analogWrite(green, 0);
  }
  else{
    if(Fadebool == 1){
    Fade();
  }
  else{
    if(R == 1){
      analogWrite(red, 2.5*Lux);
      analogWrite(blue, 0);
      analogWrite(green, 0);
    }
    if(G == 1){
      analogWrite(red,0);
      analogWrite(blue, 0);
      analogWrite(green, 2.5*Lux);
    }
    if(B == 1){
      analogWrite(red,0);
      analogWrite(blue, 2.5*Lux);
      analogWrite(green, 0);
    }
  }
  }
}



void Fade(){
  for( int i = 0; i <= 255; i++){
    analogWrite(red, i); // fade up 
    analogWrite(green, 255 - i); // fade down
    analogWrite(blue, 0); // do nothing
    delay(t);
  }
  for( int i = 0; i <= 255; i++){
    analogWrite(red, 255 - i); // fade down
    analogWrite(green, 0); // do nothing
    analogWrite(blue, i); // fade up 
    delay(t);
  }
    for( int i = 0; i <= 255; i++){
    analogWrite(red, 0); // do nothing
    analogWrite(green, i); // fade up
    analogWrite(blue, 255 - i); // fade down 
    delay(t);
  }
} 
