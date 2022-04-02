#ifndef __GAIT_TASK_H
#define __GAIT_TASK_H

#include "config.h"

extern float step_t,forward_t,back_t,turn_left_t,turn_right_t,left_shift_t,right_shift_t;
extern u8 start_flag;

void trot_task(s8 a);
void step(s16 a);       //̤��
void forward(s16 a,float rol);   //ǰ��
void back(s16 a);       //����
void turn_left(s16 a);  //��ת
void turn_right(s16 a); //��ת
void left_shift(s16 a); //����
void right_shift(s16 a);//����
void dog_start(void);  //��
void po_1(s16 a,float rol);
void po_2(s16 a,float rol);
void po_3(s16 a,float rol);
void shang_po(s16 a,float rol);
	
#endif
