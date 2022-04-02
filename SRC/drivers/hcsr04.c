#include "hcsr04.h"

u16 overcount=0;//溢出计数

//中断配置
void NVIC_Config(void)
{
		NVIC_InitTypeDef NVIC_InitStruct;
//		//设置中断优先级
//		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
		//中断初始化
		NVIC_InitStruct.NVIC_IRQChannel=TIM2_IRQn;
		NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
		NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;
		NVIC_InitStruct.NVIC_IRQChannelSubPriority=0;
		NVIC_Init(&NVIC_InitStruct);
}


//超声波初始化
void HCSR04_Init(void)
{
		GPIO_InitTypeDef GPIO_InitStruct;
		TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
		//时钟使能
		RCC_APB2PeriphClockCmd(HCSR04,ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
		//trig脚-推挽输出
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
		GPIO_InitStruct.GPIO_Pin=HCSR04_TRIG;
		GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(HCSR04_PORT,&GPIO_InitStruct);
		GPIO_ResetBits(HCSR04_PORT,HCSR04_TRIG);
		//echo脚-浮空输入
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;
		GPIO_InitStruct.GPIO_Pin=HCSR04_ECHO;
		GPIO_Init(HCSR04_PORT,&GPIO_InitStruct);
		GPIO_ResetBits(HCSR04_PORT,HCSR04_ECHO);
		//定时器TIM2初始化
		TIM_DeInit(TIM2);
		TIM_TimeBaseInitStruct.TIM_Period=1000-1;
		TIM_TimeBaseInitStruct.TIM_Prescaler=72-1;
		TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
		TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
		TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
		//定时器中断配置_更新中断
		TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
		//中断配置
		NVIC_Config();
		//关闭定时器使能
		TIM_Cmd(TIM2,DISABLE);
}


//打开定时器
void OpenTimeForHc(void)
{
		//计数器清空
		TIM_SetCounter(TIM2,0);
		overcount=0;
		TIM_Cmd(TIM2,ENABLE);
}

//关闭定时器
void CloseTimeForHc(void)
{
		TIM_Cmd(TIM2,DISABLE);
}

//获取定时器时间
u32 GetEchoTimer(void)
{
		u32 t=0;
		t=overcount*1000;
		t+=TIM_GetCounter(TIM2);
		//计数器清0
		TIM2->CNT=0;
		Delay_ms(2);
	
		return t;
}

//超声波测距
float Hcsr04GetLength(void)
{
		u32 t=0;
		int i=0;
		float lengthTemp=0;
		float sum=0;
		while(i!=5)
		{
				TRIG_Send=1;
				Delay_us(200);
				TRIG_Send=0;
				while(ECHO_Reci==0);
				OpenTimeForHc();
				i=i+1;
				while(ECHO_Reci==1);
				CloseTimeForHc();
				t=GetEchoTimer();
				lengthTemp=((float)t/58.0);
				sum+=lengthTemp;
		}
		lengthTemp=sum/i;
//		printf("lengthTemp:    %f\n",lengthTemp);
		return lengthTemp;
}

////定时器2中断
//void TIM2_IRQHandler(void)
//{
//		if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET)
//		{
//				//清除中断标志位
//				TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
//				overcount++;
//		}
//}

