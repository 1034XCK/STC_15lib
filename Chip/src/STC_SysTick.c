/*
 * 包含头文件
 */
 #include "common.h"
 #include "STC_SysTick.h"
 
 /*!
 *	@brief		短时间微秒级延时函数
 *	@param		time_us				延时时间，范围是0~255us，单位为微秒
 *	@warning	33.0000MHz->24个nop
							28.0000MHz->18个nop
							27.0000MHz->17个nop
							24.0000MHz->14个nop
							22.1184MHz->12个nop
							20.0000MHz->10个nop
							18.4320MHz-> 8个nop
							12.0000MHz-> 2个nop
							11.0592MHz-> 1个nop
							<10.000MHz-> 0个，但非常不准！
 *	@warning	时间请自行校准，在系统时钟非整数的情况下会出现较大误差
 *	@sampleusage:	systick_delay_us(255); //延时255us
 */

void systick_delay_us(uint8 time_us)//短时间微秒级延时函数
{
	if(time_us==0)
		return;
	while(--time_us)
	{
#if (EXTAL_IN_Hz >= 11000000)
		_nop_();//1个
#endif
#if (EXTAL_IN_Hz >= 12000000)
		_nop_();//2个
#endif
#if (EXTAL_IN_Hz >= 18000000)
		_nop_();_nop_();_nop_();_nop_();
		_nop_();_nop_();//8个
#endif
#if (EXTAL_IN_Hz >= 20000000)
		_nop_();_nop_();//10个
#endif
#if (EXTAL_IN_Hz >= 22000000)
		_nop_();_nop_();//12个
#endif
#if (EXTAL_IN_Hz >= 24000000)
		_nop_();_nop_();//14个
#endif
#if (EXTAL_IN_Hz >= 27000000)
		_nop_();_nop_();_nop_();//17个
#endif
#if (EXTAL_IN_Hz >= 28000000)
		_nop_();//18个
#endif
#if (EXTAL_IN_Hz >= 30000000)
		_nop_();_nop_();//20个
#endif
#if (EXTAL_IN_Hz >= 31000000)
		_nop_();//21个
#endif
#if (EXTAL_IN_Hz >= 32000000)
		_nop_();//22个
#endif
#if (EXTAL_IN_Hz >= 33000000)
		_nop_();//23个
#endif
#if (EXTAL_IN_Hz >= 34000000)
		_nop_();//24个
#endif
#if (EXTAL_IN_Hz >= 35000000)
		_nop_();//25个
#endif
	}
}

 /*!
 *	@brief		长时间微秒级延时函数
 *	@param		time_us				延时时间，范围是4~65535us，单位为微秒
 *	@warning	33.0000MHz->17个nop
							28.0000MHz->12个nop
							27.0000MHz->11个nop
							24.0000MHz-> 8个nop
							22.1184MHz-> 6个nop
							20.0000MHz-> 4个nop
							18.4320MHz-> 2个nop
							<16.000MHz-> 0个，但非常不准！
 *	@warning	时间请自行校准，在系统时钟非整数的情况下会出现较大误差
 *	@sampleusage:	systick_delay_us(32767); //延时65535us
 */

void systick_delay_lus(uint16 time_us)//长时间微秒级延时函数
{
	if(time_us==0)
		return;
	while(--time_us)
	{
#if (EXTAL_IN_Hz >= 17000000)
		_nop_();//1个
#endif
#if (EXTAL_IN_Hz >= 18000000)
		_nop_();//2个
#endif
#if (EXTAL_IN_Hz >= 20000000)
		_nop_();_nop_();//4个
#endif
#if (EXTAL_IN_Hz >= 22000000)
		_nop_();_nop_();//6个
#endif
#if (EXTAL_IN_Hz >= 24000000)
		_nop_();_nop_();//8个
#endif
#if (EXTAL_IN_Hz >= 27000000)
		_nop_();_nop_();_nop_();//11个
#endif
#if (EXTAL_IN_Hz >= 28000000)
		_nop_();//12个
#endif
#if (EXTAL_IN_Hz >= 30000000)
		_nop_();_nop_();//14个
#endif
#if (EXTAL_IN_Hz >= 33000000)
		_nop_();_nop_();_nop_();//17个
#endif
#if (EXTAL_IN_Hz >= 34000000)
		_nop_();//18个
#endif
#if (EXTAL_IN_Hz >= 35000000)
		_nop_();//19个
#endif
	}
}


 /*!
 *	@brief		长时间毫秒级延时函数
 *	@param		time_ms				延时时间，范围是0~65535ms，单位为毫秒
 *	@warning	请注意调整长时间微秒级延时的精度
 *	@sampleusage:	systick_delay_ms(65535); //延时65535ms
 */

void systick_delay_ms(uint16 time_ms)//毫秒级延时函数
{
	if(time_ms==0)
		return;
	while(time_ms--)
	{
		systick_delay_lus(1000);
	}
}
