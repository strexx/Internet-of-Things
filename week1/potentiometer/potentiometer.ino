// Minor Everything Web
// Course: Web of things
// Author: Fons Hettema
// Assignment: AVV1 - Potentiometer

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
#define POT_ID "5706c2bbc943a0661cf314e0/oYo42iPBJsjMot6r"

// ThingSpeak API
const int CHANNEL_ID = 106749;  // ThingSpeak CHANNEL_ID
const char * API_KEY = "VQ2V162PRR4G0Y9Z"; // ThingSpeak Write API key

// Pins
const int pinPot = A0;        // define A0 potentiometer interface
int resistenceAmount = 0;     // variable to store the value coming from the potentiometer sensor

// Setup
void setup ()
{
  Serial.begin(9600);         // open the serial port at 9600 bps
  eiotcloud.begin();          // start eiotcloud
  ThingSpeak.begin(client);   // start client for ThingSpeak
}

// Loop
void loop ()
{ 
  // Delay
  delay(1000);
  
  // -- Potentiometer sensor -- \\
  
  resistenceAmount = analogRead(pinPot); // read the amount of resistance from the sensor
  eiotcloud.sendParameter(POT_ID, resistenceAmount); // send data to EIoTcloud
  ThingSpeak.writeField(CHANNEL_ID, 1, resistenceAmount, API_KEY); // send data to ThingSpeak
  String stringOne = "Potentio value: ";
  String stringTwo = stringOne + resistenceAmount;
  Serial.println(stringTwo); // Print value
  delay(resistenceAmount);
}
