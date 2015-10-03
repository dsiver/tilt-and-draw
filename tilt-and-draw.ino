/*
 * Tilt and Draw
 * Board: Arduino Esplora
 *
 * David Siver
 * CS 4985
 * Fall 2015
 */

#include <Esplora.h>
#include <SPI.h>
#include <TFT.h>

#define DEBUG 0
#define serialBaudRate 9600

int xPos = EsploraTFT.width()/2;
int yPos = EsploraTFT.height()/2;

void setup() {
  Serial.begin(serialBaudRate);
  EsploraTFT.begin();
  EsploraTFT.background(0, 0, 0);
}

void loop() {
  int xAxis = Esplora.readAccelerometer(X_AXIS);
  int yAxis = Esplora.readAccelerometer(Y_AXIS);
}
