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
#define oneButtonPressed 3

int xPos = EsploraTFT.width() / 2;
int yPos = EsploraTFT.height() / 2;
int oldXPos = xPos;
int oldYPos = yPos;
boolean draw = false;

void setup() {
  Serial.begin(serialBaudRate);
  EsploraTFT.begin();
  EsploraTFT.background(0, 0, 0);
}

void loop() {
  draw = false;
  int xAxis = Esplora.readAccelerometer(X_AXIS);
  int yAxis = Esplora.readAccelerometer(Y_AXIS);
  setPosition(xAxis, yAxis);
  checkPosition();
  drawPoint();
  delay(100);
}

void drawPoint() {
  EsploraTFT.stroke(255, 255, 255); // white
  EsploraTFT.point(xPos, yPos);
  int upButtonState = Esplora.readButton(SWITCH_UP);
  int downButtonState = Esplora.readButton(SWITCH_DOWN);
  int leftButtonState = Esplora.readButton(SWITCH_LEFT);
  int rightButtonState = Esplora.readButton(SWITCH_RIGHT);
  int buttonStateSum = upButtonState + downButtonState + leftButtonState + rightButtonState;
  if (buttonStateSum == oneButtonPressed) {
    draw = true;
  }
  if (oldXPos != xPos || oldYPos != yPos) {
    if (draw) {
      if (upButtonState == LOW) {
        EsploraTFT.stroke(0, 255, 255); // yellow
      }
      else if (downButtonState == LOW) {
        EsploraTFT.stroke(0, 255, 0); // green
      }
      else if (leftButtonState == LOW) {
        EsploraTFT.stroke(255, 0, 0); // blue
      }
      else if (rightButtonState == LOW) {
        EsploraTFT.stroke(0, 0, 255); // red
      }
    }
    else {
      EsploraTFT.stroke(0, 0, 0);
    }
    EsploraTFT.point(oldXPos, oldYPos);
  }
  oldXPos = xPos;
  oldYPos = yPos;
}

void setPosition(int xAxis, int yAxis) {
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

void checkPosition() {
  if (xPos < xMin) {
    (xPos = xMin);
  }
  if (xPos > xMax) {
    (xPos = xMax);
  }
  if (yPos < yMin) {
    (yPos = yMin);
  }
  if (yPos > yMax) {
    (yPos = yMax);
  }
}
