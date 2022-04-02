#include "hcsr04.h"

u16 overcount=0;//�������

//�ж�����
void NVIC_Config(void)
{
		NVIC_InitTypeDef NVIC_InitStruct;
//		//�����ж����ȼ�
//		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
		//�жϳ�ʼ��
		NVIC_InitStruct.NVIC_IRQChannel=TIM2_IRQn;
		NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
		NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;
		NVIC_InitStruct.NVIC_IRQChannelSubPriority=0;
		NVIC_Init(&NVIC_InitStruct);
}


//��������ʼ��
void HCSR04_Init(void)
{
		GPIO_InitTypeDef GPIO_InitStruct;
		TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
		//ʱ��ʹ��
		RCC_APB2PeriphClockCmd(HCSR04,ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
		//trig��-�������
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
		GPIO_InitStruct.GPIO_Pin=HCSR04_TRIG;
		GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(HCSR04_PORT,&GPIO_InitStruct);
		GPIO_ResetBits(HCSR04_PORT,HCSR04_TRIG);
		//echo��-��������
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;
		GPIO_InitStruct.GPIO_Pin=HCSR04_ECHO;
		GPIO_Init(HCSR04_PORT,&GPIO_InitStruct);
		GPIO_ResetBits(HCSR04_PORT,HCSR04_ECHO);
		//��ʱ��TIM2��ʼ��
		TIM_DeInit(TIM2);
		TIM_TimeBaseInitStruct.TIM_Period=1000-1;
		TIM_TimeBaseInitStruct.TIM_Prescaler=72-1;
		TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
		TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
		TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
		//��ʱ���ж�����_�����ж�
		TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
		//�ж�����
		NVIC_Config();
		//�رն�ʱ��ʹ��
		TIM_Cmd(TIM2,DISABLE);
}


//�򿪶�ʱ��
void OpenTimeForHc(void)
{
		//���������
		TIM_SetCounter(TIM2,0);
		overcount=0;
		TIM_Cmd(TIM2,ENABLE);
}

//�رն�ʱ��
void CloseTimeForHc(void)
{
		TIM_Cmd(TIM2,DISABLE);
}

//��ȡ��ʱ��ʱ��
u32 GetEchoTimer(void)
{
		u32 t=0;
		t=overcount*1000;
		t+=TIM_GetCounter(TIM2);
		//��������0
		TIM2->CNT=0;
		Delay_ms(2);
	
		return t;
}

//���������
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

////��ʱ��2�ж�
//void TIM2_IRQHandler(void)
//{
//		if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET)
//		{
//				//����жϱ�־λ
//				TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
//				overcount++;
//		}
//}

