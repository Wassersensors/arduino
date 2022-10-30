
/*
  Example of reading values from a Bolsen Hall Effect water flow sensor
  and printing the values to a Grove-LCD RGB Backlight V4.0
  using an Arduino Uno Wifi.
  
  This example code is in the public domain.
*/

#include <Wire.h>
#include <WiFiNINA.h>
#include "rgb_lcd.h"
#include <TimeLib.h>     

rgb_lcd lcd;

const int colorR = 255;
const int colorG = 0;
const int colorB = 0;

volatile int flow_frequency; // Measures flow sensor pulses
// Calculated litres/hour
float vol = 0.0,l_minute;
unsigned char flowsensor = 2; // Sensor Input Pin
unsigned long currentTime;
unsigned long cloopTime;

char ssid[] = "";    //  your network SSID (name)
char pass[] = "";   // your network password

char SERVER_ADDRESS[] = ""; // hostname of web server
const int PORT = 80; // port of the server

int status = WL_IDLE_STATUS;

// Initialize the client library
WiFiClient client;

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(flowsensor, INPUT);
  digitalWrite(flowsensor, HIGH); 
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.setRGB(colorR, colorG, colorB);
  lcd.clear();
  lcd.setCursor(0,0);

  attachInterrupt(digitalPinToInterrupt(flowsensor), flow, RISING); // Setup Interrupt

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  lcd.print("SSID: " + String(ssid));

  status = WiFi.begin(ssid, pass);
  if ( status != WL_CONNECTED) {
    lcd.clear();
    lcd.print("Couldn't get a wifi connection");
    // don't do anything else:
    while(true);
  }
  lcd.clear();
  lcd.print("Connected!");
  Serial.println("Connected to wifi");

  currentTime = millis();
  cloopTime = currentTime;
}

// the loop function runs over and over again forever
void loop() {
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  if (!client.connected()) {
    client.stop();
  }
  
  currentTime = millis();
  // Every second, calculate and print litres/hour
  if(currentTime >= (cloopTime + 1000)) {
    cloopTime = currentTime; // Updates cloopTime
    if(flow_frequency != 0){
      // Pulse frequency (Hz) = 7.5Q, Q is flow rate in L/min.
      l_minute = (flow_frequency / 7.5); // (Pulse frequency x 60 min) / 7.5Q = flowrate in L/hour
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Rate: " + String(l_minute) + " L/M");
      l_minute = l_minute/60;
      lcd.setCursor(0,1);
      vol = vol +l_minute;
      makePostRequest("/record", "{\"rate\":" + String(l_minute) + ",\"vol\":" + String(vol) + ",\"timestamp\":" + String(now()) + "}");
      lcd.print("Vol: " + String(vol) + " L");
      flow_frequency = 0; // Reset Counter
      Serial.print(l_minute, DEC); // Print litres/hour
      Serial.println(" L/Sec");
   } else {
      makePostRequest("/record", "{\"rate\": 0,\"vol\":" + String(vol) + ",\"timestamp\":" + String(now()) + "}");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Rate: " + String(flow_frequency) + " L/M");
      lcd.setCursor(0,1);
      lcd.print("Vol: " + String(vol) + " L");
    }
  }
}

// Interrupt function
void flow () {
 flow_frequency++;
}
