// Adafruit IO IFTTT Door Detector
// 
// Learn Guide: https://learn.adafruit.com/using-ifttt-with-adafruit-io
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2018 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

/************************** Configuration ***********************************/

// edit the config.h tab and enter your Adafruit IO credentials
// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.
#include "config.h"
#include <EEPROM.h>
/************************ Example Starts Here *******************************/
bool triggered = false; //Keeps track of PIR state
bool last = false;

// gate gpio pin
#define GATE 5
//white led GPIO pin
#define WHITELED 4
//flashing red led GPIO pin
#define REDLED 14

// how often to report battery level to adafruit IO (in minutes)
//#define BATTERY_INTERVAL 5

// how long to sleep between checking the door state (in seconds)
//#define SLEEP_LENGTH 3

// set up the 'gate' feed
AdafruitIO_Feed *digital = io.feed("Gate");

void setup() {

  // start the serial connection
  Serial.begin(115200);

  while (!Serial);
  Serial.println("Intelligent Dummy Cam");

  
  pinMode(GATE,INPUT);
  pinMode(WHITELED,OUTPUT);
  pinMode(REDLED,OUTPUT);

  //turn off the leds
  digitalWrite(WHITELED,LOW);
  digitalWrite(REDLED,LOW);

// connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());


  
  delay(15000); //wait for PIR sensor to stabilize


}


void loop(){

// io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();


   // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 3.2V):
  float voltage = sensorValue * (3.2 / 1023.0);
  // print out the value you read:
  //Serial.println(voltage);
  
  if(digitalRead(GATE) == HIGH && triggered == false){ //If motion is detected at the door and this is the first time the PIR has been triggered...
    triggered = true;
    //Serial.println("ALARM");
    if(voltage<2){  //if its dark outside then do the LED sequence
      for (int i = 0; i <= 30; i++) { //flash the white LEDs
        digitalWrite(WHITELED,HIGH);
        delay(40);
        digitalWrite(WHITELED,LOW);
        delay(20);
      }
      digitalWrite(WHITELED, HIGH);
      delay(1000);
      digitalWrite(WHITELED,LOW);
      digitalWrite(REDLED,HIGH); //turn on flashing red led
      }
    Serial.print("sending button -> ");
    Serial.println(triggered);
    digital->save(triggered); //send the date to AdafruitIO !
  }
  else if (digitalRead(GATE) == LOW){ //when the PIR signal goes low again...
    digitalWrite(REDLED,LOW); //turn off the flashing red led
    triggered = false;
  }
  
}

