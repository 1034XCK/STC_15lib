#include "common.h"
#include "STC_gpio.h"
#include "STC_soft_IIC.h"

/*!
 *	@brief		IIC初始化
 *	@param		SCL_pxn  SCL所对应的引脚(小写类型)
              SDA_pxn  SDA所对应的引脚(小写类型)
 *	@warning	此初始化函数并非必要，应为只是对IO口的工作模式和初始电平做了初始化，而单片机上电后默认的设置就是符合要求的
              此函数有返回值，对初始化后的两根线的电平进行检测，若符合IIC总线闲置标准将回复1，否则回复0
              考虑到IIC是由软件模拟的时序，所以需要较高的执行效率，故PORT_cfg.h中端口设置为大写的Pxx，而此函数要设置端口工作模式需使用小写的pxx端口表示类型，两中表示类型不兼容，
							故若使用此函数初始化IIC工作端口请与PORT_cfg.h中的设置保持一致，如需更改端口请务必保持双方一致！
							因多个IIC设备可挂载在一条总线上，所以只设置了1路IIC通道可用
							总线速度设置由下方的#if完成，若总线上的设备均可接受1MHz以上的时钟变化率(高速模式)就填写#if 1 ， 若不能满足就填#if 0 并根据实际情况选择systick_delay_us(x)里的x值(可填写0-普通模式)
							需要注意的是总线速度需根据这条总线上最慢的设备要求来设置
 *	@Sampleusage:	IIC_init(p41 , p42);//P41作为SCL线、P42作为SDA线
 */

#if 0
 #define IIC_delay() _nop_()
#else
 #define IIC_delay() systick_delay_us(1)
#endif

bool IIC_init(pxn_e SCL_pxn , pxn_e SDA_pxn)
{
	gpio_init(SCL_pxn, WEAKPULLUP, 1);
	gpio_init(SDA_pxn, WEAKPULLUP, 1);
	_nop_();
	if (IIC_SCL && IIC_SDA) return true;
	else return false;
}

/*!
 *	@brief		IIC启动信号
 *	@param		
 *	@warning	若启动信号发送失败，说明总线正在被其他主控占用，或总线错误
              该函数为IIC协议层，不可改动(已优化在确保安全稳定的前提下代码最简化、占用CPU时间最小化)，不可外部调用
 *	@Sampleusage:	IIC_Start();//启动信号
 */

bool IIC_Start(void)
{
	IIC_SCL = 1;//SCL = 1
  IIC_SDA = 1;//SDA = 1
  _nop_();
  if (IIC_SCL && IIC_SDA)//保证在发起启动信号前总线处于空闲状态，即IIC_SDA与IIC_SCL都处于高电平状态
	{
		IIC_SDA = 0;//SDA = 0
		IIC_delay();
		if (IIC_SDA) return false;//数据线未能拉低
		else //数据线以拉低
		{
			IIC_SCL = 0;//SCL = 0
			_nop_();
			if(IIC_SCL) return false;//时钟线未能拉低
			else return true; //时钟线以拉低，开始信号传输完毕
		}
	}
  else return false;//总线未处于空闲状态
}

/*!
 *	@brief		IIC停止信号
 *	@param		
 *	@warning	该函数为IIC协议层，不可改动(已优化在确保安全稳定的前提下代码最简化、占用CPU时间最小化)，不可外部调用
 *	@Sampleusage:	IIC_Stop();//停止信号
 */

void IIC_Stop(void)
{
	IIC_SCL = 0;//SCL = 0
	IIC_SDA = 0;//SDA = 0
	IIC_delay();
	IIC_SCL = 1;//SCL = 1
	IIC_delay();
	IIC_SDA = 1;//SDA = 1
}

/*!
 *	@brief		IIC主机接收应答信号，告诉从机你发送给我(主机)的数据我已收到
 *	@param		
 *	@warning	该函数为IIC协议层，不可改动(已优化在确保安全稳定的前提下代码最简化、占用CPU时间最小化)，不可外部调用
 *	@Sampleusage:	IIC_Ack();
 */

void IIC_Ack(void)
{
	IIC_SDA = 0;//SDA = 0
	IIC_delay();
	IIC_SCL = 1;//SCL = 1
	IIC_delay();
	IIC_SCL = 0;//SCL = 0
}

/*!
 *	@brief		IIC主机接收回复非应答信号，告诉从机你发送给我(主机)的数据我没收到
 *	@param		
 *	@warning	该函数为IIC协议层，不可改动(已优化在确保安全稳定的前提下代码最简化、占用CPU时间最小化)，不可外部调用
 *	@Sampleusage:	IIC_NoAck();
 */

void IIC_NoAck(void)
{
	IIC_SDA = 1;//SDA = 1
	IIC_delay();
	IIC_SCL = 1;//SCL = 1
	IIC_delay();
	IIC_SCL = 0;//SCL = 0
}

/*!
 *	@brief		IIC主机接收应答信号
 *	@param		
 *	@warning	该函数为IIC协议层，不可改动(已优化在确保安全稳定的前提下代码最简化、占用CPU时间最小化)，不可外部调用
 *	@Sampleusage:	IIC_GetAck();
 */

bool IIC_GetAck(void)
{
	IIC_SDA = 1;//SDA = 1
	IIC_delay();
	IIC_SCL = 1;//SCL = 1
	IIC_delay();
	if(IIC_SDA)//从机回复非应答信号
	{
		IIC_SCL = 0;//SCL = 0
		IIC_SDA = 0;//SDA = 0
		return false;//从机接收此帧数据失败
	}
	else //从机回复应答信号
	{
		IIC_SDA = 0;//SDA = 0
		IIC_SCL = 0;//SCL = 0
		return true;//从机接收此帧数据成功
	}
}

/*!
 *	@brief		IIC主机发送8位数据
 *	@param		
 *	@warning	在IIC协议内部的某8个信号驱动
              该函数为IIC协议层，不可改动(已优化在确保安全稳定的前提下代码最简化、占用CPU时间最小化)，不可外部调用
 *	@Sampleusage:	IIC_SendByte(0x88)
 */

void IIC_SendByte(uint8 x)
{
	uint8 n=8;
	while(n--)
	{
		IIC_SCL = 0;//SCL = 0
		IIC_SDA = x & 0x80;//准备发送一个位的数据
		x <<= 1;
		IIC_delay();
		IIC_SCL = 1;//SCL = 1
	  IIC_delay();
	}
	IIC_SCL = 0;//SCL = 0
}

/*!
 *	@brief		IIC主机接收8位数据
 *	@param		
 *	@warning	在IIC协议内部的某8个信号驱动
              该函数为IIC协议层，不可改动(已优化在确保安全稳定的前提下代码最简化、占用CPU时间最小化)，不可外部调用
 *	@Sampleusage:	IIC_ReceiveByte();
 */

uint8 IIC_ReceiveByte(void)
{
	uint8 n=8 , byte=0;
	IIC_SDA = 1;//SDA = 1
	while(n--)
	{
		byte <<= 1;
		IIC_SCL = 0;//SCL = 0
	  IIC_delay();
		IIC_SCL = 1;//SCL = 1
	  IIC_delay();
	  byte |= IIC_SDA;
	}
	IIC_SCL = 0;//SCL = 0
	return byte;
}

/*!
 *	@brief		IIC主机等待从机准备好数据，并接收从机发过来的8位数据
 *	@param		
 *	@warning	在IIC协议内部的某8个信号驱动
              该函数为IIC协议层，不可改动(已优化在确保安全稳定的前提下代码最简化、占用CPU时间最小化)，不可外部调用
 *	@Sampleusage:	IIC_Wait_ReceiveByte();
 */

uint8 IIC_Wait_ReceiveByte(void)
{
	uint8 n=7 , byte=0;
	IIC_SDA = 1;//SDA = 1
	IIC_SCL = 0;//SCL = 0
	IIC_delay();
  IIC_SCL = 1;//SCL = 1
	while(!IIC_SCL);//等待从机准备好要发送的数据(操作为检测从机释放SCL线)
	IIC_delay();
	byte |= IIC_SDA;
	while(n--)
	{
		byte <<= 1;
		IIC_SCL = 0;//SCL = 0
	  IIC_delay();
		IIC_SCL = 1;//SCL = 1
	  IIC_delay();
	  byte |= IIC_SDA;
	}
	IIC_SCL = 0;//SCL = 0
	return byte;
}

/*!
 *	@brief		向IIC从机发送写寄存器数据指令
 *	@param		addr  从机地址
              reg   需要操作的寄存器地址
              Data  需要写入从机的数据
 *	@warning	addr为从设备的7bit地址用十六进制表示
              该函数只能写一个字节的数据，结束后会发送IIC结束信号，故不能发送多字节数据
              该函数有返回值可判定写1个字节操作是否成功，0-失败、1-成功
 *	@Sampleusage:	IIC_Write_Reg(0x1e , 0x00 , 0x10);
 */

bool IIC_Write_Reg(uint8 addr , uint8 reg , uint8 Data)
{
	if (!IIC_Start()) return false;
  IIC_SendByte(addr << 1 | IIC_Direction_Transmitter);
  if (!IIC_GetAck())
	{
    IIC_Stop();
    return false;
  }
  IIC_SendByte(reg);
  if (!IIC_GetAck())
	{
    IIC_Stop();
    return false;
  }
  IIC_SendByte(Data);
	if (!IIC_GetAck())
	{
    IIC_Stop();
    return false;
  }
  IIC_Stop();
  return true;
}

/*!
 *	@brief		向IIC从机索要寄存器数据指令
 *	@param		addr  从机地址
              reg   需要操作的寄存器地址
 *	@warning	addr为从设备的7bit地址用十六进制表示
              该函数只能读一个字节的数据，结束后会发送IIC结束信号，故不能接收多字节数据
              注意：该函数没有纠错能力，故不能得知读操作所得数据是否正确，所有总线操作属于开环操作，这样做可大大提升读取速度
 *	@Sampleusage:	IIC_Read_Reg(0x1e , 0x00);
 */

uint8 IIC_Read_Reg(uint8 addr , uint8 reg)
{
	uint8 Data=0;
	IIC_Start();
  IIC_SendByte(addr << 1 | IIC_Direction_Transmitter);
  IIC_GetAck();
  IIC_SendByte(reg);
  IIC_GetAck();
	IIC_Stop();
  IIC_Start();
  IIC_SendByte(addr << 1 | IIC_Direction_Receiver);
  IIC_GetAck();
  Data = IIC_Wait_ReceiveByte();
  IIC_NoAck();
  IIC_Stop();
  return Data;
}

/*!
 *	@brief		向某个IIC器件的某个寄存器开始(寄存器地址最大支持32位宽)填入一组数据(数据流长度最大支持255字节)
 *	@param		addr     IIC器件物理地址
              reg_wide 寄存器地址位宽(可选位宽: bit_wide_8 , bit_wide_16 , bit_wide_32)
              reg      对应位宽的寄存器地址
              len      要发送的数据流长度(单位:字节)
              *Data    数据流数组首地址(以取地址符号&传入函数)
 *	@warning	若寄存器位宽与填入的寄存器地址不符，则按照设置的位宽取低位侧发送，此时IIC器件将工作紊乱
              注意数据流长度与数据流数组长度的匹配，必要时可使用sizeof()函数检测传入
 *	@Sampleusage:	IIC_Write(0x44 , bit_wide_8 , 0x20 , 1 , &Data);
 */

bool IIC_Write(uint8 addr , bit_wide reg_wide , uint32 reg , uint8 len , uint8 *Data)
{
	if (!IIC_Start()) return false;
	IIC_SendByte(addr << 1 | IIC_Direction_Transmitter);
	if (!IIC_GetAck())
	{
    IIC_Stop();
    return false;
  }
	while(reg_wide--)
	{
		IIC_SendByte(reg >> (8*reg_wide) & 0xff);
		if (!IIC_GetAck())
		{
			IIC_Stop();
			return false;
		}
	}
	while(len--)
	{
		IIC_SendByte(*Data++);
		if (!IIC_GetAck())
		{
			IIC_Stop();
			return false;
		}
	}
	IIC_Stop();
  return true;
}

/*!
 *	@brief		向某个IIC器件的某个寄存器开始(寄存器地址最大支持32位宽)接收一组数据(数据流长度最大支持255字节)
 *	@param		addr     IIC器件物理地址
              reg_wide 寄存器地址位宽(可选位宽: bit_wide_8 , bit_wide_16 , bit_wide_32)
              reg      对应位宽的寄存器地址
              len      要接收的数据流长度(单位:字节)
              *Data    数据流数组首地址(以取地址符号&传入函数)
              函数实体第一行n为从机回复NoAck重试次数，没有出现在输入参数中，因为它并不常用，但可根据器件响应速度与本函数内重试循环部分所用时间进行调整
 *	@warning	若寄存器位宽与填入的寄存器地址不符，则按照设置的位宽取低位侧发送，此时IIC器件将工作紊乱
              注意数据流长度与数据流数组长度的匹配，具体长度应查看IIC器件手册！
 *	@Sampleusage:	IIC_Read(0x44 , bit_wide_16 , 0x2c06 , 6 , &BUF);
 */

bool IIC_Read(uint8 addr , bit_wide reg_wide , uint32 reg , uint8 len , uint8 *buf)
{
	uint8 n=10;//从机回复NoAck重试次数
	if (!IIC_Start()) return false;
	IIC_SendByte(addr << 1 | IIC_Direction_Transmitter);
	if (!IIC_GetAck())
	{
    IIC_Stop();
    return false;
  }
	while(reg_wide--)
	{
		IIC_SendByte(reg >> (8*reg_wide) & 0xff);
		if (!IIC_GetAck())
		{
			IIC_Stop();
			return false;
		}
	}
	IIC_Stop();
	while(n--)
	{
		if (!IIC_Start()) return false;
		IIC_SendByte(addr << 1 | IIC_Direction_Receiver);
		if (IIC_GetAck()) break;
		else IIC_Stop();
	}
	if(n==0) return false;
	*buf++ = IIC_Wait_ReceiveByte();
	len--;
	while(len--)
	{
		IIC_Ack();
		*buf++ = IIC_ReceiveByte();
	}
	IIC_NoAck();
  IIC_Stop();
	return true;
}
