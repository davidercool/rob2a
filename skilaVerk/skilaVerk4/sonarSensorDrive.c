#pragma config(Sensor, dgtl10, sonarSensor,         sensorSONAR_cm)
#pragma config(Sensor, in1,    lightSensor,         sensorReflection)
#pragma config(Motor,  port2,  rightMotor,          tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port9,  leftMotor,           tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Sensor, dgtl5,  rightEncoder,        sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  leftEncoder,         sensorQuadEncoder)
#include "foll/ultrasonic&light_sensor_foll.c"
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



task main () {
  while(true) {
  	if (tooDark()) {
  		while (tooDark()) {
  			motor[rightMotor] = 0;
				motor[leftMotor]  = 0;
				wait10Msec(10);
  		}
  	}
  	if (vexRT[Btn7U] == 1) {
  		break;
  	}
  	if (sensorSafe()) {
  		driveForever();
  	} else {
  		turnUntilSafe();
  	}
  }
}
