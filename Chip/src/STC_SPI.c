#include "common.h"
#include "STC_SPI.h"
#include "STC_interrupt.h"
#include "STC_gpio.h"
#include "STC_UART.h"//SPI转串口时使用

bit SPI_BUSY = 0;//SPI总线忙状态，忙时不得对数据寄存器写操作

/*!
 *	@brief		SPI初始化
 *	@param		M_S_MODE		主从模式选择
							BIT_ERDER		位传输顺序（高位在前还是低位在前）
							SPI_MODEn		SPI模式选择（0~4）
							SCLK_SPEADn	SPI速率选择
 *	@warning	SPI数据或时钟引脚所在IO口工作模式需注意，上电初始化为准双向口
              这是STC单片机自带的硬件SPI，每次只支持8位传输，不能满足所有的SPI器件，若硬件SPI满足不了可参考STC_soft_SPI
 *	@sampleusage:	SPI_init(MASTER,MSB_SPI,SPI_MODE0,FRAC_128_SPEAD);//SPI工作在主机模式，高位先发送，模式0，系统128分频速率
 */

void SPI_init(M_S_MODE_e M_S_MODE , BIT_ERDER_e BIT_ERDER , SPI_MODEn_e SPI_MODEn , SCLK_SPEADn_e SCLK_SPEADn)
{
	if(SPI_MOSI==p13 && SPI_MISO==p14 && SPI_SCLK==p15)	REPLACE(P_SW1,3,2,0);
	else if(SPI_MOSI==p23 && SPI_MISO==p22 && SPI_SCLK==p21)	REPLACE(P_SW1,3,2,1);
			 else if(SPI_MOSI==p40 && SPI_MISO==p41 && SPI_SCLK==p43)	REPLACE(P_SW1,3,2,2);
	SPDAT  = 0x00;//清除SPI数据寄存器
	SPSTAT = 0xff;//清除SPI传输完成及写冲突标志
	BIT_SET(SPCTL,7);//忽略SS引脚，主从由软件控制
	REPLACE(SPCTL,4,4,M_S_MODE);//主从模式选择
	REPLACE(SPCTL,5,5,BIT_ERDER);//SPI数据发送和接收的位顺序选择
	REPLACE(SPCTL,3,2,SPI_MODEn);//SPI模式选择
	REPLACE(SPCTL,1,0,SCLK_SPEADn);//SPI时钟速率选择
	
	BIT_SET(SPCTL,6);//启用SPI模块
	set_vector_handler(SPI_VECTORn , SPI_IRQHandler);//SPI的中断服务函数为SPI_IRQHandler
	BIT_SET(IE2,1);//允许SPI中断
	EA=1;
}

/*!
 *	@brief		SPI中断（接收为主）
 *	@param		
 *	@warning	由此接收SPI的数据
 *	@sampleusage:	主函数一般禁止调用中断函数
 */

void SPI_IRQHandler(void)
{
	SPSTAT = 0xff;//清除SPI传输完成及写冲突标志
	SPI_BUSY = 0;
	//接收数据SPDAT
	//Uart_SendData(UART0,SPDAT);//接收SPI并通过UART回传数据【SPI转串口时使用】
}

/*!
 *	@brief		SPI发送1字节数据
 *	@param		dat	要发送的1字节数据
 *	@warning	
 *	@sampleusage:	SPI_SendData(0x10);//用SPI总线发送8位数据0x10
 */

void SPI_SendData(uint8 dat)
{
	while(SPI_BUSY);//等待上一帧数据发送完成
	SPI_BUSY = 1;
	SPDAT = dat;
}