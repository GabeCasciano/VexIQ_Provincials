#pragma config(Sensor, port2,  Compass,        sensorVexIQ_Gyro)
#pragma config(Sensor, port3,  RGB,            sensorVexIQ_LED)
#pragma config(Motor,  motor1,          armMotor1,     tmotorVexIQ, PIDControl, reversed, encoder)
#pragma config(Motor,  motor6,          armMotor2,     tmotorVexIQ, PIDControl, encoder)
#pragma config(Motor,  motor8,          Rspike,        tmotorVexIQ, PIDControl, reversed, encoder)
#pragma config(Motor,  motor9,          rightMotor,    tmotorVexIQ, PIDControl, reversed, driveRight, encoder)
#pragma config(Motor,  motor10,         leftMotor,     tmotorVexIQ, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motor11,         Lspike,        tmotorVexIQ, PIDControl, reversed, encoder)
//* this is the actual autonomous not a copy *//
#include "functions/PID.h"
#include "functions/Conversions.h"
#include "functions/Motions.h"
/* #include "subsystems/Arm.h
/* #include "subsystems/Drive.h"
/* gabriel caciano russian hackers and vl russian hackers have hacked this thingyyyyyyyyyyyyyyyy */
/* header def
17 = PID
18 = Conversions
19 = Motions
*/


task main(){

	drive(placeholder); //forward
	waitUntilMotorStop(leftMotor);
	Lturn(placeholder); //turn left to tower
	waitUntilMotorStop(leftMotor);
	drive(placeholder); //forward to tower
	waitUntilMotorStop(leftMotor);
	Rturn(placeholder); //right a little
	waitUntilMotorStop(rightMotor);
	Arm(placeholder); //arm up to level
	waitUntilMotorStop(armMotor1);
	drive(placeholder); //forward all the way
	waitUntilMotorStop(leftMotor);
	Arm(placeholder); //take bonus
	waitUntilMotorStop(armMotor1);
	drive(placeholder); //backwards
	waitUntilMotorStop(leftMotor);
	Arm(placeholder); //arm down a little
	waitUntilMotorStop(armMotor1);
	Lturn(placeholder); //turn to other hubs
	waitUntilMotorStop(leftMotor);

}
