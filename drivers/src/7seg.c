/*
 * _7seg.c
 *
 * Created: 7/4/2022 1:31:35 AM
 *  Author: DELL
 */ 

#include "micro_config.h"


void two_digit_7seg(uint8 tensnum)
{
	uint16 i;
	uint16 count;
	if (tensnum==0)
	{
		display_fun(0);
	 }
	 else
	 {
		 
		 for(count=tensnum;count>=0;count--)
		 {
			 
			 //for (i=0;i<=3;i++){
				 
				 display_fun(count/10);
				 TENSPINENABLE;
				 _delay_ms(10);
				 TENSPINDISABLE;
				 display_fun(count%10);
				 UNITSPINENABLE;
				 _delay_ms(10);
				 UNITSPINDISABLE;
				 
			// }
		 }
		 display_off();
	 }
	
}
void display_seg_init(uint8 PortName)
{
	DDRC|=(0x0F<<0)|(0x03<<4);
}
void display_fun(uint8 num)
{
	uint8 BCD_Num;
	
	
		BCD_Num=num;
		switch(BCD_Num){
			case 0:
			{
				PORTC&=~(1<<0)&~(1<<1)&~(1<<2)&~(1<<3);
				break;
			}
			case 1:
			{
				PORTC|=(1<<0);
				PORTC&=~(1<<3)&~(1<<1)&~(1<<2);
				break;
			}
			case 2:
			{
				PORTC|=(1<<1);
				PORTC&=~(1<<3)&~(1<<0)&~(1<<2);
				break;
			}
			case 3:
			{
				PORTC|=(1<<0)|(1<<1);
				PORTC&=~(1<<3)&~(1<<2);
				break;
			}
			case 4:
			{
				PORTC|=(1<<2);
				PORTC&=~(1<<0)&~(1<<1)&~(1<<3);
				break;
			}
			case 5:
			{
				PORTC|=(1<<0)|(1<<2);
				PORTC&=~(1<<3)&~(1<<1);
				break;
			}
			case 6:
			{
				PORTC|=(1<<1)|(1<<2);
				PORTC&=~(1<<3)&~(1<<0);
				break;
			}
			case 7:
			{
				PORTC|=(1<<0)|(1<<1)|(1<<2);
				PORTC&=~(1<<3);
				break;
			}
			case 8:
			{
				PORTC|=(1<<3);
				PORTC&=~(1<<0)&~(1<<1)&~(1<<2);
				break;
			}
			case 9:
			{
				PORTC|=(1<<0)|(1<<3);
				PORTC&=~(1<<1)&~(1<<2);
				break;
			}
				
		}
		
	
	
}
void display_off(void)
{
	PORTC|=(1<<4)|(1<<5);
}