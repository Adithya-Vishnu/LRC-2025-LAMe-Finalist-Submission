#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE

#include <Arduino.h>
#include <DabbleESP32.h>
#include <ESP32Servo.h>

// ===== SERVOS =====
Servo baseServo;
Servo shoulderServo;
Servo elbowServo;
Servo wristPitchServo;
Servo gripperServo;

// ===== PIN ASSIGNMENTS =====
#define BASE_PIN 13
#define SHOULDER_PIN 12
#define ELBOW_PIN 14
#define WRIST_PIN 27
#define GRIP_PIN 26

// Current servo angles
int baseAngle = 90;
int shoulderAngle = 90;
int elbowAngle = 90;
int wristAngle = 90;
int gripperAngle = 20;   // open

// Current selected servo
// 0 = Base, 1 = Shoulder, 2 = Elbow, 3 = Wrist, 4 = Gripper
int selectedServo = 0;

void setup() {
  Serial.begin(115200);

  // Start Dabble Bluetooth
  Dabble.begin("ESP32_ARM");

  // Attach servos to pins
  baseServo.attach(BASE_PIN);
  shoulderServo.attach(SHOULDER_PIN);
  elbowServo.attach(ELBOW_PIN);
  wristPitchServo.attach(WRIST_PIN);
  gripperServo.attach(GRIP_PIN);

  Serial.println("Robotic Arm Ready! Open Dabble → Gamepad → Connect.");
}

void loop() {
  Dabble.processInput();

  // ---------- SELECT SERVO ----------
  // if (GamePad.isSquarePressed())  selectedServo = 0; // Base
  if (GamePad.isSquarePressed()) selectedServo = 1; // Shoulder
  if (GamePad.isTrianglePressed())   selectedServo = 2; // Elbow
  if (GamePad.isCirclePressed())    selectedServo = 3; // Wrist
  if (GamePad.isCrossPressed())       selectedServo = 4; // Gripper

  // ---------- MOVE SELECTED SERVO ----------
  int moveAmount = 2; // degrees per press

  if (selectedServo == 0) {
    // Base controlled by LEFT/RIGHT
    if (GamePad.isRightPressed()) baseAngle += moveAmount;
    if (GamePad.isLeftPressed())  baseAngle -= moveAmount;
    baseAngle = constrain(baseAngle, 0, 180);
    baseServo.write(baseAngle);
  } 
  else {
    switch(selectedServo) {
      // case 0: // Base
      //   if (GamePad.isUpPressed()) baseAngle += moveAmount;
      //   if (GamePad.isDownPressed()) baseAngle -= moveAmount;
      //   baseAngle = constrain(baseAngle, 0, 180);
      //   baseServo.write(baseAngle);
      //   break;
      case 1: // Shoulder
        if (GamePad.isUpPressed()) shoulderAngle += moveAmount;
        if (GamePad.isDownPressed()) shoulderAngle -= moveAmount;
        shoulderAngle = constrain(shoulderAngle, 0, 180);
        shoulderServo.write(shoulderAngle);
        break;

      case 2: // Elbow
        if (GamePad.isUpPressed()) elbowAngle += moveAmount;
        if (GamePad.isDownPressed()) elbowAngle -= moveAmount;
        elbowAngle = constrain(elbowAngle, 0, 180);
        elbowServo.write(elbowAngle);
        break;

      case 3: // Wrist
        if (GamePad.isUpPressed()) wristAngle += moveAmount;
        if (GamePad.isDownPressed()) wristAngle -= moveAmount;
        wristAngle = constrain(wristAngle, 0, 180);
        wristPitchServo.write(wristAngle);
        break;

      case 4: // Gripper
        if (GamePad.isUpPressed()) gripperAngle += moveAmount;
        if (GamePad.isDownPressed()) gripperAngle -= moveAmount;
        gripperAngle = constrain(gripperAngle, 0, 180);
        gripperServo.write(gripperAngle);
        break;
    }
  }

  delay(20); // smooth update
}
