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
/* #include "subsystems/Drive.h"
/* gabriel caciano russian hackers and vl russian hackers have hacked this thingyyyyyyyyyyyyyyyy */
/* header def
18 = Arm
19 = Conversions
20 = Drive
17 = PID
*/

PID_constants driveConstants;
PID_values driveValues;



void drive(int target){
	init(&driveConstants, 1.0, 0, 0);
	setNewTarget(&driveValues, target);

	while(!calculate(&driveConstants, &driveValues)){
		motor[leftMotor] = driveValues.output;
		motor[rightMotor] = driveValues.output;
	}

	resetValues(driveValues);
}

task main(){



}
