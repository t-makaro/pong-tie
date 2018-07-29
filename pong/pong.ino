/*
 * File name: TinkerTie.ino
 * Author: Tyler Makaro
 */
#include <Adafruit_NeoPixel.h>
#include <CapacitiveSensor.h>
#include "animations.h"

#define buttonPin 12
#define buttonPowerPin 13
#define groundPin 10
#define seedPin A2

Adafruit_NeoPixel bowtie = Adafruit_NeoPixel(28, 4, NEO_GRB + NEO_KHZ800);
CapacitiveSensor capSensor = CapacitiveSensor(3, 1);

void setup() {
  bowtie.begin();
  bowtie.setBrightness(5);
  bowtie.show(); // Initialize all pixels to 'off'
  
  //For the extra button
  pinMode(buttonPin, INPUT);
  pinMode(buttonPowerPin, OUTPUT);
  pinMode(groundPin, OUTPUT);
  digitalWrite(buttonPowerPin, HIGH);
  digitalWrite(groundPin, LOW);
  
  randomSeed(analogRead(seedPin));
}

void loop(){
    bowtie.show();
}

bool capButton() {
  //static long state_prev = capSensor.capacitiveSensor(30);
  long state_curr = capSensor.capacitiveSensor(30);
  return (state_curr >= 50)
}

bool physButton(){
  //static int state_prev = digitalRead(buttonPin);
  int state_curr = digitalRead(buttonPin);
  return (state_curr == HIGH)
}
