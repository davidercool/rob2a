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
