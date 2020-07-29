#include <Arduino.h>

// Connections to the touchscreen
#define X_AXIS_RIGHT 14
#define X_AXIS_LEFT 16
#define Y_AXIS_TOP 15
#define Y_AXIS_BOTTOM 17

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

  Serial.print("X: ");
  Serial.print(x_axis);
  Serial.print("\tY: ");
  Serial.println(y_axis);
}