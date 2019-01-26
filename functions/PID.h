typedef struct{
	int Kp, Kd, Ki;
}PID_constants;

typedef struct{
	int error, target, output, accum, previous, input;
}PID_values;

void calculate(PID_constants *constants, PID_values *values, ){
	values->error = values->target - values->input;
	values->accum += values->error;
	values->output = (constants->Kp * values->error) + (constants->Ki * values->accum) + (constants->Kd * (values->previous - values->error));
	values->previous = values->error;
	if(abs(values->error) < 5)
		values->output = 0;
}
void resetValues(PID_values *values){
	values->error = 0;
	values->target = 0;
	values->output = 0;
	values->accum = 0;
	values->previous = 0;
	values->input = 0;
}
