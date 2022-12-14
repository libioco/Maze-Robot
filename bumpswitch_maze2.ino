/*
 */

#include "SimpleRSLK.h"

/* Turn Constant: constant that needs to be tuned */
float turnConstant = 2;
int wheelSpeed = 15; // Default raw pwm speed for motor.

void setup() {
	Serial.begin(115200);
	setupRSLK();
	/* Left button on Launchpad */
	setupWaitBtn(LP_LEFT_BTN);
	/* Red led in rgb led */
	setupLed(RED_LED);
}

uint32_t degreesToEncoder(float turnConstant, uint32_t angle) {
    float temp = turnConstant * angle;
    return int(temp);
}

// Turn the robot angle amount
void turn(int angleToTurn) {
  Serial.print("Turn: ");  Serial.println(angleToTurn);
    
  int totalCount = 0; // Total amount of encoder pulses received
  boolean sign = angleToTurn<0? false: true;

  angleToTurn = abs(angleToTurn);

  /* Amount of encoder pulses needed to achieve distance */
  int x = degreesToEncoder(turnConstant, angleToTurn);
  
  /* Set the encoder pulses count back to zero */
  resetLeftEncoderCnt();
  resetRightEncoderCnt();

  /* Cause the robot to turn */
  if (sign == false) {
    setMotorDirection(LEFT_MOTOR,MOTOR_DIR_FORWARD);
    setMotorDirection(RIGHT_MOTOR,MOTOR_DIR_BACKWARD);
  } else {
    setMotorDirection(RIGHT_MOTOR,MOTOR_DIR_FORWARD);
    setMotorDirection(LEFT_MOTOR,MOTOR_DIR_BACKWARD);
  }

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

void loop() {
	bool hitObstacle = false;

	String btnMsg = "Push left button on Launchpad to start demo.\n";
	/* Wait until button is pressed to start robot */
	waitBtnPressed(LP_LEFT_BTN,btnMsg,RED_LED);

	/* Wait two seconds before starting */
	delay(1000);

	/* Enable both motors, set their direction and provide a default speed */
	enableMotor(BOTH_MOTORS);
	setMotorDirection(BOTH_MOTORS,MOTOR_DIR_FORWARD);
	setMotorSpeed(BOTH_MOTORS,wheelSpeed);

  // Loop forever
  while(true) {
    boolean collision = false;
  	/* Keep checking if the robot has hit an object */
    if (isBumpSwitchPressed(0) == true) {
      collision = true;
      turn(65);
    }
    else if (isBumpSwitchPressed(1) == true) {
      collision = true;
      turn(85);
    }
    else if (isBumpSwitchPressed(2) == true) {
      collision = true;
      turn(100);
    }
    else if (isBumpSwitchPressed(3) == true) {
      collision = true;
      turn(-105);
    }
    else if (isBumpSwitchPressed(4) == true) {
      collision = true;
      turn(-85);
 
    } else if (isBumpSwitchPressed(5) == true) {
      collision = true;
      turn(-65);
    }
    
    if (collision) {  // if we hit something then we need to start motors again
      delay(1000);
      enableMotor(BOTH_MOTORS);
      setMotorDirection(BOTH_MOTORS,MOTOR_DIR_FORWARD);
      setMotorSpeed(BOTH_MOTORS,wheelSpeed);
    }
  }
}
