/*
 * SCServo.c
 * ���ض��Ӳ���ӿڲ����
 * ����: 2019.9.7
 * ����: 
 */


#include "config.h"

uint32_t IOTimeOut = 2;//���������ʱ
uint8_t wBuf[128];
uint8_t wLen = 0;

//UART2 �������ݽӿ�
int readSCS(unsigned char *nDat, int nLen)
{
	int Size = 0;
	int ComData;
	uint32_t t_begin = SysTick_GetTick();
	uint32_t t_user;
	while(1){
		ComData = Uart2_Read();
		if(ComData!=-1){
			if(nDat){
				nDat[Size] = ComData;
			}
			Size++;
			t_begin = SysTick_GetTick();
		}
		if(Size>=nLen){
			break;
		}
		t_user = SysTick_GetTick() - t_begin;
		if(t_user>IOTimeOut){
			break;  
		}
	}
	return Size;
}

//UART2 �������ݽӿ�
int writeSCS(unsigned char *nDat, int nLen)
{
	while(nLen--){
		if(wLen<sizeof(wBuf)){
			wBuf[wLen] = *nDat;
			wLen++;
			nDat++;
		}
	}
	return wLen;
}

//���ջ�����ˢ��
void rFlushSCS()
{
	Uart2_Flush();
}

//���ͻ�����ˢ��
void wFlushSCS()
{
	if(wLen){
		
		Uart2_Send(wBuf, wLen);
		wLen = 0;
	}
}

