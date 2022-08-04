/*
 * pwm.c
 *
 * Created: 7/5/2022 1:35:24 AM
 *  Author: DELL
 */ 
#include "micro_config.h"

void pwm_init(void)
{
	/* configure the timer
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/1 CS00=1 CS01=0 CS02=0
	 *F(PWM)=100KHZ , F_CPU=1MH , COUNTER VALUE =10
	 */ 
	/* Set Timer Initial Value to 0 */
	TCNT0 = 246; 
	
	/*set fast PWM mode with non-inverted output*/
	TCCR0 |= (1<<WGM00) | (1<<WGM01)|(1<<CS00)|(1<<COM01) ; //fast pwm
	
	/*co pin for timer0 */
	DDRB  |= (1<<3); 
	
}
void pwm_fun(uint8 duty)
{
	OCR0=duty;
	
}
void leds_init(void)
{
	DDRB|=(1<<6);
	DDRC|=(1<<6)|(1<<7);
}
void traffic_light_handele(uint8 ledcolor)
{
	PORTB&=~(1<<6);
	PORTC&=~(1<<6)&~(1<<7);
	uint8 color =ledcolor;
	switch (color)
	{
	case red :
	{
		PORTC|=(1<<6);
		break;
	}
	
		case green :
		{
			PORTB|=(1<<6);
			break;
		}
		
		case yellow :
		{
			PORTC|=(1<<7);
			break;
		}
		
	}
	
}