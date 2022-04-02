#ifndef __USART_H
#define __USART_H

#include "config.h"
#include "stdio.h"
extern u8 USART1_com_data;

#define USART_REC_LEN  			200  	//�����������ֽ��� 200
#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����
	  	
extern u8  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART_RX_STA;         		//����״̬���	
//����봮���жϽ��գ��벻Ҫע�����º궨��
void uart_init(u32 bound);
void Uart1_Put_Char(unsigned char DataToSend);
void Uart1_Put_Buf(unsigned char *DateToSend, u8 data_num);
#endif


