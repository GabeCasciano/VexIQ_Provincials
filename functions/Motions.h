#include "Functions/PID.h"
//Written by: Vincent liu
//Motion functions

int placeholder;

PID_constants driveConstants;
PID_values driveValues;

void drinput(){
	driveValues.input = getMotorEncoder(leftMotor);
}
void Tinput(){
	driveValues.input = getGyroDegrees(Compass);
}
void Linput(){
	driveValues.input = getMotorEncoder(Lspike);
}
void Rinput(){
	driveValues.input = getMotorEncoder(Rspike);
}
void Arinput(){
	driveValues.input = getMotorEncoder(armMotor1);
}

void drive(int target){
	init(&driveConstants, 1.0, 0, 0);
	setNewTarget(&driveValues, target);

	drinput();

	while(!calculate(&driveConstants, &driveValues)){
		motor[leftMotor] = driveValues.output;
		motor[rightMotor] = driveValues.output;
		drinput();
	}

	resetValues(driveValues);
}

void Lturn(int Langle){
	init(&driveConstants, 1.0, 1.0, 0);
	setNewTarget(&driveValues, Langle);

	int Lout = driveValues.output;

	Tinput();

	while(!calculate(&driveConstants, &driveValues)){
		motor[leftMotor] = -Lout;
		motor[rightMotor] = Lout;
		Tinput();
	}

	resetValues(driveValues);
}
void Rturn(int Rangle){
	init(&driveConstants, 1.0, 1.0, 0);
	setNewTarget(&driveValues, Rangle);

	int Rout = driveValues.output;

	Tinput();

	while(!calculate(&driveConstants, &driveValues)){
		motor[leftMotor] = Rout;
		motor[rightMotor] = -Rout;
		Tinput();
	}

	resetValues(driveValues);
}
void Lspiker(int lspik){
	init(&driveConstants, 1.0, 0, 1.0);
	setNewTarget(&driveValues, lspik);

	Linput();

	while(!calculate(&driveConstants, &driveValues)){
		motor[Lspike] = driveValues.output;
		Linput();
	}

	resetValues(driveValues);
}
void Rspiker(int rspik){
	init(&driveConstants, 1.0, 0, 1.0);
	setNewTarget(&driveValues, rspik);

	Rinput();

	while(!calculate(&driveConstants, &driveValues)){
		motor[Rspike] = driveValues.output;
		Rinput();
	}

	resetValues(driveValues);
}
void Arm(int armi){
	init(&driveConstants, 1.0, 0, 1.0);
	setNewTarget(&driveValues, armi);

	Arinput();

	while(!calculate(&driveConstants, &driveValues)){
		motor[armMotor1] = driveValues.output;
		motor[armMotor2] = driveValues.output;
		Arinput();
	}

	resetValues(driveValues);
}

//example of how to use
/*
void example(){
	drive(value);
	goes forward and backward
	Lturn(degrees); always make sure sure that this number is positive
	turns left
	Rturn(degrees); this one should be positive too
	turns right
	Lspiker(value);
	moves left spike up/down
	Rspiker(value);
	moves right spike
	Arm(value);
	moves the arm catch stuff
}
*/
