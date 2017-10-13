#pragma config(Sensor, in6,    lineFollowerRIGHT,   sensorLineFollower)
#pragma config(Sensor, in7,    lineFollowerCENTER,  sensorLineFollower)
#pragma config(Sensor, in8,    lineFollowerLEFT,    sensorLineFollower)
#pragma config(Motor,  port2,           rightMotor,    tmotorNormal, openLoop)
#pragma config(Motor,  port9,           leftMotor,     tmotorNormal, openLoop, reversed)
#pragma config(Sensor, dgtl10, sonarSensor,         sensorSONAR_cm)
#pragma config(Motor,  port6,           clawMotor,     tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port7,           armMotor,      tmotorServoContinuousRotation, openLoop, reversed)

/*----------------------------------------------------------------------------------------------------*\
|*                             	    - Triple Sensor Line Tracking -                                   *|
|*                                      ROBOTC on VEX 2.0 CORTEX                                      *|
|*                                                                                                    *|
|*                                        ROBOT CONFIGURATION                                         *|
|*    This robot will follow a line until it reaches the end of it. At the end of the line it will    *|
|*    attempt to pick up a ball. Then the robot will turn around, follow the line back, and then put  *|
|*    the ball in a basket at the other end of the line.                                              *|
|*                                                                                                    *|
|*                                                                                                    *|
|*    MOTORS & SENSORS:                                                                               *|
|*    [I/O Port]          [Name]              [Type]                [Description]                     *|
|*    Motor  - Port 2     rightMotor          VEX 3-wire module     Right side motor                  *|
|*    Motor  - Port 9     leftMotor           VEX 3-wire module     Left side motor                   *|
|*    Analog - Port 6     lineFollowerRIGHT   VEX Light Sensor      Front-right, facing down          *|
|*    Analog - Port 7     lineFollowerCENTER  VEX Light Sensor      Front-center, facing down         *|
|*    Analog - Port 8     lineFollowerLEFT    VEX Light Sensor      Front-left, facing down           *|
|*    Digital - Port 10   sonarSensor         VEX Sonar Sensor      Front-left, facing forward        *|
|*    Motor - Port 6          clawMotor            VEX Motor           Claw motor                     *|
|*    Motor - Port 7					armMotor						 VEX motor					 Arm motor											*|
\*----------------------------------------------------------------------------------------------------*/
bool ballPhace = true;
int threshold = 2480;

bool sensorTriggered = false;

void stopMotors() {
	motor[leftMotor] = 0;
	motor[rightMotor] = 0;
}

void FollowLine() {
	if (SensorValue(lineFollowerCENTER) > threshold) {
    motor[leftMotor]  = 64;
    motor[rightMotor] = 64;
  }
  else if (SensorValue(lineFollowerRIGHT) > threshold) {
    motor[leftMotor]  = 64;
    motor[rightMotor] = -32;
  }
  else if (SensorValue(lineFollowerLEFT) > threshold) {
    motor[leftMotor]  = -32;
    motor[rightMotor] = 64;
  }
}

/*
void clawBite() {
	if (objectFound && phase == 0) {
		stopMotors();
		motor[clawMotor] = 63;
		wait1Msec(500);
		motor[clawMotor] = -0;
	} else if (objectFound && phase > 0) {
		emergencyStop();
		motor[armMotor] = 63;
		wait1Msec(500);
		motor[armMotor] = 0;
		motor[clawMotor] = 63;
		wait1Msec(300);
	}
	motor[clawMotor] = -63;
	wait1Msec(500);
	motor[clawMotor] = -0;
}
*/

void clawControl(const string s) {
	if (s == "open") {
		motor[clawMotor] = 125;
		wait1Msec(250);
		motor[clawMotor] = 0;
	} else if (s == "close") {
		motor[clawMotor] = -125;
		wait1Msec(250);
		motor[clawMotor] = 0;
	}
}

void turnAround() {
	motor[rightMotor] = 125;
	motor[leftMotor] = -125;
	wait1Msec(100);
	stopMotors();
}

void driveForwardMs(int x) {
	motor[rightMotor] = 125;
	motor[leftMotor] = 125;
	wait1Msec(x);
	stopMotors();
}


void getBall() {
	stopMotors();
	clawControl("open");
	driveForwardMs(200);
	clawControl("close");
	turnAround();
}

void dropInBasket() {
	stopMotors();
	driveForwardMs(200);
	clawControl("open");
}

task main()
{
	while (true) {
		if (sensorTriggered && ballPhace) {
			getBall();
		} else if (sensorTriggered && !ballPhace) {
			dropInBasket();
			break;
		} else {
			FollowLine();
		}
	}
}

task Sensor() {
	if (SensorValue[sonarSensor] < 30) {
		sensorTriggered = true;
	} else {
		sensorTriggered = false;
	}
}
