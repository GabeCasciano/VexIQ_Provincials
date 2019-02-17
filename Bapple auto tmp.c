#pragma config(Sensor, port2,  Compass,        sensorVexIQ_Gyro)
#pragma config(Sensor, port3,  RGB,            sensorVexIQ_LED)
#pragma config(Motor,  motor1,          armMotor1,     tmotorVexIQ, PIDControl, reversed, encoder)
#pragma config(Motor,  motor6,          armMotor2,     tmotorVexIQ, PIDControl, encoder)
#pragma config(Motor,  motor8,          Rspike,        tmotorVexIQ, PIDControl, reversed, encoder)
#pragma config(Motor,  motor9,          rightMotor,    tmotorVexIQ, PIDControl, reversed, driveRight, encoder)
#pragma config(Motor,  motor10,         leftMotor,     tmotorVexIQ, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motor11,         Lspike,        tmotorVexIQ, PIDControl, reversed, encoder)
/* Vincent did not do this code to humour yoyo */

int stoop = false;

//Library
int error;
int PID(int setpoint, int Kp, int speed, int feedback){
	if(stoop == true){
		return 0;
	}
	error = setpoint - feedback;
	if(abs(error) >= 5){
		int out = Kp * error;
		if(abs(out) >= 50){
			return sgn(out) * speed;
		}
		return out;
	}
	return 0;
}

void motion(int target){
	error = target - getMotorEncoder(leftMotor);
	while(error > 5){
		motor[rightMotor] = PID(target, 1, 127, getMotorEncoder(rightMotor));
		motor[leftMotor] = PID(target, 1, 127, getMotorEncoder(leftMotor));
	}
	motor[leftMotor] = 0;
		motor[rightMotor] = 0;
}

void turn(int angle){
	error = angle - getGyroDegrees(Compass);
	while((abs(error)) > 5){
		int power = PID(angle, 1, 40, getGyroDegrees(Compass));
		motor[leftMotor] = power;
		motor[rightMotor] = -power;
		writeDebugStreamLine(" output = %d error = %d", power, error);
	}
	motor[leftMotor] = 0;
		motor[rightMotor] = 0;
}

void lspiker(int lspik){
	error = lspik - getMotorEncoder(Lspike);
	while(error > 5){
		motor[leftMotor] = PID(lspik, 1, 120, getMotorEncoder(Lspike));
	}
}

void rspiker(int rspik){
	error = rspik - getMotorEncoder(Rspike);
	while(error > 5){
		motor[Rspike] = PID(rspik, 1, 120, getMotorEncoder(Rspike));
	}
}

void arm(int armi){
	error = armi - getMotorEncoder(armMotor1);
	while(error > 5){
		motor[armMotor1] = PID(armi, 1, 120, getMotorEncoder(armMotor1));
		motor[armMotor2] = PID(armi, 1, 120, getMotorEncoder(armMotor2));
	}
}

/* void example(){
	motion(how many degrees per motor); moves forward/backward
	turn(what angle to go to); turns left/right
	lspiker(); moves left spike
	rspiker(-180); moves right spike
	arm(50); moves arm up/down
} */

void reset(){
	resetMotorEncoder(leftMotor);
	resetMotorEncoder(rightMotor);
	resetMotorEncoder(armMotor1);
	resetMotorEncoder(armMotor2);
	resetMotorEncoder(Lspike);
	resetMotorEncoder(Rspike);
	resetGyro(Compass);
}


//this is for when you want to move the bot and wait for the rgb reference this void:
void stopp(){
	stoop = true;
	while(stoop == true){
		if(getTouchLEDValue(RGB) == 1){
			stoop = false;
		}else{
			stoop = true;
		}
	}
}
/* how to use stopp or wait
wait();
waitUntil(stoop = false);
*/

//this one is for if you need to wait a specific time:
void wait(int numTicks){
	//FYI 1 tick = 1 milsec
	stoop = true;
	int waiting;
	for(waiting = 0; waiting <= numTicks + 1; waiting++){
		if(waiting >= numTicks){
			stoop = false;
		}else{
			stoop = true;
		}
		wait1Msec(1);
	}
}


//Motions
void motion1(){
	motion(100);
	waitUntilMotorStop(rightMotor);
	turn(-45);
	waitUntilMotorStop(rightMotor);
	lspiker(-400);
	rspiker(400);
	waitUntilMotorStop(Lspike);
}

void motion2(){
}

task main(){

	reset();
	motion1();
	reset();
	motion2();
	reset();

}
