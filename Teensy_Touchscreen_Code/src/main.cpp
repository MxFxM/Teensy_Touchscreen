#include <Arduino.h>

#define TOUCH_DEVICE 2

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
#define MAP_RIGHT 1000
#define MAP_TOP 0
#define MAP_BOTTOM 1000

// Zero values
int x_zero;
int y_zero;
int clicktime;
boolean clicked;

// Variable for transferring x and y coordinates
int coordinates[2];

// Functions
void fun_readPositions(void);
void fun_mapValues(void);
void fun_moveMouse(void);
void fun_clickMouse(void);
void fun_touchpadLoop(void);

void setup() {
//  Serial.begin(9600); // Usb is always 12 Mbit/s
//  while(!Serial.available()) {;} // Wait for serial communication
  for (int i = 0; i < 10; i++) {
    fun_readPositions();
  }

  fun_mapValues();

  x_zero = coordinates[0];
  y_zero = coordinates[1];

  Mouse.screenSize(MAP_RIGHT, MAP_BOTTOM);
}

void loop() {
  fun_touchpadLoop();
}

void fun_readPositions(void) {
  pinMode(X_AXIS_RIGHT, OUTPUT);
  pinMode(X_AXIS_LEFT, OUTPUT);
  pinMode(Y_AXIS_TOP, INPUT);
  pinMode(Y_AXIS_BOTTOM, INPUT);
  delay(10);
  digitalWriteFast(X_AXIS_RIGHT, HIGH);
  digitalWriteFast(X_AXIS_LEFT, LOW);
  delay(10);
  coordinates[0] = analogRead(Y_AXIS_TOP);

  pinMode(X_AXIS_RIGHT, INPUT);
  pinMode(X_AXIS_LEFT, INPUT);
  pinMode(Y_AXIS_TOP, OUTPUT);
  pinMode(Y_AXIS_BOTTOM, OUTPUT);
  delay(10);
  digitalWriteFast(Y_AXIS_BOTTOM, HIGH);
  digitalWriteFast(Y_AXIS_TOP, LOW);
  delay(10);
  coordinates[1] = analogRead(X_AXIS_LEFT);
}

void fun_mapValues(void) {
  // map values
  coordinates[0] = map(coordinates[0], CAL_LEFT, CAL_RIGHT,  MAP_LEFT, MAP_RIGHT);
  coordinates[1] = map(coordinates[1], CAL_TOP, CAL_BOTTOM,  MAP_TOP, MAP_BOTTOM);

  // limit values
  if (coordinates[0] > MAP_RIGHT) {
    coordinates[0] = MAP_RIGHT;
  }
  if (coordinates[0] < MAP_LEFT) {
    coordinates[0] = MAP_LEFT;
  }
  if (coordinates[1] > MAP_BOTTOM) {
    coordinates[1] = MAP_BOTTOM;
  }
  if (coordinates[1] < MAP_TOP) {
    coordinates[1] = MAP_TOP;
  }
}

void fun_moveMouse(void) {
  // move mouse to that position
  Mouse.moveTo(coordinates[0], coordinates[1]);
}

void fun_clickMouse(void) {
  if (abs(coordinates[0] - x_zero) > 5 && abs(coordinates[1] - y_zero) > 5) {
    fun_moveMouse();
    Mouse.press();
    clicked = true;
  } else {
    if (clicked) {
      Mouse.release();
      clicked = false;
    }
  }
}

void fun_touchpadLoop(void) {
  fun_readPositions();
  fun_mapValues();
  fun_clickMouse();
}