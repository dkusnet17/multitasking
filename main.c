/****************************************************************************
* Simple FreeRTOS application demo / JPP 27022020
*
* Implements two tasks each blinking a led.
* 
****************************************************************************/
#include <avr/io.h> 
#include <util/delay.h>

/* FreeRTOS include files are located in FreeRTOS/source/include, which must be set as an additional
   include path in project */

#include "FreeRTOS.h"
#include "task.h"
#include "croutine.h"

// in FreeRTOS, higher priority value means higher priority 
// Number of available priorities is fixed in FreeRTOSConfig.h : configMAX_PRIORITIES
#define mainPRIOHIGH			( tskIDLE_PRIORITY + 3 )
#define mainPRIOLOW				( tskIDLE_PRIORITY + 1 )
#define mainPRIOTEST				( tskIDLE_PRIORITY + 2 )

static void vTestTask1( void *pvParameters );
static void vTestTask2( void *pvParameters );
static void vTestTask3( void *pvParameters );

#define mainTASK1_LED 0x01
#define mainTASK2_LED 0x02
#define mainTASK3_LED 0x04

int main( void )
{
    DDRC |= (mainTASK1_LED + mainTASK2_LED + mainTASK3_LED);
    // create tasks and start scheduler
	xTaskCreate( vTestTask1, ( const char * ) "T1", 255, (void *)('1'), mainPRIOHIGH, NULL );
	xTaskCreate( vTestTask2, ( const char * ) "T2", 255, (void *)('2'), mainPRIOLOW, NULL );
	xTaskCreate( vTestTask3, ( const char * ) "T3", 255, (void *)('3'), mainPRIOTEST, NULL );
	vTaskStartScheduler();
	return 0;
}

#define mainTASK1_LED 0x01
#define mainTASK2_LED 0x02
#define mainTASK3_LED 0x04

static void vTestTask1( void *pvParameters )
{	
    while(1)
	{
		PORTC ^= mainTASK1_LED;
        vTaskDelay( 15 ); 
		//value above means number of OS ticks, and tick rate is defined in FreeRTOSConfig.h : configTICK_RATE_HZ
	}
}

static void vTestTask2( void *pvParameters )
{
    while(1)
    {
	    PORTC ^= mainTASK2_LED;
	    vTaskDelay( 25 );
    }
}

static void vTestTask3( void *pvParameters )
{
	while(1)
	{
		PORTC ^= mainTASK3_LED;
		vTaskDelay( 35 );
	}
}

