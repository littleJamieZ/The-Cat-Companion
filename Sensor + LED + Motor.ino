//LED
#include <Arduino.h>
#include <Ultrasonic.h>
#include <FastLED.h>
#define NUM_LEDS 60
#define DATA_PIN 6
//Pin 3 and 4 for distance sensor
Ultrasonic ultrasonic1(3, 3);
//Define numbe of LEDs
CRGB leds[NUM_LEDS];
//Variable used for LED
int Pot = A0;
int PotVal = 0;
int OutVal = 0;
//Variable used for Motor Speed
int Speed = 100;
// variable used for motor activation
int motorCode = -1;
// the transistor which controls the motor will be attached to digital pin 9
int motorControl = 9;
void setup() {
  Serial.begin(9600);  // initialise the serial communication
  // make the transistor's pin an output:
  pinMode(motorControl, OUTPUT);
  // state the LED information
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
}
void loop() {
  // wait for a message to arrive
  if (Serial.available()) {
    // save the message when it arrives
    motorCode = Serial.read();
  }
  PotVal = analogRead(Pot);
  //OutVal = map(PotVal, 0, 1023, 0, 255);
  if (ultrasonic1.read() <= 25) {
    fill_solid(leds, NUM_LEDS, CRGB::Blue);
    analogWrite(NUM_LEDS, OutVal);
    //FastLED.setBrightness(OutVal);
    FastLED.show();
    delay(1000);
    Speed = 150;
  } else {
    FastLED.clear();
    FastLED.show();
    Speed = 100;
  }
  switch (motorCode) {
    case 1:
      // on
      analogWrite(motorControl, Speed);
      break;
    case 2:
      // off
      analogWrite(motorControl, 0);
      break;
    case 3:
      // else
      analogWrite(motorControl, Speed);
      break;
    default:
      // default
      break;
      delay(1);  // delay in between reads for stability
  }
}