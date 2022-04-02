#include "sys.h"
#include "usart.h"	  

u8 USART1_com_data;

void uart_init(u32 bound){
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9
   
  //USART1_RX	  GPIOA.10��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  

  //Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=NVIC_USART1_P ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = NVIC_USART1_S;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART1, &USART_InitStructure); //��ʼ������1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1 

}


static u8 TxBuffer[256];
static u8 TxCounter=0;
static u8 count=0;

void Uart1_Put_Char(unsigned char DataToSend)
{
	TxBuffer[count++] = DataToSend;
	USART_ITConfig(USART1, USART_IT_TXE,ENABLE);
}
	
void Uart1_Put_Buf(unsigned char *DateToSend, u8 data_num)
{
	for(u8 i=0;i<data_num;i++)
		TxBuffer[count++] = *(DateToSend+i);
	if(!(USART1->CR1 & USART_CR1_TXEIE))
	{
		USART_ITConfig(USART1, USART_IT_TXE,ENABLE);
	}
}

void USART1_IRQHandler(void)  
{
	if(USART_GetITStatus(USART1,USART_IT_ORE)!=RESET)
	{
		USART_ReceiveData(USART1);
	}
	
	//�����ж�
  if(USART1->SR &(1<<7)&&(USART1->CR1&USART_CR1_TXEIE))
	{
		USART1->DR=TxBuffer[TxCounter++];
		if(TxCounter==count)
		{
			USART1->CR1&=~USART_CR1_TXEIE;
			
		}
	}
	//�����ж�
	if(USART1->SR &(1<<5))
	{
		USART1_com_data = USART1->DR;
//		Uart1_Put_Char(com_data);
//		OpenMV_Byte_Get(com_data);
	}
}


///�ض���c�⺯��printf�����ڣ��ض�����ʹ��printf����
int fputc(int ch, FILE *f)
{
		/* ����һ���ֽ����ݵ����� */
		USART_SendData(USART1, (uint8_t) ch);
		
		/* �ȴ�������� */
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}


