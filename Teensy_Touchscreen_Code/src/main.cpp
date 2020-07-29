#include <Arduino.h>

// Connections to the touchscreen
#define X_AXIS_RIGHT 15
#define X_AXIS_LEFT 17
#define Y_AXIS_TOP 16
#define Y_AXIS_BOTTOM 14

// Calibration values
#define CAL_BOTTOM 860
#define CAL_TOP 100
#define CAL_LEFT 90
#define CAL_RIGHT 950

// Mapping values
#define MAP_LEFT 0
#define MAP_RIGHT 100
#define MAP_TOP 0
#define MAP_BOTTOM 100

void setup() {
  Serial.begin(9600); // Usb is always 12 Mbit/s
  while(!Serial.available()) {;} // Wait for serial communication
}

void loop() {
  pinMode(X_AXIS_RIGHT, OUTPUT);
  pinMode(X_AXIS_LEFT, OUTPUT);
  pinMode(Y_AXIS_TOP, INPUT);
  pinMode(Y_AXIS_BOTTOM, INPUT);
  delay(10);
  digitalWriteFast(X_AXIS_RIGHT, HIGH);
  digitalWriteFast(X_AXIS_LEFT, LOW);
  delay(10);
  int x_axis = analogRead(Y_AXIS_TOP);

  pinMode(X_AXIS_RIGHT, INPUT);
  pinMode(X_AXIS_LEFT, INPUT);
  pinMode(Y_AXIS_TOP, OUTPUT);
  pinMode(Y_AXIS_BOTTOM, OUTPUT);
  delay(10);
  digitalWriteFast(Y_AXIS_BOTTOM, HIGH);
  digitalWriteFast(Y_AXIS_TOP, LOW);
  delay(10);
  int y_axis = analogRead(X_AXIS_LEFT);

  x_axis = map(x_axis, CAL_LEFT, CAL_RIGHT,  MAP_LEFT, MAP_RIGHT);
  y_axis = map(y_axis, CAL_TOP, CAL_BOTTOM,  MAP_TOP, MAP_BOTTOM);

  if (x_axis > MAP_RIGHT) {
    x_axis = MAP_RIGHT;
  }
  if (x_axis < MAP_LEFT) {
    x_axis = MAP_LEFT;
  }
  if (y_axis > MAP_BOTTOM) {
    y_axis = MAP_BOTTOM;
  }
  if (y_axis < MAP_TOP) {
    y_axis = MAP_TOP;
  }

  Serial.print("X: ");
  Serial.print(x_axis);
  Serial.print("\tY: ");
  Serial.println(y_axis);
}