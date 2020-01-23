
//define states either as enum or constants
#define DIAGNOSTICS_CHECKING 0
#define POSSIBLE_NEED_FOR_CONTROL 1
#define HELP_NEEDED 2
#define PID_WORKING 3
#define PROCESS_HEATER_DATASEND 4
#define LOW_PASS_FILTERING 5
unsigned char diagnostics_needed_detected=0;
unsigned char maintenance_needed_detected=0;
unsigned char pid_working_detected=0;
unsigned char datasend_detected=0;
unsigned char datafiltering_detected=0;
//***********************************************************************
// The function requires some sense of time. In this example we use
// system time accessible with millis() call. Of course, something somewhere
// must keep this value updated.
//***********************************************************************
void pid_control(void)
{
        // In C language, static local variables keep their value over successive calls.
        // Normally, local values are created in stack, 
        // so they exist only during function call and are recreated at next call.
        // Static local variables are allocated in global memory, 
        // but their visibility is limited into function scope.
        static unsigned char process_state=PID_WORKING;
        static unsigned long entry_time;
        static unsigned long autorepeat_time;
		bool contact_maintenance_server;
		bool Error_led;
        
        switch(process_state){
                case DIAGNOSTICS_CHECKING:
                        if(no_error)
                        {
                                entry_time = millis();
                                process_state = POSSIBLE_NEED_FOR_CONTROL;
                        }
                        break;
                case POSSIBLE_NEED_FOR_CONTROL:
                        if(possible_error_detected)
                        {
                                process_state = DIAGNOSTICS_NEEDED;
                        }
                        else if
                        {
                                diagnostics_needed_detected++;
                                process_state = HELP_NEEDED;
                        }
                        break;
				case HELP_NEEDED:
						if(error_detected)
						{
							contact_maintenance_server = 1;
							Error_led = 1;
						}
						else if(millis()-entry_time>25)
						{
							autorepeat_time = millis();
                            maintenance needed_detected++;
                            process_state = MAINTENANCE ;
						}
						
                case PID_WORKING:
			
						if(Process_heater_control_normal)
						{	
							process_state = WORKING_NORMALLY;
						}
						else if(millis()-entry_time>20)
						{
							autorepeat_time = millis();
							pid_working_detected++;
							process_state = PID_WORKING;
						}
						break;
				case PROCESS_HEATER_DATASEND:
						if(datasends)
						{
							process_state = PID_WORKING;
						}
						else if(millis()-entry_time>5)
						{
							autorepeat_time = millis();
							datasend_detected++;
							process_state = PROCESS_HEATER_DATASEND;
						}	
			
						break;
				case LOW_PASS_FILTERING:
						if(filtering)
						{
							process_state = LOW_PASS_FILTERING;
						}
						else if(millis()-entry_time>200)
						{
							autorepeat_time = millis();
							datafiltering_detected++;
							process_state = LOW_PASS_FILTERING;
						}	
			
						break;
        }
}