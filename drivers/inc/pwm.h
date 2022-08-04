/*
 * pwm.h
 *
 * Created: 7/5/2022 1:35:45 AM
 *  Author: DELL
 */ 


#ifndef PWM_H_
#define PWM_H_


#include "std_types.h"

enum colors{red,green,yellow}color;



void pwm_init(void);
void pwm_fun(uint8 duty);
void leds_init(void);
void traffic_light_handele(uint8 ledcolor);
#endif /* PWM_H_ */