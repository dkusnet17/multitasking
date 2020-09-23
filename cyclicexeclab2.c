#include <Arduino.h>

#define FRAMES 4
#define MINOR_CYCLE 10

void Task1();
void Task2();
void Task3();

void setup() {
	// put your setup code here, to run once:
	pinMode(0, OUTPUT);
}

void loop() {
	// put your main code here, to run repeatedly:

	unsigned char frame=0;
	unsigned long next_frame_start_time=10;
	while(1) {
		while( millis() < next_frame_start_time );
		next_frame_start_time += MINOR_CYCLE;
		switch(frame) {
			case 0:
			Task1();
			Task2();
			break;
			case 1:
			Task1();
			Task3();
			break;
			case 2:
			Task1();
			Task2();
			break;
			case 3:
			Task1();
			break;
		}
		frame = (frame + 1) % FRAMES;
	}
}

void Task1(){
	digitalWrite(0,HIGH);
	delay(1);
	digitalWrite(0,LOW);
}

void Task2(){
	digitalWrite(0,HIGH);
	delay(2);
	digitalWrite(0,LOW);
}

void Task3(){
	digitalWrite(0,HIGH);
	delay(3);
	digitalWrite(0,LOW);
}

/*
Times from the oscilloscope:
high 3,0 ms, task1 + task2 10,2 ms
high 4,0 ms + high 1,0 ms = 5,0 ms:  task1 + tak3 10,2 ms
...
*/