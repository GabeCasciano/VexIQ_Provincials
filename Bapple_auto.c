#pragma config(Motor,  motor1,          armMotor1,     tmotorVexIQ, PIDControl, reversed, encoder)
#pragma config(Motor,  motor6,          armMotor2,     tmotorVexIQ, PIDControl, encoder)
#pragma config(Motor,  motor8,          Rspike,        tmotorVexIQ, PIDControl, reversed, encoder)
#pragma config(Motor,  motor9,          rightMotor,    tmotorVexIQ, PIDControl, reversed, driveRight, encoder)
#pragma config(Motor,  motor10,         leftMotor,     tmotorVexIQ, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motor11,         Lspike,        tmotorVexIQ, PIDControl, reversed, encoder)
#include "functions/PID.h"
#include "subsystems/Arm.h"
#include "functions/Conversions.h"
#include "subsystems/Drive.h"
/* gabriel caciano russian hackers and vl russian hackers have hacked this thingyyyyyyyyyyyyyyyy */
/* header warning: 18 = Arm 19 = Conversions 20 = Drive 17 = PID */

task main()
{



}
