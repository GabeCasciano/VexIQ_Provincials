#include "../functions/PID.h"

#define drive_Kp 1
#define drive_Ki 0
#define drive_Kd 0

typedef struct{
	int leftPort, rightPort, gyroPort;

	PID_constants leftConst, rightConst, gyroConst;
	PID_values leftVals, rightVals, gyroVals;

	int wheelDiameter, index;

	bool isAuto;
}drive_values *driveVals;

void setGyroPort(int gyro){
	driveVals->gyroPort = gyro;
}

void updateGyro(){
	driveVals->gyroVals->input = getGyroDegrees(driveVals->gyroPort);
}

void updateMotorEncoders(){
	driveVals->leftVals->input = getMotorEncoder(driveVals->leftPort);
	driveVals->rightVals->input = getMotorEncoder(driveVals->rightPort);
}

void updateMotorOutput(){
	motor[driveVals->leftPort] = driveVals->leftVals->output;
	motor[driveVals->rightPort] = driveVals->rightVals->output;
}

void followPath(int path[][], int len1){

	driveVals->leftVals->target = path[driveVals->index];
	driveVals->rightVals->target = path[driveVals->index];

	updateMotorEncoders(driveVals);

	if(calculate(driveVals->leftConst, driveVals->leftVals) && calculate(driveVals->rightConst, driveVals->rightVals))
		index++;

	updateMotorOutput(driveVals);
}

void driveStraight(int distance){

}

void rotateInPlace(int degRotation){

}

void driveArc(int radius, int degRotation){

}

void driveInit(int leftPort, int rightPort, bool auto){
	driveVals->leftPort = leftPort;
	driveVals->rightPort = rightPort;
	driveVals->isAuto = auto;

	if(auto)

}
