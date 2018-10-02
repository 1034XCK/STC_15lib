#include "common.h"
#include "STC_LCD_1602.h"

/*!
 *	@brief		LCD1602写指令函数
 *	@param		com				指令码
 *	@warning	指令码是8位的
 *	@Sampleusage:	write_LCD1602_com(0x38); //显示模式设置：16×2显示，5×7点阵，8位数据接口
 */
 
void write_LCD1602_com(uint8 com)//LCD1602写指令函数
{
	LCD1602_RS = 0;
	LCD1602_RW = 0;
	LCD1602_EN = 0;
	LCD1602_D0 = BIT_GET(com,0);
	LCD1602_D1 = BIT_GET(com,1);
	LCD1602_D2 = BIT_GET(com,2);
	LCD1602_D3 = BIT_GET(com,3);
	LCD1602_D4 = BIT_GET(com,4);
	LCD1602_D5 = BIT_GET(com,5);
	LCD1602_D6 = BIT_GET(com,6);
	LCD1602_D7 = BIT_GET(com,7);
	LCD1602_EN = 1;
	_nop_();
	LCD1602_EN = 0;
}

/*!
 *	@brief		LCD1602写数据函数
 *	@param		date				数据码
 *	@warning	数据吗是8位的
 *	@sampleusage:	write_LCD1602_date(0x48); //显示ascii码0x48
 */

void write_LCD1602_date(uint8 date)//LCD1602写数据函数
{
	LCD1602_RS = 1;
	LCD1602_RW = 0;
	LCD1602_EN = 0;
	LCD1602_D0 = BIT_GET(date,0);
	LCD1602_D1 = BIT_GET(date,1);
	LCD1602_D2 = BIT_GET(date,2);
	LCD1602_D3 = BIT_GET(date,3);
	LCD1602_D4 = BIT_GET(date,4);
	LCD1602_D5 = BIT_GET(date,5);
	LCD1602_D6 = BIT_GET(date,6);
	LCD1602_D7 = BIT_GET(date,7);
	LCD1602_EN = 1;
	_nop_();
	LCD1602_EN = 0;
}

/*!
 *	@brief		等待LCD1602忙完并给足反应延时时间
 *	@param		
 *	@warning	不同厂家生产的屏幕反应时间差别较大，如遇见不能显示或显示不正常请将延时改大
 *	@sampleusage:	wait_LCD1602_busy_delay(); //等待LCD1602忙完并给予充分的反应时间
 */

void wait_LCD1602_busy_delay(void)//等待LCD1602忙完并给予充分的反应时间
{
	LCD1602_RS = 0;
	LCD1602_RW = 1;
	LCD1602_EN = 1;
	_nop_();
	while(LCD1602_D7==1);
	LCD1602_EN = 0;
	LCD1602_RS = 0;
	LCD1602_RW = 0;
	DELAY_US(750);
}

/*!
 *	@brief		LCD1602老手初始化函数
 *	@param		
 *	@warning	显示模式设置：16×2显示，5×7点阵，8位数据接口
 *	@sampleusage:	init_LCD1602(); //最简单的初始化，其他功能需自己设定
 */

void init_LCD1602(void)//LCD1602简单始化函数
{
	LCD1602_LED= 1;
	LCD1602_EN = 0;
	LCD1602_RW = 0;
	LCD1602_RS = 0;
	LCD1602_D0 = 0;
	LCD1602_D1 = 0;
	LCD1602_D2 = 0;
	LCD1602_D3 = 0;
	LCD1602_D4 = 0;
	LCD1602_D5 = 0;
	LCD1602_D6 = 0;
	LCD1602_D7 = 0;
	DELAY_MS(15);
	write_LCD1602_com(0x38);
	DELAY_MS(5);
	write_LCD1602_com(0x38);
	DELAY_MS(5);
	write_LCD1602_com(0x38);
	wait_LCD1602_busy_delay();
	write_LCD1602_com(0x38);
}

/*!
 *	@brief		LCD1602新手初始化函数
 *	@param		
 *	@warning	显示模式设置：16×2显示，5×7点阵，8位数据接口
 *	@warning	开显示，不显示光标
 *	@warning	写一个字符后地址指针自动加1
 *	@warning	清屏
 *	@sampleusage:	commoninit_init_LCD1602(); //已设置基本功能的初始化
 */

void commoninit_init_LCD1602(void)//普通初始化函数
{
	LCD1602_LED= 1;
	LCD1602_EN = 0;
	LCD1602_RW = 0;
	LCD1602_RS = 0;
	LCD1602_D0 = 0;
	LCD1602_D1 = 0;
	LCD1602_D2 = 0;
	LCD1602_D3 = 0;
	LCD1602_D4 = 0;
	LCD1602_D5 = 0;
	LCD1602_D6 = 0;
	LCD1602_D7 = 0;
	DELAY_MS(15);
	write_LCD1602_com(0x38);
	DELAY_MS(5);
	write_LCD1602_com(0x38);
	DELAY_MS(5);
	write_LCD1602_com(0x38);
	wait_LCD1602_busy_delay();
	write_LCD1602_com(0x38);
	wait_LCD1602_busy_delay();
	write_LCD1602_com(0x08);
	wait_LCD1602_busy_delay();
	write_LCD1602_com(0x01);
	wait_LCD1602_busy_delay();
	write_LCD1602_com(0x06);
	wait_LCD1602_busy_delay();
	write_LCD1602_com(0x0c);
}

/*!
 *	@brief		LCD1602显示设置函数
 *	@param		com				指令码
 *	@warning	0x0×：0000_1abc：a=1开显示，b=1显示光标，c=1光标闪烁
							0x0×：0000_01ab：a=1当读或写一个字符后地址指针自动+1且光标+1/反之-1
															 b当写一个字符时整屏左移(a=1)或右移(a=0)以得到光标不移动而屏幕移动的效果/反之不移动
							0x10：光标左移
							0x14：光标右移
							0x18：整屏左移同时光标更随移动
							0x1c：整屏右移同时光标更随移动
							0x01：清屏（指针及数据归零）
 *	@sampleusage:	display_setup_LCD1602(0x01); //清屏
 */

void display_setup_LCD1602(uint8 com)//LCD1602显示设置函数
{
	wait_LCD1602_busy_delay();
	write_LCD1602_com(com);
}

































/*!
 *	@brief		显示一个字符于line行list列
 *	@param		line				要显示到第几行(从1开始， 2结束)
							list				要显示到第几列(从1开始，16结束)
							character		要显示的字符的ASCII码值
 *	@warning	行列超出部分将不显示
 *	@sampleusage:	LCD1602_display_achar(2,8,0x41); //在LCD1602的下排第8个位置显示
 */

void LCD1602_display_achar(uint8 line,uint8 list,uint8 character)//显示一个字符于line行list列
{
	if(line>2)line=2;
	else if(line<1)line=1;
	if(list>16)list=16;
	else if(list<1)list=1;
	if(line==1)
	{
		wait_LCD1602_busy_delay();
		write_LCD1602_com(0x80+list-1);
		wait_LCD1602_busy_delay();
		write_LCD1602_date(character);
	}
	else if(line==2)
	{
		wait_LCD1602_busy_delay();
		write_LCD1602_com(0x80+0x40+list-1);
		wait_LCD1602_busy_delay();
		write_LCD1602_date(character);
	}
}

/*!
 *	@brief		显示一串字符于line行list列
 *	@param		line				要显示到第几行(从1开始， 2结束)
							list				要显示到第几列(从1开始，16结束)
							*p					要显示的字符串数组的地址
 *	@warning	传入的字符串必须以数组取地址的形式传入(&a)
							字符串位数+list>16将不能显示
							行列超出部分将不显示
 *	@sampleusage:	LCD1602_display_array(1,2,&A); //在LCD1602的上排第2个位置开始显示A数组中存放的字符串
 */

void LCD1602_display_array(uint8 line,uint8 list,uint8 *p)//显示一字符串于line行list列
{
	uint8 num=16;
	if(line>2)line=2;
	else if(line<1)line=1;
	if(list>16)list=16;
	else if(list<1)list=1;
		if(line==1)
	{
		wait_LCD1602_busy_delay();
		write_LCD1602_com(0x80+list-1);
		while(num--)
		{
			if(*p=='\0')break;
			wait_LCD1602_busy_delay();
			write_LCD1602_date(*p++);
		}
	}
	else if(line==2)
	{
		wait_LCD1602_busy_delay();
		write_LCD1602_com(0x80+0x40+list-1);
		while(num--)
		{
			if(*p==0)break;
			wait_LCD1602_busy_delay();
			write_LCD1602_date(*p++);
		}
	}
}

/*!
 *	@brief		显示一uint8型数字于line行list列
 *	@param		line				要显示到第几行(从1开始， 2结束)
							list				要显示到第几列(从1开始，16结束)
							num					要显示的数字  (显示的数字范围0~255)
 *	@warning	行列超出部分将不显示
 *	@sampleusage:	LCD1602_display_uint8_number(1,2,208); //在第一行第二个格子开始显示“208”
 */

void LCD1602_display_uint8_number(uint8 line,uint8 list,uint8 num)//显示一uint8型数字于line行list列
{
	if(line>2)line=2;
	else if(line<1)line=1;
	if(list>14)list=14;
	else if(list<1)list=1;
	if(line==1)
	{
		wait_LCD1602_busy_delay();
		write_LCD1602_com(0x80+list-1);
		wait_LCD1602_busy_delay();
		write_LCD1602_date(num/100+'0');
		wait_LCD1602_busy_delay();
		write_LCD1602_date(num/10%10+'0');
		wait_LCD1602_busy_delay();
		write_LCD1602_date(num%100%10+'0');
	}
	else if(line==2)
	{
		wait_LCD1602_busy_delay();
		write_LCD1602_com(0x80+0x40+list-1);
		wait_LCD1602_busy_delay();
		write_LCD1602_date(num/100+'0');
		wait_LCD1602_busy_delay();
		write_LCD1602_date(num/10%10+'0');
		wait_LCD1602_busy_delay();
		write_LCD1602_date(num%100%10+'0');
	}
}

/*!
 *	@brief		显示一int8型数字于line行list列
 *	@param		line				要显示到第几行(从1开始， 2结束)
							list				要显示到第几列(从1开始，16结束)
							num					要显示的数字  (显示的数字范围-127~+127)
 *	@warning	若要显示的数字是正数则最高位显示在line行list列
							若要显示的数字是负数则“-”号会显示在line行list列，数值最高位会显示在line行list+1列
							行列超出部分将不显示
 *	@sampleusage:	LCD1602_display_int8_number(2,2,-127); //在第二排第二个格子开始显示“-127”
 */

void LCD1602_display_int8_number(uint8 line,uint8 list,int8 num)//显示一int8型数字于line行list列
{
	if(line>2)line=2;
	else if(line<1)line=1;
	if(list>14)list=14;
	else if(list<2)list=2;
	if(line==1)
	{
		if(num<0)
		{
			if(list==1)
			{
				wait_LCD1602_busy_delay();
				write_LCD1602_com(0x80);
				wait_LCD1602_busy_delay();
				write_LCD1602_date('-');
			}
			else
			{
				wait_LCD1602_busy_delay();
				write_LCD1602_com(0x80+list-2);
				wait_LCD1602_busy_delay();
				write_LCD1602_date('-');
			}
			num=-num;
		}
		else 
		{
			wait_LCD1602_busy_delay();
			write_LCD1602_com(0x80+list-2);
			wait_LCD1602_busy_delay();
			write_LCD1602_date(' ');
		}
		wait_LCD1602_busy_delay();
		write_LCD1602_date(num/100+'0');
		wait_LCD1602_busy_delay();
		write_LCD1602_date(num/10%10+'0');
		wait_LCD1602_busy_delay();
		write_LCD1602_date(num%100%10+'0');
	}
	else if(line==2)
	{
		if(num<0)
		{
			if(list==1)
			{
				wait_LCD1602_busy_delay();
				write_LCD1602_com(0x80+0x40);
				wait_LCD1602_busy_delay();
				write_LCD1602_date('-');
			}
			else
			{
				wait_LCD1602_busy_delay();
				write_LCD1602_com(0x80+0x40+list-2);
				wait_LCD1602_busy_delay();
				write_LCD1602_date('-');
			}
			num=-num;
		}
		else 
		{
			wait_LCD1602_busy_delay();
			write_LCD1602_com(0x80+0x40+list-2);
			wait_LCD1602_busy_delay();
			write_LCD1602_date(' ');
		}
		wait_LCD1602_busy_delay();
		write_LCD1602_date(num/100+'0');
		wait_LCD1602_busy_delay();
		write_LCD1602_date(num/10%10+'0');
		wait_LCD1602_busy_delay();
		write_LCD1602_date(num%100%10+'0');
	}	
}

/*!
 *	@brief		显示一uint16型数字于line行list列
 *	@param		line				要显示到第几行(从1开始， 2结束)
							list				要显示到第几列(从1开始，16结束)
							num					要显示的数字  (显示的数字范围0~65535)
 *	@warning	行列超出部分将不显示
 *	@sampleusage:	LCD1602_display_uint16_number(1,1,65535); //在第一排第一个格子开始显示“65535”
 */

void LCD1602_display_uint16_number(uint8 line,uint8 list,uint16 num)//显示一uint16型数字于line行list列
{
	if(line>2)line=2;
	else if(line<1)line=1;
	if(list>12)list=12;
	else if(list<1)list=1;
	if(line==1)
	{
		wait_LCD1602_busy_delay();
		write_LCD1602_com(0x80+list-1);
		wait_LCD1602_busy_delay();
		write_LCD1602_date(num/10000+'0');
		wait_LCD1602_busy_delay();
		write_LCD1602_date(num/1000%10+'0');
		wait_LCD1602_busy_delay();
		write_LCD1602_date(num/100%100%10+'0');
		wait_LCD1602_busy_delay();
		write_LCD1602_date(num/10%1000%100%10+'0');
		wait_LCD1602_busy_delay();
		write_LCD1602_date(num/1%10000%1000%100%10+'0');
	}
	else if(line==2)
	{
		wait_LCD1602_busy_delay();
		write_LCD1602_com(0x80+0x40+list-1);
		wait_LCD1602_busy_delay();
		write_LCD1602_date(num/10000+'0');
		wait_LCD1602_busy_delay();
		write_LCD1602_date(num/1000%10+'0');
		wait_LCD1602_busy_delay();
		write_LCD1602_date(num/100%100%10+'0');
		wait_LCD1602_busy_delay();
		write_LCD1602_date(num/10%1000%100%10+'0');
		wait_LCD1602_busy_delay();
		write_LCD1602_date(num/1%10000%1000%100%10+'0');
	}
}

/*!
 *	@brief		显示一int16型数字于line行list列
 *	@param		line				要显示到第几行(从1开始， 2结束)
							list				要显示到第几列(从1开始，16结束)
							num					要显示的数字  (显示的数字范围-32768~32767)
 *	@warning	行列超出部分将不显示
 *	@sampleusage:	LCD1602_display_int16_number(1,1,-32767); //在第一排第一个格子开始显示“-32767”
 */

void LCD1602_display_int16_number(uint8 line,uint8 list,int num)//显示一int16型数字于line行list列
{
	if(line>2)line=2;
	else if(line<1)line=1;
	if(list>12)list=12;
	else if(list<2)list=2;
	if(line==1)
	{
		if(num<0)
		{
			if(list==1)
			{
				wait_LCD1602_busy_delay();
				write_LCD1602_com(0x80);
				wait_LCD1602_busy_delay();
				write_LCD1602_date('-');
			}
			else
			{
				wait_LCD1602_busy_delay();
				write_LCD1602_com(0x80+list-2);
				wait_LCD1602_busy_delay();
				write_LCD1602_date('-');
			}
			num=-num;
		}
		else 
		{
			wait_LCD1602_busy_delay();
			write_LCD1602_com(0x80+list-2);
			wait_LCD1602_busy_delay();
			write_LCD1602_date(' ');
		}
		wait_LCD1602_busy_delay();
		write_LCD1602_date(num/10000+'0');
		wait_LCD1602_busy_delay();
		write_LCD1602_date(num/1000%10+'0');
		wait_LCD1602_busy_delay();
		write_LCD1602_date(num/100%100%10+'0');
		wait_LCD1602_busy_delay();
		write_LCD1602_date(num/10%1000%100%10+'0');
		wait_LCD1602_busy_delay();
		write_LCD1602_date(num%10000%1000%100%10+'0');
	}
	else if(line==2)
	{
		if(num<0)
		{
			if(list==1)
			{
				wait_LCD1602_busy_delay();
				write_LCD1602_com(0x80+0x40);
				wait_LCD1602_busy_delay();
				write_LCD1602_date('-');
			}
			else
			{
				wait_LCD1602_busy_delay();
				write_LCD1602_com(0x80+0x40+list-2);
				wait_LCD1602_busy_delay();
				write_LCD1602_date('-');
			}
			num=-num;
		}
		else 
		{
			wait_LCD1602_busy_delay();
			write_LCD1602_com(0x80+0x40+list-2);
			wait_LCD1602_busy_delay();
			write_LCD1602_date(' ');
		}
		wait_LCD1602_busy_delay();
		write_LCD1602_date(num/10000+'0');
		wait_LCD1602_busy_delay();
		write_LCD1602_date(num/1000%10+'0');
		wait_LCD1602_busy_delay();
		write_LCD1602_date(num/100%100%10+'0');
		wait_LCD1602_busy_delay();
		write_LCD1602_date(num/10%1000%100%10+'0');
		wait_LCD1602_busy_delay();
		write_LCD1602_date(num%10000%1000%100%10+'0');
	}	
}

/*!
 *	@brief		显示一uint32型数字于line行list列
 *	@param		line				要显示到第几行(从1开始， 2结束)
							list				要显示到第几列(从1开始，16结束)
							num					要显示的数字  (显示的数字范围0~4294967295)
 *	@warning	行列超出部分将不显示
 *	@sampleusage:	LCD1602_display_uint32_number(1,1,4294967295); //在第一排第一个格子开始显示“4294967295”
 */

void LCD1602_display_uint32_number(uint8 line,uint8 list,uint32 num)//显示一uint32型数字于line行list列
{
	if(line>2)line=2;
	else if(line<1)line=1;
	if(list>12)list=12;
	else if(list<1)list=1;
	if(line==1)
	{
		wait_LCD1602_busy_delay();
		write_LCD1602_com(0x80+list-1);
		wait_LCD1602_busy_delay();
		write_LCD1602_date(num/1000000000L+'0');
		wait_LCD1602_busy_delay();
		write_LCD1602_date(num/100000000L%10L+'0');
		wait_LCD1602_busy_delay();
		write_LCD1602_date(num/10000000L%100L%10L+'0');
		wait_LCD1602_busy_delay();
		write_LCD1602_date(num/1000000L%1000L%100L%10L+'0');
		wait_LCD1602_busy_delay();
		write_LCD1602_date(num/100000L%10000L%1000L%100L%10L+'0');
		wait_LCD1602_busy_delay();
		write_LCD1602_date(num/10000L%100000L%10000L%1000L%100L%10L+'0');
		wait_LCD1602_busy_delay();
		write_LCD1602_date(num/1000L%1000000L%100000L%10000L%1000L%100L%10L+'0');
		wait_LCD1602_busy_delay();
		write_LCD1602_date(num/100L%10000000L%1000000L%100000L%10000L%1000L%100L%10L+'0');
		wait_LCD1602_busy_delay();
		write_LCD1602_date(num/10L%100000000L%10000000L%1000000L%100000L%10000L%1000L%100L%10L+'0');
		wait_LCD1602_busy_delay();
		write_LCD1602_date(num/1L%1000000000L%100000000L%10000000L%1000000L%100000L%10000L%1000L%100L%10L+'0');
	}
	else if(line==2)
	{
		wait_LCD1602_busy_delay();
		write_LCD1602_com(0x80+0x40+list-1);
		wait_LCD1602_busy_delay();
		write_LCD1602_date(num/1000000000L+'0');
		wait_LCD1602_busy_delay();
		write_LCD1602_date(num/100000000L%10L+'0');
		wait_LCD1602_busy_delay();
		write_LCD1602_date(num/10000000L%100L%10L+'0');
		wait_LCD1602_busy_delay();
		write_LCD1602_date(num/1000000L%1000L%100L%10L+'0');
		wait_LCD1602_busy_delay();
		write_LCD1602_date(num/100000L%10000L%1000L%100L%10L+'0');
		wait_LCD1602_busy_delay();
		write_LCD1602_date(num/10000L%100000L%10000L%1000L%100L%10L+'0');
		wait_LCD1602_busy_delay();
		write_LCD1602_date(num/1000L%1000000L%100000L%10000L%1000L%100L%10L+'0');
		wait_LCD1602_busy_delay();
		write_LCD1602_date(num/100L%10000000L%1000000L%100000L%10000L%1000L%100L%10L+'0');
		wait_LCD1602_busy_delay();
		write_LCD1602_date(num/10L%100000000L%10000000L%1000000L%100000L%10000L%1000L%100L%10L+'0');
		wait_LCD1602_busy_delay();
		write_LCD1602_date(num/1L%1000000000L%100000000L%10000000L%1000000L%100000L%10000L%1000L%100L%10L+'0');
	}
}
