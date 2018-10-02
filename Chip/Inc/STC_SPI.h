#ifndef __STC_SPI_H__
#define __STC_SPI_H__

typedef enum
{
	SLAVE, //SPI从机
	MASTER,//SPI主机
}M_S_MODE_e;//主从模式选择

typedef enum
{
	MSB_SPI,//高位先发送或接收
	LSB_SPI,//低位先发送或接收
}BIT_ERDER_e;//SPI数据发送和接收的位顺序选择

typedef enum
{
	SPI_MODE0,//SPI模式0【空闲时SCLK=0，前时钟沿采样（获取数据）】
	SPI_MODE1,//SPI模式1【空闲时SCLK=0，后时钟沿采样（获取数据）】
	SPI_MODE2,//SPI模式2【空闲时SCLK=1，前时钟沿采样（获取数据）】
	SPI_MODE3,//SPI模式3【空闲时SCLK=1，后时钟沿采样（获取数据）】
}SPI_MODEn_e;//SPI总线模式

typedef enum
{
	FRAC_4_SPEAD,		//4分频系统时钟速度
	FRAC_16_SPEAD,	//16分频系统时钟速度
	FRAC_64_SPEAD,	//64分频系统时钟速度
	FRAC_128_SPEAD,	//128分频系统时钟速度
}SCLK_SPEADn_e;//SPI时钟速率

extern void SPI_init(M_S_MODE_e , BIT_ERDER_e , SPI_MODEn_e , SCLK_SPEADn_e);//SPI初始化
extern void SPI_SendData(uint8 dat);//发送1字节数据
	
void SPI_IRQHandler(void);//SPI中断

#endif //__STC_SPI_H__