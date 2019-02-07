/*Written by: Gabriel Casciano
PID base function, requires the use of the PID_constants & PID_values structs*/

typedef struct{//contains the constants for the PID calculation
	int Kp, Kd, Ki;
}PID_constants;

typedef struct{//contains the values calculated or set by the PID calculation
	int error, target, output, accum, previous, input;
}PID_values;

/*Use this function to initialize the PID_constants struct within the main function.

	Parameters:
		*constants -> structure containing the PID constants, PID_constants pointer;
		kp -> kp constant, integer;
		ki -> ki constant, integer;
		kd -> kd constant, integer;
*/
void init(PID_constants *constants, int kp, int ki, int kd){
	constants->Kp = kp;
	constants->Ki = ki;
	constants->Kd = kd;
}

/*Use this function to calculate the PID

	Parameters:
		*constants -> structure containing the PID constants, PID_constants pointer;
		*values -> structure containing the PID values, PID_values pointer;

	Return:
		bool -> true if the error is within 5 of the target, false otherwise;
*/
bool calculate(PID_constants *constants, PID_values *values){
	values->error = values->target - values->input;
	values->accum += values->error;
	values->output = (constants->Kp * values->error) + (constants->Ki * values->accum) + (constants->Kd * (values->error - values->previous));
	values->previous = values->error;
	if(abs(values->error) < 5){
		values->output = 0;
		return true;
	}
	return false;
}

/*Use this function to reset the PID values before performing a new series of calculation

	Parameters:
		*values -> structure containing the PID values, PID_values pointer;
*/
void resetValues(PID_values *values){
	values->error = 0;
	values->target = 0;
	values->output = 0;
	values->accum = 0;
	values->previous = 0;
	values->input = 0;
}

/*Use this function to set a new target

	Parameters:
		*vals -> structure containing the PID values, PID_values pointer;
		target -> the new target to calculate for, integer;
*/
void setNewTarget(PID_values *vals, int target){
	vals->target = target;
	resetValues(vals);
}
