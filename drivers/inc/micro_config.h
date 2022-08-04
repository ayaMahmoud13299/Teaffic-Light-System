

#ifndef MICRO_CONFIG_H_
#define MICRO_CONFIG_H_

#ifndef F_CPU
#define F_CPU 1000000UL //1MHz Clock frequency
#endif  

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "7seg.h"
#include "adc.h"
#include "common_macros.h"
#include "pwm.h"
#include "lcd.h"
#include "std_types.h"
#include "Timer.h"
#include "uart.h"

#endif /* MICRO_CONFIG_H_ */
