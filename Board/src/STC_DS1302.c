#include "common.h"
#include "STC_DS1302.h"

/*!
 *	@brief		��DS1302д��һ���ֽ�
 *	@param		dat Ҫд������ݣ�������ַ���ݣ�
 *	@warning	�κβ���һ��Ҫ��д������ַ
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
 *	@brief		��DS1302��ȡһ���ֽ�
 *	@param		
 *	@warning	һ���Ǹ���write_Byte_DS1302()��������
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
 *	@brief		��DS1302д��һ�ֽ�����
 *	@param		adr Ҫд��ĵ�ַ�������
 *	@param		dat Ҫд��ľ�������
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
 *	@brief		��ȡDS1302ĳһ��ַ�ڵ�����
 *	@param		adr Ҫ��ȡ�ļĴ�����ַ
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
 *	@brief		DS1302��ʼ��
 *	@param		
 *	@warning	
 *	@sampleusage:	
 */

void init_DS1302(void)
{
	write_DS1302(0x8e,0x00);//д����      �ر�
	write_DS1302(0x80,0x00);//��Ĵ���    0
	write_DS1302(0x82,0x08);//���ӼĴ���  0
	write_DS1302(0x84,0x00);//Сʱ�Ĵ���  0
	write_DS1302(0x86,0x01);//��Ĵ���    1
	write_DS1302(0x88,0x01);//�¼Ĵ���    1
	write_DS1302(0x8a,0x01);//���ڼĴ���  1
	write_DS1302(0x8c,0x07);//��Ĵ���    00
	write_DS1302(0x90,0xa5);//���Ĵ���
	write_DS1302(0xc0,0xaa);//��ʼ��һ�α�־
	write_DS1302(0x8e,0x80);//д����      ����
}