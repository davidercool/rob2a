#pragma config(Sensor, in6,    lineFollowerRIGHT,   sensorLineFollower)
#pragma config(Sensor, in7,    lineFollowerCENTER,  sensorLineFollower)
#pragma config(Sensor, in8,    lineFollowerLEFT,    sensorLineFollower)
#pragma config(Motor,  port2,           rightMotor,    tmotorNormal, openLoop)
#pragma config(Motor,  port9,           leftMotor,     tmotorNormal, openLoop, reversed)

/*----------------------------------------------------------------------------------------------------*\
|*                             	    - Triple Sensor Line Tracking -                                   *|
|*                                      ROBOTC on VEX 2.0 CORTEX                                      *|
|*                                                                                                    *|
|*                                        ROBOT CONFIGURATION                                         *|
|*    NOTES:                                                                                          *|
|*		This Robot Follows A Line...																																		*|
|*                                                                                                    *|
|*    MOTORS & SENSORS:                                                                               *|
|*    [I/O Port]          [Name]              [Type]                [Description]                     *|
|*    Motor  - Port 2     rightMotor          VEX 3-wire module     Right side motor                  *|
|*    Motor  - Port 9     leftMotor           VEX 3-wire module     Left side motor                   *|
|*    Analog - Port 6     lineFollowerRIGHT   VEX Light Sensor      Front-right, facing down          *|
|*    Analog - Port 7     lineFollowerCENTER  VEX Light Sensor      Front-center, facing down         *|
|*    Analog - Port 8     lineFollowerLEFT    VEX Light Sensor      Front-left, facing down           *|
\*-----------------------------------------------------------------------------------------------4246-*/

task main() {
  wait1Msec(2000);

  int threshold = 2420;
  while(true)
  {
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

  	if (vexRT[Btn7U] == 1) {
  		break;
  	}
  }
}
