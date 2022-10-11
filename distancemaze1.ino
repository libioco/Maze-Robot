#include "SimpleRSLK.h"
#include "Energia.h"

/* Diameter of Romi wheels in inches */
float wheelDiameter = 2.78;

/* Number of encoder (rising) pulses every time the wheel turns completely */
int cntPerRevolution = 360;

int cntPerDegree = 16;

int wheelSpeed = 15; // Default raw pwm speed for motor.



void setup() {
  Serial.begin(115200);

  setupRSLK();
  /* Left button on Launchpad */
  setupWaitBtn(LP_LEFT_BTN);
  /* Red led in rgb led */
  setupLed(RED_LED);
}

void firstForward(int inchesToTravel) {
  uint16_t totalCount = 0; // Total amount of encoder pulses received

  /* Amount of encoder pulses needed to achieve distance */
  uint16_t x = distanceToEncoder(wheelDiameter, cntPerRevolution, inchesToTravel);
  String btnMsg = "Expected count: ";
  btnMsg += x;

  /* Wait until button is pressed to start robot */
  btnMsg += "\nPush left button on Launchpad to start demo.\n";
  /* Wait until button is pressed to start robot */
  waitBtnPressed(LP_LEFT_BTN,btnMsg,RED_LED);

  delay(2000);

  /* Set the encoder pulses count back to zero */
  resetLeftEncoderCnt();
  resetRightEncoderCnt();

  /* Cause the robot to drive forward */
  setMotorDirection(BOTH_MOTORS,MOTOR_DIR_FORWARD);

  /* "Turn on" the motor */
  enableMotor(BOTH_MOTORS);

  /* Set motor speed */
  setMotorSpeed(BOTH_MOTORS,wheelSpeed);

  /* Drive motor until it has received x pulses */
  while(totalCount < x)
  {
    totalCount = getEncoderLeftCnt();
    Serial.println(totalCount);
  }

  /* Halt motors */
  disableMotor(BOTH_MOTORS);
}

void turn(int angleToTurn) {
  uint16_t totalCount = 0; // Total amount of encoder pulses received

  /* Amount of encoder pulses needed to achieve distance */
  uint16_t x = angleToEncoder(wheelDiameter, cntPerDegree, angleToTurn);
  String btnMsg = "Expected count: ";
  btnMsg += x;

  delay(2000);

  /* Set the encoder pulses count back to zero */
  resetLeftEncoderCnt();
  resetRightEncoderCnt();

  /* Cause the robot to turn */
  setMotorDirection(LEFT_MOTOR,MOTOR_DIR_FORWARD);
  setMotorDirection(RIGHT_MOTOR,MOTOR_DIR_BACKWARD);

  /* "Turn on" the motor */
  enableMotor(BOTH_MOTORS);

  /* Set motor speed */
  setMotorSpeed(BOTH_MOTORS,wheelSpeed);

  /* Drive motor until it has received x pulses */
  while(totalCount < x)
  {
    totalCount = getEncoderLeftCnt();
    Serial.println(totalCount);
  }

  /* Halt motors */
  disableMotor(BOTH_MOTORS);
}

void forward(int inchesToTravel) {
  uint16_t totalCount = 0; // Total amount of encoder pulses received

  /* Amount of encoder pulses needed to achieve distance */
  uint16_t x = distanceToEncoder(wheelDiameter, cntPerRevolution, inchesToTravel);
  String btnMsg = "Expected count: ";
  btnMsg += x;

  delay(2000);

  /* Set the encoder pulses count back to zero */
  resetLeftEncoderCnt();
  resetRightEncoderCnt();

  /* Cause the robot to drive forward */
  setMotorDirection(BOTH_MOTORS,MOTOR_DIR_FORWARD);

  /* "Turn on" the motor */
  enableMotor(BOTH_MOTORS);

  /* Set motor speed */
  setMotorSpeed(BOTH_MOTORS,wheelSpeed);

  /* Drive motor until it has received x pulses */
  while(totalCount < x)
  {
    totalCount = getEncoderLeftCnt();
    Serial.println(totalCount);
  }

  /* Halt motors */
  disableMotor(BOTH_MOTORS);
}

void loop(){

  firstForward(10);
  turn(90);
  forward(10);
  turn(290);
  forward(22);
  turn(90);
  forward(22);
  turn(90); 
  forward(33);
  turn(90);
  forward(10);
  turn(360);
  
}
