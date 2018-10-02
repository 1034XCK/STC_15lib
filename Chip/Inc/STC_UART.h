#ifndef __STC_UART_H__
#define __STC_UART_H__
#include "STC_PIT.h"

typedef enum
{
	UART0,
	UART1,
	UART2,
	UART3,
}UARTn_e;

typedef enum
{
	NONE_PARITY	,	//无校验
	ODD_PARITY	,	//奇校验
	EVEN_PARITY	,	//偶校验
	MARK_PARITY	,	//“1”校验
	SPACE_PARITY,	//“0”校验
}PARITYn_e;

#define UART_RX_BUF_SIZE 10

extern void UART_init(UARTn_e , PARITYn_e , TIMERn_e , uint32 baud_rate);
extern void Uart_SendData(UARTn_e UARTn , uint8 dat);
extern void SendString(UARTn_e UARTn , uint8 *s);

void UART0_IRQHandler(void);
void UART1_IRQHandler(void);
void UART2_IRQHandler(void);
void UART3_IRQHandler(void);


uint8 uart_code[];

#endif //__STC_UART_H__