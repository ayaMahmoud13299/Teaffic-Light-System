#include "micro_config.h"


/*******************************************************************************
 *                          Global Variables                                   *
 *******************************************************************************/
//volatile uint16 g_adcResult = 0;

/*******************************************************************************
 *                          ISR's Definitions                                  *
 *******************************************************************************/
/* Interrupt Service Routine for timer0 compare mode */
ISR(TIMER0_COMP_vect)
{		
}

/* For clock=1Mhz and prescale F_CPU/1024 every count will take 1ms
 * so we just need 250 counts to get 250ms every compare match.
 * put initial timer counter=0 and output compare register=250 0 --> 250 (250ms per compare match)
 * so we need timer to make 2 times compare matches to get a 0.5 second
 */
 
void timer0_init_CTC_mode(unsigned char tick)
{
	TCNT0 = 0;    // Set Timer initial value to 0
	OCR0  = tick; // Set Compare Value
	TIMSK |= (1<<OCIE0); // Enable Timer0 Compare Interrupt
	/* Configure timer0 control register 
	 * 1. Non PWM mode FOC0=1
	 * 2. CTC Mode WGM01=1 & WGM00=0
	 * 3. No need for OC0 in this example so COM00=0 & COM01=0 
	 * 4. clock = F_CPU/1024 CS00=1 CS01=0 CS02=1
	 */
	TCCR0 = (1<<FOC0) | (1<<WGM01) | (1<<CS02) | (1<<CS00);
}