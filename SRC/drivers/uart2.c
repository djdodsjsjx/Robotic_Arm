#include "uart2.h"

//UART 读数据缓冲区
__IO uint8_t uartBuf[128];
__IO int head = 0;
__IO int tail = 0;

void Uart2_Flush(void)
{
	head = tail = 0;
}

int16_t Uart2_Read(void)
{
	if(head!=tail){
		uint8_t Data = uartBuf[head];
		head =  (head+1)%128;
		return Data;
	}else{
		return -1;
	}
}

void Uart2_Init(uint32_t baudRate)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	//UART2 GPIO 配置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;//PA2 UART2_TX
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
    
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PA3 UART2_RX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//UART 数据格式配置
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;
	USART_InitStructure.USART_BaudRate = baudRate;
	USART_Init(USART2, &USART_InitStructure);
	
	//中断配置
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIC_USART2_P;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = NVIC_USART2_S;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	//打开UART使能开关
	USART_Cmd(USART2, ENABLE);
}

void USART2_IRQHandler(void)
{
	USART_ClearITPendingBit(USART2, USART_IT_ORE);
	uartBuf[tail] = USART_ReceiveData(USART2);
	tail = (tail+1)%128;
}

void Uart2_Send(uint8_t *buf , uint8_t len)
{
	uint8_t i=0;
	for(i=0; i<len; i++){
		USART_SendData(USART2, buf[i]);
		while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
	}
	while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
}

