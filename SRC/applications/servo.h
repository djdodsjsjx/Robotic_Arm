#ifndef __SERVO_H
#define __SERVO_H
#include "config.h"

#define SERVO_TIM_ARR  19999
#define SERVO_TIM_PSC  71
extern u16 frompos[4],topos[4],outpos[4];
void pwm_servo_init(void);
void servo_demo(void);
void PS2_servo_control(void);
void servo_output(void);
#endif
