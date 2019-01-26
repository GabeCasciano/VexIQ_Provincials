typedef struct{
	double Kp, Ki, Kd;
	double *output, *input;
	double integrator, previousError;
}PID_Values;

//gabe was here
