#pragma config(Sensor, in7,    lineFollowerRIGHT,   sensorLineFollower)
#pragma config(Sensor, in6,    lineFollowerCENTER,  sensorLineFollower)
#pragma config(Sensor, in8,    lineFollowerLEFT,    sensorLineFollower)
#pragma config(Motor,  port2,  rightMotor,          tmotorNormal, openLoop)
#pragma config(Motor,  port9,  leftMotor,           tmotorNormal, openLoop, reversed)
#pragma config(Sensor, dgtl10, sonarSensor,         sensorSONAR_cm)
#pragma config(Sensor, in1,    lightSensor,         sensorReflection)
#pragma config(Sensor, dgtl5,  rightEncoder,        sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  leftEncoder,         sensorQuadEncoder)
#pragma config(Motor,  port6,  clawMotor,           tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port7,  armMotor,            tmotorServoContinuousRotation, openLoop, reversed)
#include "foll/controlsVoid.c"
#include "foll/Verkefni6.c"
#include "foll/Verkefni5.c"
#include "foll/Verkefni4.c"
#include "foll/Verkefni3.c"
#include "foll/Verkefni2.c"

/*----------------------------------------------------------------------------------------------------*\
|*                             	    - Triple Sensor Line Tracking -                                   *|
|*                                      ROBOTC on VEX 2.0 CORTEX                                      *|
|*                                                                                                    *|
|*                                        ROBOT CONFIGURATION                                         *|
|*    This robot will do all sorts of things, woohoo                                                  *|
|*                                                                                                    *|
|*                                                                                                    *|
|*    Notes:                                                                                          *|
|*    verkefni 1: controller takki 8R                                                                 *|
|*    verkefni 2: suicide takki 8D                                                                    *|
|*    verkefni 3: verkefni 2.2 left right 8L                                                          *|
|*    verkefni 4: navigation og light sensetivity takki 7R                                            *|
|*    verkefni 5: line follower takki 7D                                                              *|
|*    verkefni 6: put ball into basket ft. line follower takki 7L                                     *|
|*                                                                                                    *|
|*    MOTORS & SENSORS:                                                                               *|
|*    [I/O Port]          [Name]              [Type]                [Description]                     *|
|*    Motor  - Port 2     rightMotor          VEX 3-wire module     Right side motor                  *|
|*    Motor  - Port 9     leftMotor           VEX 3-wire module     Left side motor                   *|
|*    Analog - Port 6     lineFollowerRIGHT   VEX Light Sensor      Front-right, facing down          *|
|*    Analog - Port 7     lineFollowerCENTER  VEX Light Sensor      Front-center, facing down         *|
|*    Analog - Port 8     lineFollowerLEFT    VEX Light Sensor      Front-left, facing down           *|
|*    Digital -Port 10    sonarSensor         VEX Sonar Sensor      Front-left, facing forward        *|
|*    Motor -  Port 6     clawMotor           VEX Motor             Claw motor                        *|
|*    Motor -  Port 7			armMotor						VEX motor				    	Arm motor									    		*|
|*    sensor - Port in1		lightSensor					VEX motor				    	Arm motor									    		*|
|*    sensor - Port 15		leftEncoder					VEX motor				    	Arm motor									    		*|
|*    sensor - Port 17		rightEncoder				VEX motor				    	Arm motor									    		*|
\*----------------------------------------------------------------------------------------------------*/

/* VARIABLES */

string turnList[3] = {"l", "r", "r"};
float length = 0.5;

/* MAIN TASKS */

task verk6() {
	/* main loop */
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

task verk5() {
	/* main loop */
  while(true) {
  	if (vexRT[Btn8U] == 1) {break;}
      FollowLine();
  }
}

task verk4() {
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

task verk3() {
	/* main loop */
	for (int i = 0; i < 3; i++) {
		clearEncoders();
			if (vexRT[Btn8U] == 1) {break;}
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
	stopMotors(100);
}

task verk2() {
	/* main loop */
	while (true) {
		if (vexRT[Btn8U] == 1) {break;}
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

task verk1() {
	while(true)
  {
  	if (vexRT[Btn8U] == 1) {
  		break;
  	}
  	enableControls();
  }
}

/* MAIN */
task main() {
	while (true) {
		if (vexRT[Btn7U] == 1) {break;}
		if (vexRT[Btn7L] == 1) {StartTask(verk6);}
		if (vexRT[Btn7D] == 1) {StartTask(verk5);}
		if (vexRT[Btn7R] == 1) {StartTask(verk4);}
		if (vexRT[Btn8L] == 1) {StartTask(verk3);}
		if (vexRT[Btn8D] == 1) {StartTask(verk2);}
		if (vexRT[Btn8R] == 1) {StartTask(verk1);}
	}
}
