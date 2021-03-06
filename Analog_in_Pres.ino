#include <AdafruitIO.h>
#include <AdafruitIO_Dashboard.h>
#include <AdafruitIO_Data.h>
#include <AdafruitIO_Definitions.h>
#include <AdafruitIO_Feed.h>
#include <AdafruitIO_Group.h>
#include <AdafruitIO_MQTT.h>
#include <AdafruitIO_WiFi.h>


// Adafruit IO Analog In Example
// Tutorial Link: https://learn.adafruit.com/adafruit-io-basics-analog-input
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

/************************** Configuration ***********************************/

// edit the config.h tab and enter your Adafruit IO credentials
// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.
#define IO_USERNAME    "your io-username"
#define IO_KEY         "key"

/******************************* WIFI **************************************/

// the AdafruitIO_WiFi client will work with the following boards:
//   - HUZZAH ESP8266 Breakout -> https://www.adafruit.com/products/2471
//   - Feather HUZZAH ESP8266 -> https://www.adafruit.com/products/2821
//   - Feather M0 WiFi -> https://www.adafruit.com/products/3010
//   - Feather WICED -> https://www.adafruit.com/products/3056

#define WIFI_SSID       "wifi_ssid"
#define WIFI_PASS       "password"

// comment out the following two lines if you are using fona or ethernet
#include "AdafruitIO_WiFi.h"
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);


/************************ Example Starts Here *******************************/

// analog pin A
#define PHOTOCELL_PIN A1
#define T A2
#define P A4

// photocell state
int current = 0;
int last = -1;

// set up the 'analog' feed
AdafruitIO_Feed *analog = io.feed("feather_mo_test2");

AdafruitIO_Feed *Tem = io.feed("feather_mo_test1");

AdafruitIO_Feed *Pres = io.feed("feather_mo_test3");

void setup() {

  // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
  while(! Serial);

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

}

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();

  // grab the current state of the pin A1
  current = analogRead(A1);


  // save the current state to the analog feed
  Serial.print("sending -> analog");
  Serial.println(current);
  analog->save(current);

  // store last state
  last = current;

  // grab the current state of the pin A2
  current = analogRead(A2);


  // save the current state to the analog feed
  Serial.print("sending -> Tem");
  Serial.println(current);
  Tem->save(current);

  // store last state
  last = current;

   // grab the current state of the pin A3
  current = analogRead(A4);


  // save the current state to the analog feed
  Serial.print("sending -> Pres");
  Serial.println(current);
  Pres->save(current);

  // store last state
  last = current;

  // wait one second (1000 milliseconds == 1 second)
  delay(30000);
}
