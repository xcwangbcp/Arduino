#include <ArduinoRobot.h>
#include <Arduino_LCD.h>
#include <Compass.h>
#include <EasyTransfer2.h>
#include <EEPROM_I2C.h>
#include <Fat16.h>
#include <Fat16Config.h>
#include <Fat16mainpage.h>
#include <Fat16util.h>
#include <FatStructs.h>
#include <Multiplexer.h>
#include <SdCard.h>
#include <SdInfo.h>
#include <Squawk.h>
#include <SquawkSD.h>

#include <Stepper.h>


/*
 Stepper Motor Control - one step at a time

 This program drives a unipolar or bipolar stepper motor.
 The motor is attached to digital pins 8 - 11 of the Arduino.

 The motor will step one step at a time, very slowly.  You can use this to
 test that you've got the four wires of your stepper wired to the correct
 pins. If wired correctly, all steps should be in the same direction.

 Use this also to count the number of steps per revolution of your motor,
 if you don't know it.  Then plug that number into the oneRevolution
 example to see if you got it right.

 Created 30 Nov. 2009
 by Tom Igoe

 */

#include <Stepper.h>

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 9, 12, 13);

int stepCount = 0;         // number of steps the motor has taken
int bufferInt = -1;

void setup() {
  // initialize the serial port:
  Serial.begin(9600);
}

void loop() {
  // step one step:
  if (Serial.available() > 0) {
    bufferInt = Serial.read();
  if (bufferInt == '1') {
  myStepper.step(1);
  Serial.print("steps:");
  Serial.println(stepCount);
  stepCount++;
  delay(500);
  }
  }
}
