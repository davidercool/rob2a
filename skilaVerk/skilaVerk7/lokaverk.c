#pragma config(Sensor, in7,    lineFollowerRIGHT,   sensorLineFollower)
#pragma config(Sensor, in6,    lineFollowerCENTER,  sensorLineFollower)
#pragma config(Sensor, in8,    lineFollowerLEFT,    sensorLineFollower)
#pragma config(Motor,  port2,           rightMotor,    tmotorNormal, openLoop)
#pragma config(Motor,  port9,           leftMotor,     tmotorNormal, openLoop, reversed)
#pragma config(Sensor, dgtl10, sonarSensor,         sensorSONAR_cm)
#pragma config(Sensor, in1,    lightSensor,         sensorReflection)
#pragma config(Sensor, dgtl5,  rightEncoder,        sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  leftEncoder,         sensorQuadEncoder)
#pragma config(Motor,  port6,           clawMotor,     tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port7,           armMotor,      tmotorServoContinuousRotation, openLoop, reversed)
#include "foll/controlsVoid.c"
#include "constants.h"

/*----------------------------------------------------------------------------------------------------*\
|*                             	    - Triple Sensor Line Tracking -                                   *|
|*                                      ROBOTC on VEX 2.0 CORTEX                                      *|
|*                                                                                                    *|
|*                                        ROBOT CONFIGURATION                                         *|
|*    This robot will do all sorts of things, woohoo                                                  *|
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
/* VARIABLES */
int threshold = 2100;
string turnList[3] = {"l", "r", "r"};
float length = 0.5;

/* GLOBAL FOLL */
void stopMotors(int time=0) {
	motor[leftMotor] = 0;
	motor[rightMotor] = 0;
	wait1Msec(time);
}

void driveForever() {
	if(SensorValue[rightEncoder] == -SensorValue[leftEncoder]) {
		motor[rightMotor] = 70;
		motor[leftMotor]  = 70;
	}
	else if(SensorValue[rightEncoder] > -SensorValue[leftEncoder]) {
		motor[rightMotor] = 50;
		motor[leftMotor]  = 70;
	}
	else {
		motor[rightMotor] = 70;
		motor[leftMotor]  = 50;
	}
}

void driveForward(int rot) {
	while (SensorValue(rightEncoder) < rot) {
		if(SensorValue[rightEncoder] == -SensorValue[leftEncoder]) {
			motor[rightMotor] = 70;
			motor[leftMotor]  = 70;
		}
		else if(SensorValue[rightEncoder] > -SensorValue[leftEncoder])
		{
			motor[rightMotor] = 50;
			motor[leftMotor]  = 70;
		}
		else
		{
			motor[rightMotor] = 70;
			motor[leftMotor]  = 50;
		}
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

bool sonarvalue() {
	if (SensorValue[sonarSensor] < 20) {
		return true;
	} else {
		return false;
	}
}

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

/* VERK 6 FOLL */
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

/* VERK 5 FOLL */
bool sensorSafe() {
	if (SensorValue(sonarSensor) > 35  || SensorValue(sonarSensor) == -1) {
		return true;
	} else {
		return false;
	}
}

int tooDark() {
	if (SensorValue(lightSensor) > 450) {
		return 1;
	} else {
		return 0;
	}
}

void turnUntilSafe() {
	motor[rightMotor] = -64;
	motor[leftMotor] = -64;
	wait1Msec(500);
	motor[rightMotor] = -50;
	motor[leftMotor] = 50;
	wait1Msec(300);
	while (SensorValue(sonarSensor) < 100 || SensorValue(sonarSensor) == -1) {
		motor[rightMotor] = -70;
		motor[leftMotor] = 70;
	}
}

/* VERK 3 FOLL */
void clearEncoders() {
  SensorValue[rightEncoder] = 0;
  SensorValue[leftEncoder] = 0;
}

void turnLeft() {
	while (SensorValue(rightEncoder) < 90 * 3) {
		motor[rightMotor] = 50;
		motor[leftMotor] = -50;
	}
}

void turnRight() {
	while (-SensorValue(leftEncoder) < 90 * 3.8) {
		motor[leftMotor] = 50;
		motor[rightMotor] = -50;
	}
}

/* VERK 2 FOLL */
void driveForwardLen(int len) {
	motor[rightMotor] = 127;
	motor[leftMotor]  = 70;
	wait1Msec(len);
}

void driveBackwardLen(int len) {
	motor[rightMotor] = -75;
	motor[leftMotor]  = -127;
	wait1Msec(len);
}

/* VERKEFNI FOLL */
void verk6() {
	/* main loop */
	threshold = 2100;
	int c = 0;
	clawControl("open");
	while (c != 2) {
		if (vexRT[Btn8U] == 1) {break;}
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

void verk5() {
	/* main loop */
  threshold = 2420;
  while(true) {
  	if (vexRT[Btn8U] == 1) {break;}
  	if (SensorValue(lineFollowerCENTER) > threshold) {
      // go straight
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
}

void verk4() {
	/* main loop */
	while(true) {
		if (vexRT[Btn8U] == 1) {break;}
  	if (tooDark()) {
  		while (tooDark()) {
  			if (vexRT[Btn8U] == 1) {break;}
  			motor[rightMotor] = 0;
				motor[leftMotor]  = 0;
				wait10Msec(10);
  		}
  	}
  	if (sensorSafe()) {
  		driveForever();
  	} else {
  		turnUntilSafe();
  	}
  }
}

void verk3() {
	/* main loop */
	for (int i = 0; i < 3; i++) {
  	if (vexRT[Btn8U] == 1) {break;}
		clearEncoders();
		driveForward(0.5*BASEROTATION);
		if (vexRT[Btn8U] == 1) {break;}
		clearEncoders();
		if (turnList[i] == "l") {
			turnLeft();
		} else {
			turnRight();
		}
		if (vexRT[Btn8U] == 1) {break;}
		stopMotors(250);
	}
	if (vexRT[Btn8U] == 1) {return;}
	clearEncoders();
	driveForward(0.5*BASEROTATION);
}

void verk2() {
	/* main loop */
	while (true) {
		if (vexRT[Btn8U] == 1) {break;}
		length = 0.5;
		if (length == 2.5) {
			break;
		}
		driveForwardLen(length*BASETIME);
		stopMotors(250);
		driveBackwardLen(length*BASETIME);
		stopMotors(250);
		length = length + 0.5;
	}
}

/* MAIN */
task main() {
	while (true) {
		if (vexRT[Btn7U] == 1) {break;}
		if (vexRT[Btn7L] == 1) {verk6();}
		if (vexRT[Btn7D] == 1) {verk5();}
		if (vexRT[Btn7R] == 1) {verk4();}
		if (vexRT[Btn8L] == 1) {verk3();}
		if (vexRT[Btn8D] == 1) {verk2();}
		if (vexRT[Btn8R] == 1) {
			while (true) {
				if (vexRT[Btn8U] == 1) {break;}
				enableControls();
			}
		}
	}
}
