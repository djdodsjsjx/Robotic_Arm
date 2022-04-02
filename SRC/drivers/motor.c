#include "motor.h"

void Motor_Init(void)
{
//  GPIO_InitTypeDef GPIO_InitStructure;
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE); //使能PB PC端口时钟
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;	//端口配置
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //推挽输出
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     //50M
//  GPIO_Init(GPIOB, &GPIO_InitStructure);					      //根据设定参数初始化GPIOB 
//	
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;	//端口配置
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //推挽输出
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     //50M
//  GPIO_Init(GPIOC, &GPIO_InitStructure);					      //根据设定参数初始化GPIOC
//	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;	//端口配置
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //推挽输出
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     //50M
//  GPIO_Init(GPIOA, &GPIO_InitStructure);					      //根据设定参数初始化GPIOC
	
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 	    		 
	GPIO_Init(GPIOB, &GPIO_InitStructure);	  

//	MOTORA1=0;
//	MOTORA2=0;
}
void Motor_PWM_Init(u16 arr,u16 psc)
{	
	Motor_Init();
	TIM3_PWM_Init(arr,psc);
} 

void MOTORA_control(void)
{
	MOTORA1=0;
	MOTORA2=1;
	PWMA=1000;
	Delay_ms(3000);
	MOTORA1=1;
	MOTORA2=0;
	Delay_ms(3000);
}

