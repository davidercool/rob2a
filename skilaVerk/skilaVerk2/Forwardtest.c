#pragma config(Sensor, dgtl5,  rightEncoder,        sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  leftEncoder,         sensorQuadEncoder)
#pragma config(Motor,  port2,           rightMotor,    tmotorNormal, openLoop)
#pragma config(Motor,  port9,           leftMotor,     tmotorNormal, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//


/*----------------------------------------------------------------------------------------------------*\
|*                              - Forward for Distance with Encoders -                                *|
|*                                      ROBOTC on VEX 2.0 CORTEX                                      *|
|*                                                                                                    *|
|*  This program instructs the robot to move forward for 5 rotations of the left shaft encoder.       *|
|*                                                                                                    *|
|*                                        ROBOT CONFIGURATION                                         *|
|*    NOTES:                                                                                          *|
|*    1)  Reversing 'rightMotor' (port 2) in the "Motors and Sensors Setup" is needed with the        *|
|*        "Squarebot" model, but may not be needed for all robot configurations.                      *|
|*    2)  Whichever encoder is being used for feedback should be cleared just before it starts        *|
|*        counting by using the "SensorValue(encoder) = 0;".  This helps ensure consistancy.          *|
|*                                                                                                    *|
|*    MOTORS & SENSORS:                                                                               *|
|*    [I/O Port]          [Name]              [Type]                [Description]                     *|
|*    Motor   - Port 2    rightMotor          VEX 3-wire module     Right side motor                  *|
|*    Motor   - Port 9    leftMotor           VEX 3-wire module     Left side motor                   *|
|*    Digital - Port 5,6  rightEncoder        VEX Shaft Encoder     Right side                        *|
|*    Digital - Port 7,8  leftEncoder         VEX Shaft Encoder     Left side                         *|
\*----------------------------------------------------------------------------------------------------*/


//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++
task main()
{
  wait1Msec(2000);  // 2 Second Delay

  //Clear Encoders
  SensorValue[rightEncoder] = 0;
  SensorValue[leftEncoder] = 0;

  while(SensorValue[rightEncoder] < 1010)  // While less than 5 rotations on the leftEncoder...
  {
    //...Move Forward
    motor[rightMotor] = 127;
    motor[leftMotor] = 70;
  }
	motor[leftMotor] = 0;
	motor[rightMotor] = 0;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
