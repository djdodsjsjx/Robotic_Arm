#ifndef __GAIT_TASK_H
#define __GAIT_TASK_H

#include "config.h"

extern float step_t,forward_t,back_t,turn_left_t,turn_right_t,left_shift_t,right_shift_t;
extern u8 start_flag;

void trot_task(s8 a);
void step(s16 a);       //踏步
void forward(s16 a,float rol);   //前进
void back(s16 a);       //后退
void turn_left(s16 a);  //左转
void turn_right(s16 a); //右转
void left_shift(s16 a); //左移
void right_shift(s16 a);//右移
void dog_start(void);  //起步
void po_1(s16 a,float rol);
void po_2(s16 a,float rol);
void po_3(s16 a,float rol);
void shang_po(s16 a,float rol);
	
#endif
