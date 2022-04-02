#include "usart3.h"	  

//===========P4->RX, P5->TX==========
void Usart3_Init(u32 bound)
{
	GPIO_InitTypeDef   GPIO_InitStructure;
	USART_InitTypeDef  USART_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_PinRemapConfig(GPIO_PartialRemap_USART3, ENABLE);
	
	//USART3_TX		PB.10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;					//�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//USART3_RX		PB.11
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;			//��������
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//�Դ���3ͨ��Э����г�ʼ������
	USART_InitStructure.USART_BaudRate = bound;						//���ò�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;		//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;			//1λֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;				//����żЧ��
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//��Ӳ��������
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;	//˫��ͨ��
	USART_Init(USART3, &USART_InitStructure);
	
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);					//���������ж�	
	USART_Cmd(USART3, ENABLE);

	//�Դ���3�շ��ж�����
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);					//�ж���ѡ�ڶ���
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;  				
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIC_USART3_P;  		//��ռ���ȼ�2��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = NVIC_USART3_S;  			//�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 				//IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);
}


static u8 TxBuffer[256];
static u8 TxCounter=0;
static u8 count=0;


void Uart3_Put_Char(unsigned char DataToSend)
{
	TxBuffer[count++] = DataToSend;
	USART_ITConfig(USART3, USART_IT_TXE,ENABLE);
}
	
void Uart3_Put_Buf(unsigned char *DateToSend, u8 data_num)
{
	u8 i;
	for(i=0;i<data_num;i++)
		TxBuffer[count++] = *(DateToSend+i);
	if(!(USART3->CR1 & USART_CR1_TXEIE))
	{
		USART_ITConfig(USART3, USART_IT_TXE,ENABLE);
	}
}

/* ����һ���ֽ� */
void Usart3_SendByte(uint8_t data)
{
	USART_SendData(USART3, data);
	while( USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET );
}

/* ���������ֽڵ����� */
void Usart3_SendWord(uint16_t data)
{
	uint8_t temp_h,temp_l;
	
	temp_h = (data&0xff00) >> 8 ;
	temp_l = data&0xff;
	
	USART_SendData(USART3, temp_h);
	while( USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET );
	
	USART_SendData(USART3, temp_l);
	while( USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET );
}


void USART3_IRQHandler(void)  
{
	if(USART_GetITStatus(USART3,USART_IT_ORE)!=RESET)
	{
		USART_ReceiveData(USART3);
	}
	
	//�����ж�
  if(USART3->SR &(3<<7)&&(USART3->CR1&USART_CR1_TXEIE))
	{
		USART3->DR=TxBuffer[TxCounter++];
		if(TxCounter==count)
		{
			USART3->CR1&=~USART_CR1_TXEIE;
			
		}
	}
	//�����ж�
	if(USART3->SR &(1<<5))
	{
		u8 com_data;
		USART_ClearITPendingBit(USART3,USART_IT_RXNE);
		com_data = USART3->DR;
		OpenMV_Byte_Get(com_data);
//		printf("com_data:%d\n",com_data);
		
	}
}


