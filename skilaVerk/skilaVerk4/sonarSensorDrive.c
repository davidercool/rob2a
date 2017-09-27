#pragma config(Sensor, dgtl10,  sonarSensor,         sensorSONAR_cm)
#pragma config(Sensor, in1,    lightSensor,         sensorReflection)
#pragma config(Motor,  port2,           rightMotor,    tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port9,           leftMotor,     tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Sensor, dgtl5,  rightEncoder,        sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  leftEncoder,         sensorQuadEncoder)

/*----------------------------------------------------------------------------------------------------*\
|*                                     - Dual Joystick Control -                                      *|
|*                                      ROBOTC on VEX 2.0 Cortex                                      *|
|*                                                                                                    *|
|*    This program lets the robot navigate a room freely without crashing into walls.                 *|
|*    Additionally the robot is very scared of the dark and will stop if you turn the lights off.     *|
|*                                                                                                    *|
|*                                        ROBOT CONFIGURATION                                         *|
|*    NOTES:                                                                                          *|
|*    Pressing 7U stops the program                                                                   *|
|*                                                                                                    *|
|*    MOTORS & SENSORS:                                                                               *|
|*    [I/O Port]              [Name]              [Type]              [Description]                   *|
|*    Motor - Port 2          rightMotor           VEX Motor           Right motor                    *|
|*    Motor - Port 6          clawMotor            VEX Motor           Claw motor                     *|
\*----------------------------------------------------------------------------------------------------*/

bool sensorSafe() {
	if (SensorValue(sonarSensor) > 35  || SensorValue(sonarSensor) == -1) {
		return true;
	} else {
		return false;
	}
}

bool tooDark() {
	if (SensorValue(lightSensor) > 400) {
		return true;
	} else {
		return false;
	}
}

void turnUntilSafe() {
	motor[rightMotor] = -64;
	motor[leftMotor] = -64;
	wait1Msec(500);
	motor[rightMotor] = -50;
	motor[leftMotor] = 50;
	wait1Msec(300);
	while (SensorValue(sonarSensor) < 150 || SensorValue(sonarSensor) == -1) {
		motor[rightMotor] = -70;
		motor[leftMotor] = 70;
	}
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

task main () {
  while(true) {
  	if (vexRT[Btn7U] == 1 || tooDark()) {
  		break;
  	}

  	if (sensorSafe()) {
  		driveForever();
  	} else {
  		turnUntilSafe();
  	}
  }
}
