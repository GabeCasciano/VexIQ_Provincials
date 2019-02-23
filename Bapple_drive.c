#pragma config(Sensor, port2,  Compass,        sensorVexIQ_Gyro)
#pragma config(Sensor, port3,  RGB,            sensorVexIQ_LED)
#pragma config(Motor,  motor1,          armMotor1,     tmotorVexIQ, PIDControl, reversed, encoder)
#pragma config(Motor,  motor6,          armMotor2,     tmotorVexIQ, PIDControl, encoder)
#pragma config(Motor,  motor8,          Rspike,        tmotorVexIQ, PIDControl, reversed, encoder)
#pragma config(Motor,  motor9,          rightMotor,    tmotorVexIQ, PIDControl, reversed, driveRight, encoder)
#pragma config(Motor,  motor10,         leftMotor,     tmotorVexIQ, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motor11,         Lspike,        tmotorVexIQ, PIDControl, reversed, encoder)

#include "functions/Drive_Structs.h"
/* Written, coded, and debugged by Vincent liu */

//int A, B;
//int left, right;
//A = getjoystickvalue(ChA);
//B = getjoystickvalue(ChB);
//left = A + B;
//right = A - B;
//motor[leftmotor] = left*0.9;
//motor[rightmotor] = right*0.9;


int calculate(int lik, int rik){
	values->lspik = lik;
	values->rspik = rik;
	if(abs(values->lspik) || abs(values->rspik) <= 50){
		values->Sped = true;
	}else if(abs(values->lspik) || abs(values->rspik) >= 51){
		values->Sped = false;
	}
	if(values->Sped == true){
		values->mult = 1;
	}else if(values->Sped == false){
		values->mult = 0.7;
	}
	return values->mult;
}

//arcade o
int ArcadeOMapTurbo[101] = {
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	10,10,10,10,10,10,10,10,10,10,
	10,10,10,10,10,10,10,10,10,10,
	20,20,20,20,20,20,20,20,20,20,
	30,30,30,30,30,30,30,30,30,30,
	40,40,40,40,40,40,40,40,40,40,
	50,50,50,50,50,50,50,50,50,50,
	60,62,64,66,68,70,72,74,76,78,
	84,88,92,96,100,100,100,100,100,100,100};

int ArcadeOMapNurbo[101] = {0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	10,10,10,10,10,10,10,10,10,10,
	10,10,10,10,10,10,10,10,10,10,
	20,20,20,20,20,20,20,20,20,20,
	20,20,20,20,20,20,20,20,20,20,
	20,20,20,20,20,20,20,20,20,20,
	30,30,30,30,30,30,30,30,30,30,
	30,30,30,30,30,30,30,30,30,30,
	40,40,40,40,40,40,40,40,40,40,40};

enum arm_def {Nothing, BTOM = 0, YELO = 790, TOP = 934, BARM = -140, lvl2 = 380, lvl3 = 590};
enum spike_def {Nothing, Spike1 = -280, Spike2 = -130, Spike3 = 0};
enum TN_urbo {Turbo, Nurbo};

arm_def arms = Nothing;
spike_def spikes = Nothing;
TN_urbo speed = Turbo;

task main(){

	//Spk def.
	spik->Lspiker = 3;
	spik->Rspiker = 3;
	spik->yesL = true;
	spik->yesL2 = true;
	spik->yesR = true;
	spik->yesR2 = true;

	//cntrl def.
	cntrl->TURBO = "Happy";
	cntrl->x = 0;
	cntrl->y = 0;
	cntrl->left = 0;
	cntrl->right = 0;

	while(true){
		//arcade r
		if(abs(vexRT[ChA]) > 15){
			cntrl->x = vexRT[ChA];
		}else{
			cntrl->x = 0;
		}

		cntrl->x = sgn(cntrl->x) * ArcadeOMapTurbo[abs(cntrl->x)];

		if(abs(vexRT[ChB]) > 15){
			cntrl->y = vexRT[ChB];
		}else{
			cntrl->y = 0;
		}

		cntrl->y = sgn(cntrl->y) * ArcadeOMapTurbo[abs(cntrl->y)] * 0.8;

		cntrl->left = cntrl->x + cntrl->y;
		cntrl->right = cntrl->x - cntrl->y;

		motor[leftMotor] = cntrl->left * calculate(getMotorEncoder(Lspike), getMotorEncoder(Rspike));
		motor[rightMotor] = cntrl->right * calculate(getMotorEncoder(Lspike), getMotorEncoder(Rspike));

		if(abs(getMotorEncoder(Lspike)) || abs(getMotorEncoder(Rspike)) <= 50){
			speed = Turbo;
		}else if(abs(getMotorEncoder(Lspike)) || abs(getMotorEncoder(Rspike)) >= 51){
			speed = Nurbo;
		}

		if(vexRT[ChD] >= 50){
			arms = lvl3;
			setMotorTarget(armMotor1, arms, 127);
			setMotorTarget(armMotor2, arms, 127);
		}
		if(vexRT[ChD] <= -50){
			arms = lvl2;
			setMotorTarget(armMotor1, arms, 127);
			setMotorTarget(armMotor2, arms, 127);
		}

		//bottom
		if(vexRT[BtnEDown] == 1){
			arms = BTOM;
			setMotorTarget(armMotor1, arms, 127);
			setMotorTarget(armMotor2, arms, 127);
		}//yellow
		if(vexRT[BtnEUp] == 1){
			arms = YELO;
			setMotorTarget(armMotor1, arms, 127);
			setMotorTarget(armMotor2, arms, 127);
		}//top
		if(vexRT[BtnFUp] == 1){
			arms = TOP;
			setMotorTarget(armMotor1, arms, 127);
			setMotorTarget(armMotor2, arms, 127);
		}

		//back
		if(vexRT[BtnFDown] == 1){
			arms = BARM;
			moveMotorTarget(armMotor1, arms, 127);
			moveMotorTarget(armMotor2, arms, 127);
			setMotorSpeed(leftMotor, -30);
			setMotorSpeed(rightMotor, -30);
			wait1Msec(600);
		}

		//left spike down aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
		if(vexRT[BtnLDown] == 1){
			if(spik->yesL == true){
				if(spik->Lspiker == 1){
					spikes = Spike2;
					setMotorTarget(Lspike, abs(spikes), 100);
					spik->Lspiker = 2;
				}
				else if(spik->Lspiker == 2){
					spikes = Spike3;
					setMotorTarget(Lspike, spikes, 100);
					spik->Lspiker = 3;
				}
				else if(spik->Lspiker == 3){
					spikes = Spike2;
					setMotorTarget(Lspike, abs(spikes), 100);
					spik->Lspiker = 2;
				}
				spik->yesL = false;
			}
		}else{
			spik->yesL = true;
		}

		//left spike up aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
		if(vexRT[BtnLUp] == 1){
			if(spik->yesL2 == true){
				spikes = Spike1;
				if(spik->Lspiker == 1){
					setMotorTarget(Lspike, abs(spikes), 100);
					spik->Lspiker = 1;
				}
				if(spik->Lspiker == 2){
					spikes = Spike1;
					setMotorTarget(Lspike, abs(spikes), 100);
					spik->Rspiker = 1;
				}
				if(spik->Lspiker == 3){
					spikes = Spike1;
					setMotorTarget(Lspike, abs(spikes), 100);
					spik->Rspiker = 1;
				}
				spik->yesL2 = false;
			}
		}else{
			spik->yesL2 = true;
		}

		//right spike down aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
		if(vexRT[BtnRDown] == 1){
			if(spik->yesR == true){
				if(spik->Rspiker == 1){
					spikes = Spike2;
					setMotorTarget(Rspike, spikes, 100);
					spik->Rspiker = 2;
				}
				else if(spik->Rspiker == 2){
					spikes = Spike3;
					setMotorTarget(Rspike, spikes, 100);
					spik->Rspiker = 3;
				}
				else if(spik->Rspiker == 3){
					spikes = Spike2;
					setMotorTarget(Rspike, spikes, 100);
					spik->Rspiker = 2;
				}
				spik->yesR = false;
			}
		}else{
			spik->yesR = true;
		}

		//right spike up aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
		if(vexRT[BtnRUp] == 1){
			if(spik->yesR2 == true){
				spikes = Spike1;
				if(spik->Rspiker == 1){
					setMotorTarget(Rspike, spikes, 100);
					spik->Rspiker = 1;
				}
				if(spik->Rspiker == 2){
					setMotorTarget(Rspike, spikes, 100);
					spik->Rspiker = 1;
				}
				if(spik->Rspiker == 3){
					setMotorTarget(Rspike, spikes, 100);
					spik->Rspiker = 1;
				}
				spik->yesR2 = false;
			}
		}else{
			spik->yesR2 = true;
		}

		//resetting stuffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff
		arms = Nothing;
		spikes = Nothing;

	}

}
//russian hackers russian hackers russian hackers russian hackers russian hackers russian hackers russian hackers russian hackers russian hackers russian hackers russian hackers russian hackers russian hackers russian hackers russian hackers russian hackers russian hackers russian hackers russian hackers russian hackers russian hackers russian hackers russian hackers russian hackers russian hackers russian hackers russian hackers russian hackers russian hackers russian hackers russian hackers russian hackers russian hackers russian hackers*
//russian hackers *heart*
