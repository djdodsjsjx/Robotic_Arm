#ifndef __CONTROL_H
#define __CONTROL_H
#include "config.h"

void demo(void);
void lanya(u8 data);

void Set_Pwm(int motor_a,int motor_b,int motor_c,int motor_d);

void Xianfu_Pwm(int amplitude);
void Xianfu_Velocity(int amplitude_A,int amplitude_B,int amplitude_C,int amplitude_D);

int Incremental_PI_A (int Encoder,int Target);
int Postion_PID (int Encoder,int Target);


#endif
