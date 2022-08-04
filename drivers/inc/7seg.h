/*
 * _7seg.h
 *
 * Created: 7/4/2022 1:32:00 AM
 *  Author: DELL
 */ 


#ifndef DSEG_H_
#define DSEG_H_
#include "std_types.h"
#include <AVR/io.h>
//#define F_CPU 8000000ul

#include <util/delay.h>

#define PC 0x03
#define OUTPUT 1
#define TENSPINENABLE (PORTC&=~(1<<4))
#define UNITSPINENABLE (PORTC&=~(1<<5))
#define TENSPINDISABLE (PORTC|=(1<<4))
#define UNITSPINDISABLE (PORTC|=(1<<5))



void display_seg_init(uint8 PortName);
void display_fun(uint8 num);
void two_digit_7seg(uint8 tensnum);
void display_off(void);



#endif /* 7SEG_H_ */
