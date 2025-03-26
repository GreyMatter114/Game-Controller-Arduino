#include "UnoJoy.h"
#include "JoystickShield.h"
//#include <Wire.h>
//#include "MMA845XQ.h"
//
//// If SA0 on MMA845XQ is connected to GND (as on Akafuino L)
//MMA845XQ accel;
// If SA0 on MMA845XQ is connected to VCC or floating
//MMA845XQ accel(0x1D);
// JoystickShield object
JoystickShield joystick;

void setup() {
    setupUnoJoy();
    delay(20);  // Allow initialization
    joystick.setJoystickPins(A0, A1);  // Assuming default analog pins for X and Y
    joystick.setButtonPins(2, 3, 4, 5, 6, 7, 8);  // Set the digital pins for buttons
    joystick.calibrateJoystick();  // Calibrate the joystick
//    Wire.begin();
//    accel.begin(true, 16);
}

void loop() {
    dataForController_t controllerData = getBlankDataForController();
//    accel.update();
    // Map the joystick movement to the gamepad’s axes
    controllerData.leftStickX = analogRead(A0)>>2;
    controllerData.leftStickY = map(analogRead(A1)>>2, 0, 255, 255, 0);
//    controllerData.rightStickX = map(accel.getX(),-1,1,0,255);
//    controllerData.rightStickX = map(-accel.getY(),-1,1,255,0);
    // Map digital buttons to the gamepad buttons
    controllerData.crossOn = !digitalRead(2);  // CROSS button
    controllerData.circleOn = !digitalRead(3);  // CIRCLE button
    controllerData.squareOn = !digitalRead(4);  // SQUARE button
    controllerData.triangleOn = !digitalRead(7);  // TRIANGLE button

    // Map additional buttons
    controllerData.l1On = !digitalRead(6);  // L1 button
    controllerData.r1On = !digitalRead(5);  // R1 button
    controllerData.l3On = !digitalRead(8);  // Joystick press (L3)
//    controllerData.r3On = !digitalRead(9);  // Joystick press (R3)

    // Map D-Pad directions
    controllerData.dpadUpOn = joystick.isUp();
    controllerData.dpadDownOn = joystick.isDown();
    controllerData.dpadLeftOn = joystick.isLeft();
    controllerData.dpadRightOn = joystick.isRight();

    // Send data to the game controller
    setControllerData(controllerData);

    delay(10);  // Short delay for smooth response
}
