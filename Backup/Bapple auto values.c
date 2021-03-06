#pragma config(Sensor, port2,  Bump,           sensorVexIQ_Touch)
#pragma config(Sensor, port3,  Gyro,           sensorVexIQ_Gyro)
#pragma config(Motor,  motor1,          armMotor1,     tmotorVexIQ, PIDControl, reversed, driveLeft, encoder)
#pragma config(Motor,  motor6,          armMotor2,     tmotorNone, openLoop)
#pragma config(Motor,  motor8,          Rspike,        tmotorVexIQ, PIDControl, encoder)
#pragma config(Motor,  motor9,          rightmotor,    tmotorVexIQ, PIDControl, reversed, encoder)
#pragma config(Motor,  motor10,         Lspike,        tmotorVexIQ, PIDControl, encoder)
#pragma config(Motor,  motor11,         leftmotor,     tmotorVexIQ, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//reset motors in between motions
void resetMotor(){
	resetMotorEncoder(leftMotor);
	resetMotorEncoder(rightMotor);
	resetMotorEncoder(armMotor1);
	resetMotorEncoder(armMotor2);
	resetMotorEncoder(Lspike);
	resetMotorEncoder(Rspike);
}//raise arm and spikes then turn
void motion1(){
	setMotorTarget(armMotor1, 760, 127);
	setMotorTarget(armMotor2, 760, 127);
	setMotorTarget(Lspike, -286, 127);
	setMotorTarget(Rspike, 260, 127);
	waitUntilMotorStop(armMotor1);
	setMotorTarget(rightmotor, 91, 100);
	setMotorTarget(leftmotor, -44, 100);
	waitUntilMotorStop(rightmotor);
}//get bonus hub
void motion2(){
	setMotorTarget(leftmotor, 240, 50);
	setMotorTarget(rightmotor, 240, 50);
	waitUntilMotorStop(rightmotor);
	setMotorTarget(armMotor1, 117, 127);
	setMotorTarget(armMotor2, 117, 127);
	waitUntilMotorStop(armMotor1);
}	//move back
void motion3(){
	setMotorTarget(rightmotor, -200, 80);
	setMotorTarget(leftmotor, -190, 80);
	wait1Msec(500);
}//turn left
void motion4(){
	setMotorTarget(rightmotor, 75, 60);
	setMotorTarget(leftmotor, -75, 60);
	waitUntilMotorStop(rightmotor);
}//move forward
void motion5(){
	setMotorTarget(rightmotor, 555, 70);
	setMotorTarget(leftmotor, 555, 70);
	waitUntilMotorStop(leftmotor);
}//turn to oranges
void motion6(){
	setMotorTarget(rightmotor, -170, 70);
	setMotorTarget(leftmotor, 170, 70);
	wait1Msec(600);
}//move with orange hubs to the square
void motion7(){
	setMotorTarget(rightmotor, 780, 55);
	setMotorTarget(leftmotor, 780, 55);
	waitUntilMotorStop(rightmotor);
}//turn to square
void motion8(){
	setMotorTarget(rightmotor, 120, 80);
	setMotorTarget(leftmotor, -120, 80);
	wait1Msec(600);
}//push to square
void motion9(){
	setMotorTarget(rightmotor, 300,120);
	setMotorTarget(leftmotor, 300, 120);
	wait1Msec(400);
}
task main(){
 	motion1();
	resetMotor();
	motion2();
	resetMotor();
	motion3();
	resetMotor();
	motion4();
	resetMotor();
	motion5();
	resetMotor();
	motion6();
	resetMotor();
	motion7();
	resetMotor();
	motion8();
	resetMotor();
	motion9();
	resetMotor();
}
