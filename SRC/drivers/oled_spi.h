#ifndef __OLED_SPI_H
#define __OLED_SPI_H
#include "config.h"

////=============   ���spi   ===========
//#define OLED_RST_Clr() PBout(1)=0   //RST
//#define OLED_RST_Set() PBout(1)=1   //RST

//#define OLED_DC_Clr() PBout(0)=0    //DC
//#define OLED_DC_Set() PBout(0)=1    //DC

//#define OLED_SCL_Clr()  PBout(13)=0  //SCL
//#define OLED_SCL_Set()  PBout(13)=1   //SCL

//#define OLED_SDA_Clr()  PBout(15)=0   //SDA
//#define OLED_SDA_Set()  PBout(15)=1   //SDA


//============   Ӳ��spi   ===============

#define OLED_RESET_LOW()					GPIO_ResetBits(SPI_RES_GPIOX, SPI_RES_PIN)	//�͵�ƽ��λ
#define OLED_RESET_HIGH()					GPIO_SetBits(SPI_RES_GPIOX, SPI_RES_PIN)
 
#define OLED_CMD_MODE()						GPIO_ResetBits(SPI_DC_GPIOX, SPI_DC_PIN) 		//����ģʽ
#define OLED_DATA_MODE()					GPIO_SetBits(SPI_DC_GPIOX, SPI_DC_PIN)			//����ģʽ

#define OLED_CS_HIGH()   					GPIO_SetBits(SPI_CS_GPIOX, SPI_CS_Pin_X)
#define OLED_CS_LOW()  		  			GPIO_ResetBits(SPI_CS_GPIOX, SPI_CS_Pin_X)

//===============DC->PB0  RES->PB1  SDA->PB15  SCL->PB13

#define SPIX                      SPI2
//ʹ��SPI2ʱ��
#define SPI_RCC_APB1Periph_SPIX   RCC_APB1Periph_SPI2
//ʹ��gpioʱ��
#define SPI_RCC_APB2Periph_GPIOX	RCC_APB2Periph_GPIOB	
//CSƬѡ�����Ƭѡ��
#define SPI_CS_Pin_X              GPIO_Pin_12
#define SPI_CS_GPIOX							GPIOB
//SPI2 ʱ�ӡ�mosi��miso����
#define SPI_HW_ALL_PINS          	(GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15) 
#define SPI_HW_ALL_GPIOX					GPIOB
//��λ����
#define SPI_RES_PIN 							GPIO_Pin_1
#define SPI_RES_GPIOX							GPIOB
//��������
#define SPI_DC_PIN 								GPIO_Pin_0
#define SPI_DC_GPIOX							GPIOB


#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����

void OLED_SPI_Init(void);
void SPI_Configuration(void);
void SPI_WriterByte(unsigned char dat);
void WriteCmd(unsigned char cmd);
void WriteDat(unsigned char dat);
void OLED_WR_Byte(u8 dat,u8 cmd);

#endif
