int x = vexRT[Ch1];
int y = vexRT[Ch2];
int yxArray[2];

int convertToInt(float fl) {
	return (int)(fl);
}

void yAxis(int yas) {
	yas = yas / 2;
	yxArray[0] = yas;
	yxArray[1] = yas;
}

void xAxis(int xas) {
	xas = xas / 2;
	xas = convertToInt(xas);
	int arr1 = xas+yxArray[0];
	int arr2 = xas-yxArray[1];
	yxArray[0] = arr1;
	yxArray[1] = arr2;
}

void driveArray (int *arr) {
	motor[leftMotor] = arr[0];
	motor[rightMotor] = arr[1];
}

void clawControl() {
	if (vexRT[Btn6U] == 1) {
		motor[armMotor] = 63;
	}	else if (vexRT[Btn5U] == 1) {
		motor[armMotor] = -15;
	} else {
		motor[armMotor] = 0;
	}

	if (vexRT[Btn5D] == 1) {
		motor[clawMotor] = 63;
	} else if (vexRT[Btn6D] == 1) {
		motor[clawMotor] = -63;
	} else {
		motor[clawMotor] = 0;
	}
}

void enableControls() {
	x = vexRT[Ch2];
	y = vexRT[Ch1];
	yAxis(y);
	xAxis(x);
	driveArray(yxArray);
	clawControl();
}
