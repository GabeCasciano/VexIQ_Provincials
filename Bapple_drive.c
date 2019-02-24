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
	84,88,92,96,100,100,100,100,100,100,100
};

int ArcadeOMapNurbo[101] = {0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	10,10,10,10,10,10,10,10,10,10,
	10,10,10,10,10,10,10,10,10,10,
	20,20,20,20,20,20,20,20,20,20,
	20,20,20,20,20,20,20,20,20,20,
	20,20,20,20,20,20,20,20,20,20,
	30,30,30,30,30,30,30,30,30,30,
	30,30,30,30,30,30,30,30,30,30,
	40,40,40,40,40,40,40,40,40,40,40
};



task main(){

	//Spk def.
	spik->Lspiker = 3;
	spik->Rspiker = 3;
	spik->yesL = true;
	spik->yesL2 = true;
	spik->yesR = true;
	spik->yesR2 = true;
	spik->spikes = Nothing;

	//cntrl def	cntrl->x = 0;
	cntrl->y = 0;
	cntrl->left = 0;
	cntrl->right = 0;
	cntrl->arms = Nothing;
	cntrl->speed = Fast;
	cntrl->TURBO = OK;

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
			cntrl->speed = Fast;
		}else if(abs(getMotorEncoder(Lspike)) || abs(getMotorEncoder(Rspike)) >= 51){
			cntrl->speed = Slow;
		}

		if(vexRT[ChD] >= 50){
			cntrl->arms = lvl3;
			setMotorTarget(armMotor1, cntrl->arms, 127);
			setMotorTarget(armMotor2, cntrl->arms, 127);
		}
		if(vexRT[ChD] <= -50){
			cntrl->arms = lvl2;
			setMotorTarget(armMotor1, cntrl->arms, 127);
			setMotorTarget(armMotor2, cntrl->arms, 127);
		}

		//bottom
		if(vexRT[BtnEDown] == 1){
			cntrl->arms = BTOM;
			setMotorTarget(armMotor1, cntrl->arms, 127);
			setMotorTarget(armMotor2, cntrl->arms, 127);
		}//yellow
		if(vexRT[BtnEUp] == 1){
			cntrl->arms = YELO;
			setMotorTarget(armMotor1, cntrl->arms, 127);
			setMotorTarget(armMotor2, cntrl->arms, 127);
		}//top
		if(vexRT[BtnFUp] == 1){
			cntrl->arms = TOP;
			setMotorTarget(armMotor1, cntrl->arms, 127);
			setMotorTarget(armMotor2, cntrl->arms, 127);
		}

		//back
		if(vexRT[BtnFDown] == 1){
			cntrl->arms = BARM;
			moveMotorTarget(armMotor1, cntrl->arms, 127);
			moveMotorTarget(armMotor2, cntrl->arms, 127);
			setMotorSpeed(leftMotor, -30);
			setMotorSpeed(rightMotor, -30);
			wait1Msec(600);
		}

		//left spike down aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
		if(vexRT[BtnLDown] == 1){
			if(spik->yesL == true){
				if(spik->Lspiker == 1){
					spik->spikes = Spike2;
					setMotorTarget(Lspike, abs(spik->spikes), 100);
					spik->Lspiker = 2;
				}
				else if(spik->Lspiker == 2){
					spik->spikes = Spike3;
					setMotorTarget(Lspike, spik->spikes, 100);
					spik->Lspiker = 3;
				}
				else if(spik->Lspiker == 3){
					spik->spikes = Spike2;
					setMotorTarget(Lspike, abs(spik->spikes), 100);
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
				spik->spikes = Spike1;
				if(spik->Lspiker == 1){
					setMotorTarget(Lspike, abs(spik->spikes), 100);
					spik->Lspiker = 1;
				}
				if(spik->Lspiker == 2){
					spik->spikes = Spike1;
					setMotorTarget(Lspike, abs(spik->spikes), 100);
					spik->Rspiker = 1;
				}
				if(spik->Lspiker == 3){
					spik->spikes = Spike1;
					setMotorTarget(Lspike, abs(spik->spikes), 100);
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
					spik->spikes = Spike2;
					setMotorTarget(Rspike, spik->spikes, 100);
					spik->Rspiker = 2;
				}
				else if(spik->Rspiker == 2){
					spik->spikes = Spike3;
					setMotorTarget(Rspike, spik->spikes, 100);
					spik->Rspiker = 3;
				}
				else if(spik->Rspiker == 3){
					spik->spikes = Spike2;
					setMotorTarget(Rspike, spik->spikes, 100);
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
				spik->spikes = Spike1;
				if(spik->Rspiker == 1){
					setMotorTarget(Rspike, spik->spikes, 100);
					spik->Rspiker = 1;
				}
				if(spik->Rspiker == 2){
					setMotorTarget(Rspike, spik->spikes, 100);
					spik->Rspiker = 1;
				}
				if(spik->Rspiker == 3){
					setMotorTarget(Rspike, spik->spikes, 100);
					spik->Rspiker = 1;
				}
				spik->yesR2 = false;
			}
		}else{
			spik->yesR2 = true;
		}

		//resetting stuffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff
		cntrl->arms = Nothing;
		spik->spikes = Nothing;

	}

}
//russian hackers russian hackers russian hackers russian hackers russian hackers russian hackers russian hackers russian hackers russian hackers russian hackers russian hackers russian hackers russian hackers russian hackers russian hackers russian hackers russian hackers russian hackers russian hackers russian hackers russian hackers russian hackers russian hackers russian hackers russian hackers russian hackers russian hackers russian hackers russian hackers russian hackers russian hackers russian hackers russian hackers russian hackers*
//russian hackers *heart*
