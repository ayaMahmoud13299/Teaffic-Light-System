/*
 * Final_project.c
 *
 * Created: 7/4/2022 2:19:19 AM
 * Author : EGYPT_LAPTOP
 */ 


#include "micro_config.h"
#include "FreeRTOS.h"
#include "task.h"


uint8 emergency_detection=UNDETECTED;

volatile uint16 g_adcResult = 0;
uint8 counter =0;
uint8 pedestrian_request=UNDETECTED;


enum states{Green,Yellow,Red}state;
	
//void manage(void);	
void Task1_Func(void *parameters);
TaskHandle_t task1ptr;

void Task2_Func(void *parameters);
TaskHandle_t task2ptr;

void emergencydetection_Func(void *parameters);
TaskHandle_t task3ptr;


int main(void)
{
		DDRB |= (1<<5);   // Configure pin 5 in PORTB as output pin
		PORTB &= ~(1<<5);
		


		state=Red;

	
		leds_init();
		ADC_init(); /* initialize ADC driver */
		display_seg_init(PC);
		pwm_init();
		pwm_fun(179);

	
	
	xTaskCreate(Task1_Func,"first",configMINIMAL_STACK_SIZE,NULL,3,&task1ptr);
	xTaskCreate(Task2_Func,"second",configMINIMAL_STACK_SIZE,NULL,2,&task2ptr);
	xTaskCreate(emergencydetection_Func,"third",configMINIMAL_STACK_SIZE,NULL,2,&task3ptr);
	


	vTaskStartScheduler();
	

	
	
	
	while(1)
	{
		     
	}
}

void Task1_Func(void *parameters)
{
	TickType_t xLastWakeTime;
	const TickType_t xPeriod = pdMS_TO_TICKS( 10 );

	// Initialise the xLastWakeTime variable with the current time.
	xLastWakeTime = xTaskGetTickCount();

	while(1)
	{
		vTaskDelayUntil(&xLastWakeTime,xPeriod);
		
		g_adcResult=ADC_readChannel(0);
		
		if((g_adcResult >=341 ) && (g_adcResult < 512))
		{
			counter++;
		}
		else
		{
			counter=0;
		}
		
		if (counter==10)
		{
			counter=0;
			pedestrian_request = DETECTED;
		}
		
		if(pedestrian_request==DETECTED)
		{
			PORTB ^= (1<<5);
			pedestrian_request=UNDETECTED;
		}

	}
}

void Task2_Func(void *parameters)
{
    
	while(1)
	{ 
		   switch(state)
		   
		   {
			   case Green:
			   {
				   
				   traffic_light_handele(green);
				   two_digit_7seg(0);
				   
				   
				   if(pedestrian_request==DETECTED)
				   {
					   if(emergency_detection==UNDETECTED)
					   {
						   state=Yellow;
					   }
					   else
					   {
						   //while(!(emergency_detection == DETECTED))
						   //{
						   state=Green;
						   emergency_detection=UNDETECTED;
						   //}
					   }
					   pedestrian_request=UNDETECTED;
					   
				   }
				   vTaskDelay(pdMS_TO_TICKS( 10 ));
				   break;
			   }
			   
			   case Yellow:
			   {
				   traffic_light_handele(yellow); //Encrement el counter till 10 sec and display it on sevensegemnt
				   two_digit_7seg(10);
				   display_off;
				   state=Red;
				   vTaskDelay(pdMS_TO_TICKS( 10 ));
				   break;
			   }
			   
			   
			   case Red:
			   {
				   traffic_light_handele(red);
				   two_digit_7seg(30);
				   
				   
				   
				   state=Green;
				   vTaskDelay(pdMS_TO_TICKS( 10 ));
				   break;
			   }
		   }
	}
	vTaskDelay(pdMS_TO_TICKS( 100 ));
}

void emergencydetection_Func(void *parameters)
{
	uint8 Str[30];
	uint8 *head;
	uint8 *data;
	

	/* Initialize the UART driver with Baud-rate = 9600 bits/sec */
	UART_init(9600);

	while(1)
	{
		//data = UART_recieveByte(); /* Receive Byte from Terminal1 */
		//UART_sendByte(data);       /* Re-send the received byte to Terminal2 */
		head=UART_receiveString(Str);     /* Receive String from Terminal */
		data=UART_receiveString(Str);
		
		if((data[12] == (uint8)'0') && (data[13] == (uint8)'2')  || (data[13] == (uint8)'3'))
		{
			emergency_detection=DETECTED;
			UART_sendString("Emergency!\r");
			vTaskDelay(pdMS_TO_TICKS( 10000 ));
		}
		else
		{
			
			UART_sendString("No Emergency\r");
			//vTaskDelay(pdMS_TO_TICKS( 100 ));
		}
	}
}





