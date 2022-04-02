#include "led.h"

void LED_Init(void)
{
 
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 	    		 
	GPIO_Init(GPIOA, &GPIO_InitStructure);	  

	LED1=0;
	LED2=0;
	
}
 
void LED_control(void)
{
	LED1=0;
	LED2=1;
	Delay_ms(3000);
	LED1=1;
	LED2=0;
	Delay_ms(3000);
}