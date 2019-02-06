//Written by: Gabriel Casciano
//Conversion Functions

#define ticksPerRotation 960

float ticksToLinearDistance(int ticks, float diameter){
	return (ticks/ticksPerRotation) * PI * diameter;
}

float tickToRotations(int ticks){
	return (ticks/ticksPerRotation) * 360;
}
