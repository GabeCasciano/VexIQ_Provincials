#pragma config(Motor,  motor1,          armMotor2,     tmotorVexIQ, PIDControl, reversed, encoder)
#pragma config(Motor,  motor6,          armMotor1,     tmotorVexIQ, PIDControl, encoder)
#pragma config(Motor,  motor8,          rightCatchMotor, tmotorVexIQ, PIDControl, encoder)
#pragma config(Motor,  motor9,          rightMotor,    tmotorVexIQ, PIDControl, reversed, driveRight, encoder)
#pragma config(Motor,  motor10,         leftMotor,     tmotorVexIQ, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motor11,         leftCatchMotor, tmotorVexIQ, PIDControl, reversed, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "functions/PID.h"
#include "subsystems/Drive.h"

driveInit(10, 9, true);

void screen(int index){
	displayTextLine(0,"Current State: %d", index);
	displayTextLine(1,"Drive Position (L&R): %d %d", getMotorEncoder(leftMotor), getMotorEncoder(rightMotor));
	displayTextLine(2,"Arm Location: %d", getMotorEncoder(armMotor1));
	displayTextLine(3,"Catcher Location (L&R): %d %d", getMotorEncoder(leftCatchMotor), getMotorEncoder(rightCatchMotor));
}

task main()
{
	int index = 0;
	isAuto = true;

	while(isAuto){
		screen(index);
		switch(index){
			case 0: //drive a little bit
				if(driveStraight(100)){
					resetValues(driveVals->leftVals);
					resetValues(driveVals->rightVals);
					index++;
				}
				break;
			case 1: //turn 90 deg right
				if(rotateInPlace(90)){
					resetValues(driveVals->gyroVals);
					index++;
				}
				break;
			case 2: //drive straight more
				if(driveStraight(1000)){
					resetValues(driveVals->leftVals);
					resetValues(driveVals->rightVals);
					index++;
				}
				break;
			case 3: //1st hub & claws up
				break;
			case 4: //grab hubs
				break;
			case 5: //reverse accross field
				break;
			default:
					displayTextLine(0, "Incorrect state");
					isAuto = false;
				break
		}
	}
}
