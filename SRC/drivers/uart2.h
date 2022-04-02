#ifndef		__UART2_H
#define		__UART2_H

#include "config.h"

extern void Uart2_Init(uint32_t baudRate);
extern void Uart2_Flush(void);
extern int16_t Uart2_Read(void);
extern void Uart2_Send(uint8_t *buf , uint8_t len);

#endif
