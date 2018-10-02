/*
 * ����ͷ�ļ�
 */
 #include "common.h"
 #include "STC_SysTick.h"
 
 /*!
 *	@brief		��ʱ��΢�뼶��ʱ����
 *	@param		time_us				��ʱʱ�䣬��Χ��0~255us����λΪ΢��
 *	@warning	33.0000MHz->24��nop
							28.0000MHz->18��nop
							27.0000MHz->17��nop
							24.0000MHz->14��nop
							22.1184MHz->12��nop
							20.0000MHz->10��nop
							18.4320MHz-> 8��nop
							12.0000MHz-> 2��nop
							11.0592MHz-> 1��nop
							<10.000MHz-> 0�������ǳ���׼��
 *	@warning	ʱ��������У׼����ϵͳʱ�ӷ�����������»���ֽϴ����
 *	@sampleusage:	systick_delay_us(255); //��ʱ255us
 */

void systick_delay_us(uint8 time_us)//��ʱ��΢�뼶��ʱ����
{
	if(time_us==0)
		return;
	while(--time_us)
	{
#if (EXTAL_IN_Hz >= 11000000)
		_nop_();//1��
#endif
#if (EXTAL_IN_Hz >= 12000000)
		_nop_();//2��
#endif
#if (EXTAL_IN_Hz >= 18000000)
		_nop_();_nop_();_nop_();_nop_();
		_nop_();_nop_();//8��
#endif
#if (EXTAL_IN_Hz >= 20000000)
		_nop_();_nop_();//10��
#endif
#if (EXTAL_IN_Hz >= 22000000)
		_nop_();_nop_();//12��
#endif
#if (EXTAL_IN_Hz >= 24000000)
		_nop_();_nop_();//14��
#endif
#if (EXTAL_IN_Hz >= 27000000)
		_nop_();_nop_();_nop_();//17��
#endif
#if (EXTAL_IN_Hz >= 28000000)
		_nop_();//18��
#endif
#if (EXTAL_IN_Hz >= 30000000)
		_nop_();_nop_();//20��
#endif
#if (EXTAL_IN_Hz >= 31000000)
		_nop_();//21��
#endif
#if (EXTAL_IN_Hz >= 32000000)
		_nop_();//22��
#endif
#if (EXTAL_IN_Hz >= 33000000)
		_nop_();//23��
#endif
#if (EXTAL_IN_Hz >= 34000000)
		_nop_();//24��
#endif
#if (EXTAL_IN_Hz >= 35000000)
		_nop_();//25��
#endif
	}
}

 /*!
 *	@brief		��ʱ��΢�뼶��ʱ����
 *	@param		time_us				��ʱʱ�䣬��Χ��4~65535us����λΪ΢��
 *	@warning	33.0000MHz->17��nop
							28.0000MHz->12��nop
							27.0000MHz->11��nop
							24.0000MHz-> 8��nop
							22.1184MHz-> 6��nop
							20.0000MHz-> 4��nop
							18.4320MHz-> 2��nop
							<16.000MHz-> 0�������ǳ���׼��
 *	@warning	ʱ��������У׼����ϵͳʱ�ӷ�����������»���ֽϴ����
 *	@sampleusage:	systick_delay_us(32767); //��ʱ65535us
 */

void systick_delay_lus(uint16 time_us)//��ʱ��΢�뼶��ʱ����
{
	if(time_us==0)
		return;
	while(--time_us)
	{
#if (EXTAL_IN_Hz >= 17000000)
		_nop_();//1��
#endif
#if (EXTAL_IN_Hz >= 18000000)
		_nop_();//2��
#endif
#if (EXTAL_IN_Hz >= 20000000)
		_nop_();_nop_();//4��
#endif
#if (EXTAL_IN_Hz >= 22000000)
		_nop_();_nop_();//6��
#endif
#if (EXTAL_IN_Hz >= 24000000)
		_nop_();_nop_();//8��
#endif
#if (EXTAL_IN_Hz >= 27000000)
		_nop_();_nop_();_nop_();//11��
#endif
#if (EXTAL_IN_Hz >= 28000000)
		_nop_();//12��
#endif
#if (EXTAL_IN_Hz >= 30000000)
		_nop_();_nop_();//14��
#endif
#if (EXTAL_IN_Hz >= 33000000)
		_nop_();_nop_();_nop_();//17��
#endif
#if (EXTAL_IN_Hz >= 34000000)
		_nop_();//18��
#endif
#if (EXTAL_IN_Hz >= 35000000)
		_nop_();//19��
#endif
	}
}


 /*!
 *	@brief		��ʱ����뼶��ʱ����
 *	@param		time_ms				��ʱʱ�䣬��Χ��0~65535ms����λΪ����
 *	@warning	��ע�������ʱ��΢�뼶��ʱ�ľ���
 *	@sampleusage:	systick_delay_ms(65535); //��ʱ65535ms
 */

void systick_delay_ms(uint16 time_ms)//���뼶��ʱ����
{
	if(time_ms==0)
		return;
	while(time_ms--)
	{
		systick_delay_lus(1000);
	}
}
