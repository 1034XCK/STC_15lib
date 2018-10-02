#ifndef __STC_SOFT_IIC_H__
#define __STC_SOFT_IIC_H__

#include "STC_SysTick.h"
#include "PORT_cfg.h"

//0表示写入
#define	IIC_Direction_Transmitter   0
//1表示读取
#define	IIC_Direction_Receiver      1

typedef enum
{
	bit_wide_8  = 1,
	bit_wide_16 = 2,
	bit_wide_32 = 4,
}bit_wide;

extern bool IIC_Write_Reg(uint8 addr , uint8 reg , uint8 Data);
extern uint8 IIC_Read_Reg(uint8 addr , uint8 reg);
extern bool IIC_Write(uint8 addr , bit_wide reg_wide , uint32 reg , uint8 len , uint8 *Data);
extern bool IIC_Read(uint8 addr , bit_wide reg_wide , uint32 reg , uint8 len , uint8 *buf);

bool IIC_Start(void);
void IIC_Stop(void);
void IIC_Ack(void);
void IIC_NoAck(void);
bool IIC_GetAck(void);
void IIC_SendByte(uint8 x);
uint8 IIC_ReceiveByte(void);
uint8 IIC_Wait_ReceiveByte(void);

#endif //__STC_SOFT_IIC_H__