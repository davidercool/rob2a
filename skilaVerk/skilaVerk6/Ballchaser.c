#pragma config(Sensor, in6,    lineFollowerRIGHT,   sensorLineFollower)
#pragma config(Sensor, in7,    lineFollowerCENTER,  sensorLineFollower)
#pragma config(Sensor, in8,    lineFollowerLEFT,    sensorLineFollower)
#pragma config(Motor,  port2,           rightMotor,    tmotorNormal, openLoop)
#pragma config(Motor,  port9,           leftMotor,     tmotorNormal, openLoop, reversed)
#pragma config(Sensor, dgtl10, sonarSensor,         sensorSONAR_cm)

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
\*----------------------------------------------------------------------------------------------------*/
int threshold = 2420;
void FollowLine() {
  	if (SensorValue(lineFollowerCENTER) > threshold) {
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

  	if (vexRT[Btn7U] == 1) {
  		break;
  	}
}

bool sensorSafe() {
	if (SensorValue(sonarSensor) > 35  || SensorValue(sonarSensor) == -1) {
		return true;
	} else {
		return false;
	}
}

task main()
{
	while (true) {
		FollowLine();
		if (sensorSafe()) {

	}
	}

}
