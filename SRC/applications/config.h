#ifndef __CONFIG_H
#define __CONFIG_H

#include "stm32f10x.h"
#include "sys.h"
#include "usart.h"
#include "usart3.h"
#include "pwm.h"
#include "servo.h"
#include "uart2.h"
#include "openmv.h"
#include "calculate.h"
#include "control.h"
#include "math.h"
#include "stdlib.h"
#include "SCSCL.h"
#include "INST.h"
#include "SCS.h"
#include "uart2.h"
#include "DT.h"
#include "Scheduler.h"
#include "time.h"
#include "filter.h"
#include "hcsr04.h"
#include "mpu6050.h"
#include "mpu9250.h"
#include "mpuiic.h"
#include "oled.h"
#include "show.h"
#include "oled_spi.h"
#include "my_math.h"
#include "led.h"
#include "pstwo.h"
#include "mearm.h"



#define NVIC_TIME_P       1					  
#define NVIC_TIME_S       3

#define NVIC_USART1_P       3					
#define NVIC_USART1_S       3

#define NVIC_USART2_P       1				
#define NVIC_USART2_S       0

#define NVIC_USART3_P       1					
#define NVIC_USART3_S       2

void data_config(void);
void init_config(void);
#endif

