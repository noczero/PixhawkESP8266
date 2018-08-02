/*### Wifi Commands for HERO4 
 * Cameras covered: GoPro HERO4 Black, Silver (Firmware HD4.02.05.00.00 Oct 2016) and Session (Firmware April 2016)
 * taking photo over wireless using pixhawk
 * -- Wiring --
 * PIN 5 AUX Pixhwak -- PIN 13 Wemos D7
 * -- Pixhawk Setting --
 * on MP : set gimbal to relay
 *          set cam_relay to LOW
 *          set cam_trig to type 1
 *          set CH7 to camera shutter
 */
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define inputPIN 13 //D7
const char* ssid = "DroneTeam";
const char* pwd = "droneteam123";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);

  WiFi.begin(ssid, pwd); // start the wifi

  // waiting for connection established
  while (WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.println("Waiting for connection..");
  }

  // define interrupt
  pinMode(inputPIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(inputPIN), trigger, RISING);
}

// Shutter Trigger: http://10.5.5.9/gp/gpControl/command/shutter?p=1
String shutterAPI = "http://10.5.5.9/gp/gpControl/command/shutter?p=1";
void sendHTTRequest(){
   if (WiFi.status() == WL_CONNECTED){
    HTTPClient http;
    
    http.begin(shutterAPI);
    http.GET();
    http.end();
    //Serial.println("Take photo");
  } 
}

int stats;
void loop() {
  // put your main code here, to run repeatedly:
  //sendHTTRequest();

  stats = digitalRead(inputPIN);
  Serial.println(stats);
  
  if (stats == 0){
    sendHTTRequest();
  }
  delay(1000);
}

void trigger(){
  Serial.println("Trigger Go Pro");
  //sendHTTRequest();
}

