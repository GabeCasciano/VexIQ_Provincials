#pragma config(Sensor, port2,  Compass,           sensorVexIQ_Gyro)
#pragma config(Sensor, port3,  RGB,        sensorVexIQ_LED)
#pragma config(Motor,  motor1,          armMotor1,     tmotorVexIQ, PIDControl, encoder)
#pragma config(Motor,  motor6,          armMotor2,     tmotorVexIQ, PIDControl, encoder)
#pragma config(Motor,  motor8,          Rspike,        tmotorVexIQ, PIDControl, encoder)
#pragma config(Motor,  motor9,          rightMotor,    tmotorVexIQ, PIDControl, reversed, driveRight, encoder)
#pragma config(Motor,  motor10,         leftMotor,     tmotorVexIQ, PIDControl, reversed, encoder)
#pragma config(Motor,  motor11,         Lspike,        tmotorVexIQ, PIDControl, driveLeft, encoder)

#include "functions/PID.h"
#include "functions/Conversions.h"
/* #include "subsystems/Arm.h
/* #include "subsystems/Drive.h"
/* gabriel caciano russian hackers and vl russian hackers have hacked this thingyyyyyyyyyyyyyyyy */
/* this is the actual autonomous not a copy */
/* header def
17 = PID
18 = Conversions
19 = Motions
*/

//Written by: Vincent liu
//Motion functions



typedef struct{//contains the constants for the PID calculation
	int Kp, Kd, Ki;
}PID_constants;

typedef struct{//contains the values calculated or set by the PID calculation
	int error, target, output, accum, previous, input, calc, multiplier;
	bool mult;
}PID_values;

void init(PID_constants *constants, int kp, int ki, int kd){
	constants->Kp = kp;
	constants->Ki = ki;
	constants->Kd = kd;
}

bool calculate(PID_constants *constants, PID_values *values){
	values->error = values->target - values->input;
	values->accum += values->error;
	values->calc = (constants->Kp * values->error) + (constants->Ki * values->accum) + (constants->Kd * (values->error - values->previous));
	values->output = values->calc * values->multiplier;
	values->previous = values->error;
	if(stoop == true){
		values->output = 0;
	}
	if(abs(values->error) < 5){
		values->output = 0;
		return true;
	}
	return false;
}

void resetValues(PID_values *values){
	values->error = 0;
	values->target = 0;
	values->output = 0;
	values->accum = 0;
	values->previous = 0;
	values->input = 0;
}

void setNewTarget(PID_values *vals, int target){
	vals->target = target;
	resetValues(vals);
}

float ticksToLinearDistance(int ticks, float diameter){
	return (ticks/ticksPerRotation) * PI * diameter;
}

float ticksToDegrees(int ticks){
	return (ticks/ticksPerRotation) * 360;
}

float ticksToRotations(int ticks){
	return (ticks/ticksPerRotation);
}

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

	resetValues(&driveValues);
}

//example of how to use
/*
void example(){
	drive(value);
	goes forward and backward
	Lturn(degrees); always make sure sure that this number is negative
	turns left
	Rturn(degrees); this one should be positive
		turns right
	Lspiker(value);
	moves left spike up/down
	Rspiker(value);
	moves right spike
	Arm(value);
	moves the arm catch stuff
}
*/

task main(){

	Arm(760);
/*	Lspiker(286);
	Rspiker(286);
	Lturn(-60);
	waitUntilMotorStop(armMotor1); */
	waitUntil(SensorValue[RGB] == 0);

}
