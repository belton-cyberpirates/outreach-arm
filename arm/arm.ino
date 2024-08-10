#include <Servo.h>

/******************************************************
 *                   PIN DEFINITIONS                  *
 ******************************************************/
#define VRX_PIN  A0 // Arduino pin connected to VRX pin
#define VRY_PIN  A1 // Arduino pin connected to VRY pin
#define BUTTON_PIN 52
#define SHOULDER_PIN 0
#define ELBOW_PIN 0
#define GRIP_PIN 7

/******************************************************
 *                   SENTINEL VALUES                  *
 ******************************************************/
#define CLOSED_VAL 150
#define OPEN_VAL 30

/******************************************************
 *         GLOBAL VARIABLES :: ARM STATE              *
 ******************************************************/
Servo shoulder;
Servo elbow;
Servo grip;

int joy_x_value = 0; // To store value of the X axis
int joy_y_value = 0; // To store value of the Y axis
int button_state = 0;
int shoulder_rot = 0;
int elbow_a = 0;

/******************************************************
 *                   INITIAL SETUP                    *
 ******************************************************/
void setup() {
  Serial.begin(9600);
  shoulder.attach(SHOULDER_PIN);
  elbow.attach(ELBOW_PIN);
  grip.attach(GRIP_PIN);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

/******************************************************
 *                   CONTROL LOOP                     *
 ******************************************************/
void loop() {
  // [ READ INPUT STATE ]
  joy_x_value = analogRead(VRX_PIN);
  joy_y_value = analogRead(VRY_PIN);
  button_state = digitalRead(BUTTON_PIN);


  // [ PRINT FOR MONITORING ]
  Serial.print("x = ");
  Serial.print(joy_x_value);
  Serial.print(", y = ");
  Serial.println(joy_y_value);
  Serial.print(", b = ");
  Serial.println(button_state);

  // [ REPOSITION ARM ]
  shoulder_rot = map(joy_x_value, 0, 1023, 0, 180);
  shoulder.write(180-shoulder_rot);

  elbow_a = map(joy_y_value, 0, 1023, 0, 180);
  elbow.write(elbow_a);

  grip.write(button_state ? CLOSED_VAL : OPEN_VAL);

  // [ DEBOUNCE DELAY ]
  delay(20);
}
