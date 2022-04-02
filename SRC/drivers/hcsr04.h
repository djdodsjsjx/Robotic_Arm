#ifndef __HCSR04_H
#define __HCSR04_H

#include "config.h"

#define HCSR04_PORT GPIOB  
#define HCSR04 RCC_APB2Periph_GPIOB
#define HCSR04_TRIG GPIO_Pin_5
#define HCSR04_ECHO GPIO_Pin_6

#define TRIG_Send PBout(5)
#define ECHO_Reci PBin(6)



void NVIC_Config(void);//÷–∂œ≈‰÷√
void HCSR04_Init(void);//≥¨…˘≤®≥ı ºªØ
float Hcsr04GetLength(void);//≥¨…˘≤®≤‚æ‡

#endif
