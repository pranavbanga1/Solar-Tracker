#include <Servo.h>

Servo panServo;   // create servo object for pan servo
Servo tiltServo;  // create servo object for tilt servo

int panPin = 10;  // define pin for pan servo
int tiltPin = 11;  // define pin for tilt servo

int ldrPins[4] = {A0, A1, A2, A3};  // define pins for 4 LDRs
int ldrReadings[4];  // array to store LDR readings

/*int joystickXPin = A4;   // define pin for joystick X-axis
int joystickYPin = A5;   // define pin for joystick Y-axis
int joystickXVal;  // variable to store joystick X-axis value
int joystickYVal;  // variable to store joystick Y-axis value*/

int panAngle = 90;   // initial pan angle (centered)
int tiltAngle = 90;  // initial tilt angle (centered)

void setup() {
  Serial.begin(9600);  // initialize serial communication
  
  panServo.attach(panPin);   // attach pan servo to pan pin
  tiltServo.attach(tiltPin);  // attach tilt servo to tilt pin
  
  // set initial servo angles to center
  panServo.write(panAngle);
  tiltServo.write(tiltAngle);
}

void loop() {
  // read joystick X-axis and Y-axis values
 /* joystickXVal = analogRead(joystickXPin);
  joystickYVal = analogRead(joystickYPin);
  
  // map joystick values to servo angles (-90 to 90)
  panAngle = map(joystickXVal, 0, 1023, 0, 180);
  tiltAngle = map(joystickYVal, 0, 1023, 0, 180);*/
  
  // read LDR values and find the LDR with the highest reading
  int maxLDRNum = 0;
  int maxLDRVal = 0;
  for (int i = 0; i < 4; i++) {
    ldrReadings[i] = analogRead(ldrPins[i]);
    if (ldrReadings[i] > maxLDRVal) {
      maxLDRNum = i;
      maxLDRVal = ldrReadings[i];
    }
  }
  
  // calculate pan and tilt adjustments based on the maximum LDR number
  int panAdjustment = 0;
  int tiltAdjustment = 0;
  switch (maxLDRNum) {
    case 0:
      panAdjustment = -10;
      tiltAdjustment = -10;
      break;
    case 1:
      panAdjustment = 10;
      tiltAdjustment = -10;
      break;
    case 2:
      panAdjustment = -10;
      tiltAdjustment = 10;
      break;
    case 3:
      panAdjustment = 10;
      tiltAdjustment = 10;
      break;
  }
  
  // apply adjustments to pan and tilt angles
  panAngle += panAdjustment;
  tiltAngle += tiltAdjustment;
  
  // limit pan and tilt angles to servo range (0-180)
 -panAngle = constrain(panAngle, 0, 180);
  tiltAngle = constrain(tiltAngle, 0, 180);
  
  // move pan and tilt servos to the new angles
panServo.write(panAngle);
tiltServo.write(tiltAngle);

// print joystick and LDR readings to serial monitor
/*Serial.print("Joystick X-axis: ");
Serial.println(joystickXVal);
Serial.print("Joystick Y-axis: ");
Serial.println(joystickYVal);*/
Serial.print("LDR 1 reading: ");
Serial.println(ldrReadings[0]);
Serial.print("LDR 2 reading: ");
Serial.println(ldrReadings[1]);
Serial.print("LDR 3 reading: ");
Serial.println(ldrReadings[2]);
Serial.print("LDR 4 reading: ");
Serial.println(ldrReadings[3]);
Serial.println();

delay(100); // small delay to allow for servo movement
}
