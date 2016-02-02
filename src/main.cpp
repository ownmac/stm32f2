/*
 * main.cpp
 *
 *  Created on: Jan 24, 2016
 *      Author: Dove
 */


/* Standard includes. */
#include <stdlib.h>
#include <string.h>
#include <stm32f30x.h>


/* Scheduler includes. */
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <semphr.h>

extern "C" char _end;
SemaphoreHandle_t xSemaphore = NULL;

//heap starts address will be changed in main after we figure the size of the stack
// this way we can avoid corruption of this var
HeapRegion_t xHeapRegions[] =
{
		{ ( uint8_t * ) 0x20000000UL, 0x9000 },
		{ NULL, 0 }
};


#define mainTASK_PRIORITY					( tskIDLE_PRIORITY + 1 )
#define mainNopIdle_PRIORITY			    ( tskIDLE_PRIORITY )



/* The 'main' task as described at the top of this file. */
static void prvMainTask1( void *pvParameters );
static void prvMainTask2( void *pvParameters );
static void prvMainTask3( void *pvParameters );
static void prvMainTask4( void *pvParameters );
/* another task */
//static void prvNOPTask( void *pvParameters );




#define LED3_ON() 	(GPIOE->BSRR |= ((uint32_t)1 << 9 ))
#define LED3_OFF()	(GPIOE->BSRR |= ((uint32_t)1 << 25 ))

#define LED10_ON() 	(GPIOE->BSRR |= ((uint32_t)1 << 13 ))
#define LED10_OFF()	(GPIOE->BSRR |= ((uint32_t)1 << 29 ))

#define LED5_ON() 	(GPIOE->BSRR |= ((uint32_t)1 << 10 ))
#define LED5_OFF()	(GPIOE->BSRR |= ((uint32_t)1 << 26 ))

#define LED9_ON() 	(GPIOE->BSRR |= ((uint32_t)1 << 12 ))
#define LED9_OFF()	(GPIOE->BSRR |= ((uint32_t)1 << 28 ))





static void prvMainTask1(void *pvParameters)
{
	TickType_t xLastExecutionTime;
	xLastExecutionTime = xTaskGetTickCount();
	uint8_t onOff = 0;
	uint32_t ulTicksToWait = 500;
	SemaphoreHandle_t *xSemaphore = (SemaphoreHandle_t*)pvParameters;

	while (1)
	{
		//delay this task for certain ticks
		vTaskDelayUntil( &xLastExecutionTime, ulTicksToWait );
		// try to take the semaphore
		if (xSemaphoreTake(*xSemaphore,( TickType_t ) 100) == pdPASS)
		{
			if (onOff == 0)
			{
				LED3_OFF();
				//LED9_OFF();
				//LED10_ON();
				//LED5_ON();
				onOff = 1;
			}
			else
			{
				LED3_ON();
				//LED9_ON();
				//LED5_OFF();
				//LED10_OFF();
				onOff = 0;
			}
			xSemaphoreGive(*xSemaphore);
		} else {
			taskYIELD(); //yield
		}
	}

}

static void prvMainTask2(void *pvParameters)
{
	TickType_t xLastExecutionTime;
	xLastExecutionTime = xTaskGetTickCount();
	uint8_t onOff = 0;
	uint32_t ulTicksToWait = 500;
	SemaphoreHandle_t *xSemaphore = (SemaphoreHandle_t*)pvParameters;

	while (1)
	{
		//delay this task for certain ticks
		vTaskDelayUntil( &xLastExecutionTime, ulTicksToWait );
		// try to take the semaphore
		if (xSemaphoreTake(*xSemaphore,( TickType_t ) 100) == pdPASS)
		{
			if (onOff == 0)
				{
					//LED3_OFF();
					//LED9_OFF();
					//LED10_ON();
					LED5_ON();
					onOff = 1;
				}
				else
				{
					//LED3_ON();
					//LED9_ON();
					LED5_OFF();
					//LED10_OFF();
					onOff = 0;
				}
			xSemaphoreGive(*xSemaphore);
		} else {
			taskYIELD(); //yield
		}
	}

}

static void prvMainTask3(void *pvParameters)
{
	TickType_t xLastExecutionTime;
	xLastExecutionTime = xTaskGetTickCount();
	uint8_t onOff = 0;
	uint32_t ulTicksToWait = 500;
	SemaphoreHandle_t *xSemaphore = (SemaphoreHandle_t*)pvParameters;

	while (1)
	{
		//delay this task for certain ticks
		vTaskDelayUntil( &xLastExecutionTime, ulTicksToWait );
		// try to take the semaphore
		if (xSemaphoreTake(*xSemaphore,( TickType_t ) 100) == pdPASS)
		{
			if (onOff == 0)
				{
					//LED3_OFF();
					LED9_OFF();
					//LED10_ON();
					//LED5_ON();
					onOff = 1;
				}
				else
				{
					//LED3_ON();
					LED9_ON();
					//LED5_OFF();
					//LED10_OFF();
					onOff = 0;
				}
			xSemaphoreGive(*xSemaphore);
		} else {
			taskYIELD(); //yield
		}
	}

}

static void prvMainTask4(void *pvParameters)
{
	TickType_t xLastExecutionTime;
	xLastExecutionTime = xTaskGetTickCount();
	uint8_t onOff = 0;
	uint32_t ulTicksToWait = 500;
	SemaphoreHandle_t *xSemaphore = (SemaphoreHandle_t*)pvParameters;

	while (1)
	{
		//delay this task for certain ticks
		vTaskDelayUntil( &xLastExecutionTime, ulTicksToWait );
		// try to take the semaphore
		if (xSemaphoreTake(*xSemaphore,( TickType_t ) 100) == pdPASS)
		{
			if (onOff == 0)
				{
					//LED3_OFF();
					//LED9_OFF();
					LED10_ON();
					//LED5_ON();
					onOff = 1;
				}
				else
				{
					//LED3_ON();
					//LED9_ON();
					//LED5_OFF();
					LED10_OFF();
					onOff = 0;
				}
			xSemaphoreGive(*xSemaphore);
		} else {
			taskYIELD(); //yield
		}
	}

}



//static void prvNOPTask(void *pvParameters)
//{
//}

int main(void)
{
//	SemaphoreHandle_t xSemaphore;

	uint32_t *ptr = (uint32_t*)&_end;
	xHeapRegions[0].pucStartAddress = (uint8_t*)ptr;
	vPortDefineHeapRegions(xHeapRegions);

	RCC->AHBENR |= ((uint32_t)1 << 21); 	// enable clock for port E
	GPIOE->MODER|= ((uint32_t)1 << 18) | (1 << 26) | ( 1 << 20) | ( 1 << 24);
//	GPIOE->BSRR |= ((uint32_t)1 << 9 );

	SysTick_Config(SystemCoreClock / 100000);

	xSemaphore = xSemaphoreCreateMutex();
	if( xSemaphore == NULL )
	{
		for(;;); //loop
	}
	/* main task */
	xTaskCreate( prvMainTask1, "Task1", configMINIMAL_STACK_SIZE, (void*)&xSemaphore, mainTASK_PRIORITY, NULL );
	xTaskCreate( prvMainTask2, "Task2", configMINIMAL_STACK_SIZE, (void*)&xSemaphore, mainTASK_PRIORITY, NULL );
	xTaskCreate( prvMainTask3, "Task3", configMINIMAL_STACK_SIZE, (void*)&xSemaphore, mainTASK_PRIORITY, NULL );
	xTaskCreate( prvMainTask4, "Task4", configMINIMAL_STACK_SIZE, (void*)&xSemaphore, mainTASK_PRIORITY, NULL );

	/* Create the 'check' task, which is also defined within this file. */
//	xTaskCreate( prvNOPTask, "NOP", configMINIMAL_STACK_SIZE, NULL, mainNopIdle_PRIORITY, NULL );

    /* Start the scheduler. */
	vTaskStartScheduler();

    /* Will only get here if there was insufficient memory to create the idle
    task.  The idle task is created within vTaskStartScheduler(). */
	for( ;; );



	return 0;

}




