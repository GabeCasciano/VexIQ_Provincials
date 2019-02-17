#include "../functions/PID.h"

#define arm_Kp 1.0
#define arm_Ki 0
#define arm_Kd 0

#define catcher_Kp 1.0
#define catcher_Ki 0
#define catcher_Kd 0

typedef struct{
	int motor1Port, motor2Port;
	int currentLocation, targetLocation;
	PID_constants armConstants;
	PID_values armValues;
}ARM_VALUES;

typedef struct{
	int leftCatcherPort, rightCatcherPort;
	int currentLocationLeft, currentLocationRight, targetLocationLeft, targetLocationRight;
	PID_constants leftConstants, rightConstants;
	PID_values leftValues, rightValues;
}CATCHER_VALUES;
