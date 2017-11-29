#include "foll/repetitive.c"

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
