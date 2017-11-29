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
