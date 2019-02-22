
/*Written by: Gabriel Casciano
PID base function, requires the use of the PID_constants & PID_values structs*/

/*Use this function to initialize the PID_constants struct within the main function.

	Parameters:
		*constants -> structure containing the PID constants, PID_constants pointer;
		kp -> kp constant, integer;
		ki -> ki constant, integer;
		kd -> kd constant, integer;
*/


/*Use this function to calculate the PID

	Parameters:
		*constants -> structure containing the PID constants, PID_constants pointer;
		*values -> structure containing the PID values, PID_values pointer;

	Return:
		bool -> true if the error is within 5 of the target, false otherwise;
*/
int stoop = false;
bool mult = true;
/*Use this function to reset the PID values before performing a new series of calculation

	Parameters:
		*values -> structure containing the PID values, PID_values pointer;
*/

/*Use this function to set a new target

	Parameters:
		*vals -> structure containing the PID values, PID_values pointer;
		target -> the new target to calculate for, integer;
*/
