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
#define xMin 0
#define xMax EsploraTFT.width() - 1
#define yMin 0
#define yMax EsploraTFT.height() - 1
#define low -100
#define high 100
#define sensitivity 20
#define pixels 1

int xPos = EsploraTFT.width() / 2;
int yPos = EsploraTFT.height() / 2;

void setup() {
  Serial.begin(serialBaudRate);
  EsploraTFT.begin();
  EsploraTFT.background(0, 0, 0);
}

void loop() {
  int xAxis = Esplora.readAccelerometer(X_AXIS);
  int yAxis = Esplora.readAccelerometer(Y_AXIS);
  setPosition(xAxis, yAxis);
  EsploraTFT.stroke(255, 255, 255);
  EsploraTFT.point(xPos, yPos);
  delay(100);
}

void setPosition(int xAxis, int yAxis){
  if (xAxis < sensitivity && xAxis > -sensitivity) {
    xPos = xPos;
  }
  else {
    xPos += map(xAxis, low, high, pixels, -pixels);
  }
  if (yAxis < sensitivity && yAxis > -sensitivity) {
    yPos = yPos;
  }
  else {
    yPos += map(yAxis, low, high, -pixels, pixels);
  }
}

