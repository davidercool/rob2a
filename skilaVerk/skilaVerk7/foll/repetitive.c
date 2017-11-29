#include "constants.h"

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

void FollowLine() {
	if (SensorValue(lineFollowerCENTER) > THRESHOLD) {
    motor[leftMotor]  = 42;
    motor[rightMotor] = 42;
  }
  else if (SensorValue(lineFollowerRIGHT) > THRESHOLD) {
    motor[leftMotor]  = 42;
    motor[rightMotor] = -42;
  }
  else if (SensorValue(lineFollowerLEFT) > THRESHOLD) {
    motor[leftMotor]  = -42;
    motor[rightMotor] = 42;
  }
}

bool isLine() {
	if (SensorValue(lineFollowerCENTER) < THRESHOLD ||
		SensorValue(lineFollowerRIGHT) < THRESHOLD || SensorValue(lineFollowerLEFT) < THRESHOLD) {
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
