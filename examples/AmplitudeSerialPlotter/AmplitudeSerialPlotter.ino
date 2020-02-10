/*
 This example reads audio data from an Invensense's ICS43432 I2S microphone
 breakout board, and prints out the amplitude to the Serial console. The
 Serial Plotter built into the Arduino IDE can be used to plot the audio
 amplitude data (Tools -> Serial Plotter)

 Circuit:
 * Arduino/Genuino Zero, MKR family and Nano 33 IoT
 * ICS43432:
   * GND connected GND
   * 3.3V connected to 3.3V (Zero, Nano) or VCC (MKR)
   * WS connected to pin 0 (Zero) or 3 (MKR) or A2 (Nano)
   * CLK connected to pin 1 (Zero) or 2 (MKR) or A3 (Nano)
   * SD connected to pin 9 (Zero) or A6 (MKR) or 4 (Nano)

 created 23 November 2016
 by Sandeep Mistry
 */

#include <ArduinoSound.h>

// create an amplitude analyzer to be used with the I2S input
AmplitudeAnalyzer amplitudeAnalyzer;

void setup() {
  // Open serial communications and wait for port to open:
  // A baud rate of 115200 is used instead of 9600 for a faster data rate
  // on non-native USB ports
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

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

    // print out the amplititude to the serial monitor
    Serial.println(amplitude);
  }
}
