#pragma config(Sensor, port2,  Compass,        sensorVexIQ_Gyro)
#pragma config(Sensor, port3,  RGB,            sensorVexIQ_LED)
#pragma config(Motor,  motor1,          armMotor1,     tmotorVexIQ, PIDControl, reversed, encoder)
#pragma config(Motor,  motor6,          armMotor2,     tmotorVexIQ, PIDControl, encoder)
#pragma config(Motor,  motor8,          Rspike,        tmotorVexIQ, PIDControl, reversed, encoder)
#pragma config(Motor,  motor9,          rightMotor,    tmotorVexIQ, PIDControl, reversed, driveRight, encoder)
#pragma config(Motor,  motor10,         leftMotor,     tmotorVexIQ, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motor11,         Lspike,        tmotorVexIQ, PIDControl, reversed, encoder)
//* this is reading the values for bapple *//

task main()
{

	while(true){
		displayTextLine(0, "Arm: %d %d", getMotorEncoder(armMotor1), getMotorEncoder(armMotor2));
		displayTextLine(1, "Spike: %d %d", getMotorEncoder(Lspike), getMotorEncoder(Rspike));
		displayTextLine(2, "Gyro: %d", getGyroDegrees(Compass));
		displayTextLine(3, "leftMotor: %d", getMotorEncoder(leftMotor));
		displayTextLine(4, "rightMotor: %d", getMotorEncoder(rightMotor));
	}

}
