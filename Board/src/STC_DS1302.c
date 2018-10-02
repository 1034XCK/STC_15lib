#include "common.h"
#include "STC_DS1302.h"

/*!
 *	@brief		向DS1302写入一个字节
 *	@param		dat 要写入的数据（包括地址数据）
 *	@warning	任何操作一定要先写操作地址
 *	@sampleusage:	write_Byte_DS1302(0xff);
 */
void write_Byte_DS1302(uint8 dat)
{
	uint8 i=0;
	DS1302_CLK = 0;
	DELAY_US(2);
	for(i=0;i<8;i++)
	{
		DS1302_DAT = dat&0x01;
		DELAY_US(2);
		DS1302_CLK = 1;
		DELAY_US(2);
		DS1302_CLK = 0;
		dat >>= 1;
	}
}

/*!
 *	@brief		从DS1302读取一个字节
 *	@param		
 *	@warning	一定是跟在write_Byte_DS1302()函数后面
 *	@sampleusage:	day = read_Byte_DS1302();
 */

uint8 read_Byte_DS1302(void)
{
	uint8 i=0 , dat=0;
	DELAY_US(2);
	for(i=0;i<8;i++)
	{
		if(DS1302_DAT) dat |= 0x80;
		DS1302_CLK = 1;
		DELAY_US(2);
		DS1302_CLK = 0;
		DELAY_US(2);
		dat >>= 1;
	}
	return dat;
}

/*!
 *	@brief		向DS1302写入一字节数据
 *	@param		adr 要写入的地址或操作数
 *	@param		dat 要写入的具体数据
 *	@warning	
 *	@sampleusage:	write_DS1302(0x8e,0x00);
 */

void write_DS1302(uint8 adr , uint8 dat)
{
	DS1302_CE  = 0;
	DS1302_CLK = 0;
	DS1302_CE  = 1;
	write_Byte_DS1302(adr);
	write_Byte_DS1302(dat);
	DS1302_CE  = 0;
}

/*!
 *	@brief		读取DS1302某一地址内的数据
 *	@param		adr 要读取的寄存器地址
 *	@warning	
 *	@sampleusage:	sec = read_DS1302(0x81);
 */

uint8 read_DS1302(uint8 adr)
{
	uint8 dat = 0;
	DS1302_CE  = 0;
	DS1302_CLK = 0;
	DS1302_CE  = 1;
	write_Byte_DS1302(adr);
	dat = read_Byte_DS1302();
	DS1302_CE  = 0;
	return dat;
}

/*!
 *	@brief		DS1302初始化
 *	@param		
 *	@warning	
 *	@sampleusage:	
 */

void init_DS1302(void)
{
	write_DS1302(0x8e,0x00);//写保护      关闭
	write_DS1302(0x80,0x00);//秒寄存器    0
	write_DS1302(0x82,0x08);//分钟寄存器  0
	write_DS1302(0x84,0x00);//小时寄存器  0
	write_DS1302(0x86,0x01);//天寄存器    1
	write_DS1302(0x88,0x01);//月寄存器    1
	write_DS1302(0x8a,0x01);//星期寄存器  1
	write_DS1302(0x8c,0x07);//年寄存器    00
	write_DS1302(0x90,0xa5);//充电寄存器
	write_DS1302(0xc0,0xaa);//初始化一次标志
	write_DS1302(0x8e,0x80);//写保护      开启
}