/*
 This example reads audio data from an Invensense's ICS43432 I2S microphone
 breakout board, and uses the input to detect clapping sounds. An LED is
 togggled when a clapp is detected.

 Circuit:
 * Arduino/Genuino Zero, MKR family and Nano 33 IoT
 * ICS43432:
   * GND connected GND
   * 3.3V connected to 3.3V (Zero, Nano) or VCC (MKR)
   * WS connected to pin 0 (Zero) or 3 (MKR) or A2 (Nano)
   * CLK connected to pin 1 (Zero) or 2 (MKR) or A3 (Nano)
   * SD connected to pin 9 (Zero) or A6 (MKR) or 4 (Nano)

 created 18 November 2016
 by Sandeep Mistry
 */

#include <ArduinoSound.h>

// the LED pin to use as output
const int ledPin = LED_BUILTIN;

// the amplitude threshold for a clap to be detected
const int amplitudeDeltaThreshold = 100000000;

// create an amplitude analyzer to be used with the I2S input
AmplitudeAnalyzer amplitudeAnalyzer;

// variable to keep track of last amplitude
int lastAmplitude = 0;

void setup() {
  // setup the serial
  Serial.begin(9600);

  // configure the LED pin as an output
  pinMode(ledPin, OUTPUT);

  // setup the I2S audio input for 44.1 kHz with 32-bits per sample
  if (!AudioInI2S.begin(44100, 32)) {
    Serial.println("Failed to initialize I2S input!");
    while (1); // do nothing
  }

  // configure the I2S input as the input for the amplitude analyzer
  if (!amplitudeAnalyzer.input(AudioInI2S)) {
    Serial.println("Failed to set amplitude analyzer input!");
    while (1); // do nothing
  }
}

void loop() {
  // check if a new analysis is available
  if (amplitudeAnalyzer.available()) {
    // read the new amplitude
    int amplitude = amplitudeAnalyzer.read();

    // find the difference between the new amplitude and the last
    int delta = amplitude - lastAmplitude;
  
    // check if the difference is larger than the threshold
    if (delta > amplitudeDeltaThreshold) {
      // a clap was detected
      Serial.println("clap detected");
  
      // toggle the LED
      digitalWrite(ledPin, !digitalRead(ledPin));
  
      // delay a bit to debounce
      delay(100);
    }
  
    // update the last amplitude with the new amplitude
    lastAmplitude = amplitude;
  }
}
