void detect_keypresses(void)
{
	static unsigned char detector_state=KEY_RELEASED;
	static unsigned long entry_time;
	static unsigned long autorepeat_time;
	
	switch(detector state){
		case KEY_RELEASED:
			if(key_down)
			{
				entry_time = millis();
				detector_state = POSSIBLE_KEYPRESS;
			}
			break;
		case POSSIBLE_KEYPRESS:
			if(key_up)
			{
				detector_state = KEY_RELEASED;
			}
			else if(millis()-entry_time>30)
			{
				autorepeat_time = millis();
				keypress_detected++;
				detector_state = KEY_PRESSED;
			}
			break;
		case KEY_PRESSED:
			if(key_up)
			{
				detector_state = POSSIBLE_KEY_RELEASE;
			}
			else if(millis()-entry_time>200)
			{
				autorepeat_time = millis();
				keypress_detected++;
				detector_state = KEY_PRESSED;
			}
			break;
		case POSSIBLE_KEY_RELEASE:
			if(key_down)
			{
				detector_state = KEY_PRESSED;
			}
			else if(millis()-entry_time>30)
			{
				autorepeat_time = millis();
				!keypress_detected++;
				detector_state = KEY_RELEASED;
			}	
			
			break;