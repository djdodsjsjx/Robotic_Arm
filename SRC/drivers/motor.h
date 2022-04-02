#ifndef __MOTOR_H
#define __MOTOR_H
#include "config.h"	 


//#define PWMD   TIM8->CCR4  
//#define PWMC   TIM8->CCR3  
//#define PWMB   TIM8->CCR1 
#define PWMA   TIM3->CCR3

//#define IND1   PBout(1)  
//#define INC1   PCout(4)  
//#define INB1   PAout(4)  
//#define INA1   PAout(3)

//#define IND2   PBout(0)  
//#define INC2   PCout(5)  
//#define INB2   PAout(5)  
//#define INA2   PAout(2)


#define MOTORA1 PBout(5)	
#define MOTORA2 PBout(6)	


void Motor_PWM_Init(u16 arr,u16 psc);
void Motor_Init(void);
void MOTORA_control(void);
#endif
