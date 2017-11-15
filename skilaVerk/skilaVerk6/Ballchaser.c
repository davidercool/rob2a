#pragma config(Sensor, in7,    lineFollowerRIGHT,   sensorLineFollower)
#pragma config(Sensor, in6,    lineFollowerCENTER,  sensorLineFollower)
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
|*    Motor - Port 6      clawMotor           VEX Motor             Claw motor                        *|
|*    Motor - Port 7			armMotor						VEX motor				    	Arm motor									    		*|
\*----------------------------------------------------------------------------------------------------*/
bool ballphase = true;
int threshold = 2100;

bool sensorTriggered = false;

void stopMotors() {
	motor[leftMotor] = 0;
	motor[rightMotor] = 0;
}

void FollowLine() {
	if (SensorValue(lineFollowerCENTER) > threshold) {
    motor[leftMotor]  = 42;
    motor[rightMotor] = 42;
  }
  else if (SensorValue(lineFollowerRIGHT) > threshold) {
    motor[leftMotor]  = 42;
    motor[rightMotor] = -42;
  }
  else if (SensorValue(lineFollowerLEFT) > threshold) {
    motor[leftMotor]  = -42;
    motor[rightMotor] = 42;
  }
}

bool isLine() {
	if (SensorValue(lineFollowerCENTER) < threshold ||
		SensorValue(lineFollowerRIGHT) < threshold || SensorValue(lineFollowerLEFT) < threshold) {
		return true;
	}
	return false;
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
		wait1Msec(350);
		motor[clawMotor] = 0;
	} else if (s == "close") {
		motor[clawMotor] = -125;
		wait1Msec(350);
		motor[clawMotor] = 0;
	}
}

void driveForwardMs(int x) {
	motor[rightMotor] = 40;
	motor[leftMotor] = 40;
	wait1Msec(x);
	stopMotors();
}

void driveBackwardMs(int x) {
	motor[rightMotor] = -125;
	motor[leftMotor] = -125;
	wait1Msec(x);
	stopMotors();
}

void turnAround() {
	driveBackwardMs(200);
	motor[rightMotor] = 125;
	motor[leftMotor] = -125;
	wait1Msec(1050);
	stopMotors();
}

void liftBall() {
	motor[armMotor] = 63;
	wait1Msec(600);
	motor[armMotor] = 0;
}

void getBall() {
	stopMotors();
	driveForwardMs(100);
	clawControl("close");
	liftBall();
	turnAround();
}

void dropInBasket() {
	stopMotors();
	driveForwardMs(400);
	clawControl("open");
}

bool sonarvalue() {
	if (SensorValue[sonarSensor] < 20) {
		return true;
	} else {
		return false;
	}
}

/*
task main()
{
	clawControl("open");
	while (true) {
		if (sonarvalue() && ballphase) {
			getBall();
			ballphase = false;
		} else if (sonarvalue() && !ballphase) {
			dropInBasket();
		} else {
			FollowLine();
		}
	}
}
*/

task main() {
	while (true) {
		if (vexRT[Btn7L] == 1) {break;}
	}
	int c = 0;
	clawControl("open");
	while (c != 2) {
		if (!sonarvalue()) {
			FollowLine();
		} else {
			if (c == 1) {
				dropInBasket();
			} else {
				getBall();
			}
			c++;
		}
	}
}
