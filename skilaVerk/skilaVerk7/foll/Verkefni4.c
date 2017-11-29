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
