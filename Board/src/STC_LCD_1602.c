#include "common.h"
#include "STC_LCD_1602.h"

/*!
 *	@brief		LCD1602дָ���
 *	@param		com				ָ����
 *	@warning	ָ������8λ��
 *	@Sampleusage:	write_LCD1602_com(0x38); //��ʾģʽ���ã�16��2��ʾ��5��7����8λ���ݽӿ�
 */
 
void write_LCD1602_com(uint8 com)//LCD1602дָ���
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
 *	@brief		LCD1602д���ݺ���
 *	@param		date				������
 *	@warning	��������8λ��
 *	@sampleusage:	write_LCD1602_date(0x48); //��ʾascii��0x48
 */

void write_LCD1602_date(uint8 date)//LCD1602д���ݺ���
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
 *	@brief		�ȴ�LCD1602æ�겢���㷴Ӧ��ʱʱ��
 *	@param		
 *	@warning	��ͬ������������Ļ��Ӧʱ����ϴ�������������ʾ����ʾ�������뽫��ʱ�Ĵ�
 *	@sampleusage:	wait_LCD1602_busy_delay(); //�ȴ�LCD1602æ�겢�����ֵķ�Ӧʱ��
 */

void wait_LCD1602_busy_delay(void)//�ȴ�LCD1602æ�겢�����ֵķ�Ӧʱ��
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
 *	@brief		LCD1602���ֳ�ʼ������
 *	@param		
 *	@warning	��ʾģʽ���ã�16��2��ʾ��5��7����8λ���ݽӿ�
 *	@sampleusage:	init_LCD1602(); //��򵥵ĳ�ʼ���������������Լ��趨
 */

void init_LCD1602(void)//LCD1602��ʼ������
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
 *	@brief		LCD1602���ֳ�ʼ������
 *	@param		
 *	@warning	��ʾģʽ���ã�16��2��ʾ��5��7����8λ���ݽӿ�
 *	@warning	����ʾ������ʾ���
 *	@warning	дһ���ַ����ַָ���Զ���1
 *	@warning	����
 *	@sampleusage:	commoninit_init_LCD1602(); //�����û������ܵĳ�ʼ��
 */

void commoninit_init_LCD1602(void)//��ͨ��ʼ������
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
 *	@brief		LCD1602��ʾ���ú���
 *	@param		com				ָ����
 *	@warning	0x0����0000_1abc��a=1����ʾ��b=1��ʾ��꣬c=1�����˸
							0x0����0000_01ab��a=1������дһ���ַ����ַָ���Զ�+1�ҹ��+1/��֮-1
															 b��дһ���ַ�ʱ��������(a=1)������(a=0)�Եõ���겻�ƶ�����Ļ�ƶ���Ч��/��֮���ƶ�
							0x10���������
							0x14���������
							0x18����������ͬʱ�������ƶ�
							0x1c����������ͬʱ�������ƶ�
							0x01��������ָ�뼰���ݹ��㣩
 *	@sampleusage:	display_setup_LCD1602(0x01); //����
 */

void display_setup_LCD1602(uint8 com)//LCD1602��ʾ���ú���
{
	wait_LCD1602_busy_delay();
	write_LCD1602_com(com);
}

































/*!
 *	@brief		��ʾһ���ַ���line��list��
 *	@param		line				Ҫ��ʾ���ڼ���(��1��ʼ�� 2����)
							list				Ҫ��ʾ���ڼ���(��1��ʼ��16����)
							character		Ҫ��ʾ���ַ���ASCII��ֵ
 *	@warning	���г������ֽ�����ʾ
 *	@sampleusage:	LCD1602_display_achar(2,8,0x41); //��LCD1602�����ŵ�8��λ����ʾ
 */

void LCD1602_display_achar(uint8 line,uint8 list,uint8 character)//��ʾһ���ַ���line��list��
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
 *	@brief		��ʾһ���ַ���line��list��
 *	@param		line				Ҫ��ʾ���ڼ���(��1��ʼ�� 2����)
							list				Ҫ��ʾ���ڼ���(��1��ʼ��16����)
							*p					Ҫ��ʾ���ַ�������ĵ�ַ
 *	@warning	������ַ�������������ȡ��ַ����ʽ����(&a)
							�ַ���λ��+list>16��������ʾ
							���г������ֽ�����ʾ
 *	@sampleusage:	LCD1602_display_array(1,2,&A); //��LCD1602�����ŵ�2��λ�ÿ�ʼ��ʾA�����д�ŵ��ַ���
 */

void LCD1602_display_array(uint8 line,uint8 list,uint8 *p)//��ʾһ�ַ�����line��list��
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
 *	@brief		��ʾһuint8��������line��list��
 *	@param		line				Ҫ��ʾ���ڼ���(��1��ʼ�� 2����)
							list				Ҫ��ʾ���ڼ���(��1��ʼ��16����)
							num					Ҫ��ʾ������  (��ʾ�����ַ�Χ0~255)
 *	@warning	���г������ֽ�����ʾ
 *	@sampleusage:	LCD1602_display_uint8_number(1,2,208); //�ڵ�һ�еڶ������ӿ�ʼ��ʾ��208��
 */

void LCD1602_display_uint8_number(uint8 line,uint8 list,uint8 num)//��ʾһuint8��������line��list��
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
 *	@brief		��ʾһint8��������line��list��
 *	@param		line				Ҫ��ʾ���ڼ���(��1��ʼ�� 2����)
							list				Ҫ��ʾ���ڼ���(��1��ʼ��16����)
							num					Ҫ��ʾ������  (��ʾ�����ַ�Χ-127~+127)
 *	@warning	��Ҫ��ʾ�����������������λ��ʾ��line��list��
							��Ҫ��ʾ�������Ǹ�����-���Ż���ʾ��line��list�У���ֵ���λ����ʾ��line��list+1��
							���г������ֽ�����ʾ
 *	@sampleusage:	LCD1602_display_int8_number(2,2,-127); //�ڵڶ��ŵڶ������ӿ�ʼ��ʾ��-127��
 */

void LCD1602_display_int8_number(uint8 line,uint8 list,int8 num)//��ʾһint8��������line��list��
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
 *	@brief		��ʾһuint16��������line��list��
 *	@param		line				Ҫ��ʾ���ڼ���(��1��ʼ�� 2����)
							list				Ҫ��ʾ���ڼ���(��1��ʼ��16����)
							num					Ҫ��ʾ������  (��ʾ�����ַ�Χ0~65535)
 *	@warning	���г������ֽ�����ʾ
 *	@sampleusage:	LCD1602_display_uint16_number(1,1,65535); //�ڵ�һ�ŵ�һ�����ӿ�ʼ��ʾ��65535��
 */

void LCD1602_display_uint16_number(uint8 line,uint8 list,uint16 num)//��ʾһuint16��������line��list��
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
 *	@brief		��ʾһint16��������line��list��
 *	@param		line				Ҫ��ʾ���ڼ���(��1��ʼ�� 2����)
							list				Ҫ��ʾ���ڼ���(��1��ʼ��16����)
							num					Ҫ��ʾ������  (��ʾ�����ַ�Χ-32768~32767)
 *	@warning	���г������ֽ�����ʾ
 *	@sampleusage:	LCD1602_display_int16_number(1,1,-32767); //�ڵ�һ�ŵ�һ�����ӿ�ʼ��ʾ��-32767��
 */

void LCD1602_display_int16_number(uint8 line,uint8 list,int num)//��ʾһint16��������line��list��
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
 *	@brief		��ʾһuint32��������line��list��
 *	@param		line				Ҫ��ʾ���ڼ���(��1��ʼ�� 2����)
							list				Ҫ��ʾ���ڼ���(��1��ʼ��16����)
							num					Ҫ��ʾ������  (��ʾ�����ַ�Χ0~4294967295)
 *	@warning	���г������ֽ�����ʾ
 *	@sampleusage:	LCD1602_display_uint32_number(1,1,4294967295); //�ڵ�һ�ŵ�һ�����ӿ�ʼ��ʾ��4294967295��
 */

void LCD1602_display_uint32_number(uint8 line,uint8 list,uint32 num)//��ʾһuint32��������line��list��
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
