// Minor Everything Web
// Course: Web of things
// Author: Fons Hettema
// Assignment: AVV1 - Sound

// Include
#include <EIoTCloudRestApi.h>
#include <EIoTCloudRestApiConfig.h>
#include <ThingSpeak.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>

// Define client
const char* ssid = "MR";
const char* password = "159753!!";
WiFiClient client;

// EIoTCloud API
EIoTCloudRestApi eiotcloud;
#define SOUND_ID "5706c2bbc943a0661cf314e0/QXKZUI5ZnS1mkrFp"

// ThingSpeak API
const int CHANNEL_ID = 106749;
const char * API_KEY = "VQ2V162PRR4G0Y9Z";

// Pins
const int pinSound = D0;     // define D0 sound interface
int sound = 0;               // variable to store the value coming from the sound sensor
int pinSoundState = LOW;     // variable state to check sound

// Setup
void setup ()
{
  Serial.begin(9600);         // open the serial port at 9600 bps
  pinMode(pinSound, INPUT);   // define sound as input
  eiotcloud.begin();          // start eiotcloud
  ThingSpeak.begin(client);   // start client for ThingSpeak
}

// Loop
void loop ()
{ 
  // Delay
  delay(1000);

  // -- Microphone sound sensor -- \\
  
  sound = digitalRead(pinSound); // read status of sound
  
  if(sound == HIGH) { // check if sound is detected
    if(pinSoundState == LOW) { // check sound state
      Serial.println("Sound detected");
      eiotcloud.sendParameter(SOUND_ID, sound);
      ThingSpeak.writeField(CHANNEL_ID, 2, sound, API_KEY);
      pinSoundState = HIGH;  // switch sound state on
    }
  } else {
    if(pinSoundState == HIGH) { // check if sound is detected
      Serial.println("Silence"); // check sound state
      eiotcloud.sendParameter(SOUND_ID, sound);
      ThingSpeak.writeField(CHANNEL_ID, 2, sound, API_KEY);
      pinSoundState = LOW; // switch sound state off
    }
  }
}
