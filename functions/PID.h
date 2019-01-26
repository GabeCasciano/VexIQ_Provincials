
typedef struct{
	int target, deadband;
	double Kp, Ki, Kd;
	double *output, *input;
	double integrator, previousError;
}PID_Values;

bool calculatePID(PID_Values value){
	int error = value->target - values->*input;
	double proportional = Kp * error;
	double derivatie = Kd * (error - value->previousError);
	value->previousError = error;
	value->integrator += Ki * error;
	if(abs(error) > deadband)
		value->*output = proportional + derivative + 
value->integrator;
	else{
		value->*output = 0;
		return true;
	}
	return false;
}
