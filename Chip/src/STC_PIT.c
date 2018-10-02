#include "common.h"
#include "STC_PIT.h"

/*!
 *	@brief		关闭PIT计时
 *	@param		
 *	@warning	
 *	@sampleusage:	
 */
 
void pit_close(TIMERn_e timer)//关闭PIT计时
{
	switch(timer)
	{
		case T0 : TR0=0;break;
		case T1 : TR1=0;break;
		case T2 : BIT_CLR(AUXR,4); break;
		case T3 : BIT_CLR(T4T3M,3);break;
		case T4 : BIT_CLR(T4T3M,7);break;
	}
}

/*!
 *	@brief		初始化PIT并设置定时时间
 *	@param		timer		定时器模块号
							num			定时时间
 *	@warning	默认使用16位自动重装模式
 *	@sampleusage:	pit_init(T0,10000);//启用T0定时器,并且定时时间为10000个系统周期
 */

void pit_init(TIMERn_e timer , uint16 num)//初始化并启动定时器
{
	num = 0xffff - num;//计算好需要填入定时计数器寄存器的值
	if(timer == T0)//若使用T0定时器
		{
			TF0 = 0;//清除溢出中断标志
			BIT_SET(AUXR,7);//T0定时器工作在1T模式（系统时钟不分频作为定时器节奏）
			REPLACE(TMOD,3,0,0);//16位自动重装，不受外部引脚控制，定时器
			TL0 = num;//设置定时器走时长度
			TH0 = num>>8;////设置定时器走时长度
			TR0 = 1;//T0定时器开始计时
		}
		else if(timer == T1)
				 {
					 TF1 = 0;//清除溢出中断标志
					 BIT_SET(AUXR,6);//T1定时器工作在1T模式（系统时钟不分频作为定时器节奏）
					 REPLACE(TMOD,7,4,0);//16位自动重装，不受外部引脚控制，定时器
					 TL1 = num;//设置定时器走时长度
					 TH1 = num>>8;//设置定时器走时长度
					 TR1 = 1;//T1定时器开始计时
				 }
				 else if(timer == T2)
							{
								BIT_SET(AUXR,2);//T2定时器工作在1T模式（系统时钟不分频作为定时器节奏）
								T2L = num;//设置定时器走时长度
								T2H = num>>8;//设置定时器走时长度
								BIT_CLR(AUXR,3);//T2用作定时器
								BIT_SET(AUXR,4);//T2定时器开始计时
							}
							else if(timer == T3)
									 {
										 BIT_SET(T4T3M,1);//T3定时器工作在1T模式（系统时钟不分频作为定时器节奏）
										 T3L = num;//设置定时器走时长度
										 T3H = num>>8;//设置定时器走时长度
										 BIT_CLR(T4T3M,2);//T3用作定时器
										 BIT_SET(T4T3M,3);//T3定时器开始计时
									 }
									 else if(timer == T4)
												{
													BIT_SET(T4T3M,5);//T4定时器工作在1T模式（系统时钟不分频作为定时器节奏）
													T4L = num;//设置定时器走时长度
													T4H = num>>8;//设置定时器走时长度
													BIT_CLR(T4T3M,6);//T4用作定时器
													BIT_SET(T4T3M,7);//T4定时器开始计时
												}
}

/*!
 *	@brief		更改定时时间
 *	@param		timer		定时器模块号
							num			定时时间
 *	@warning	
 *	@sampleusage:	pit_change(T0,500);//将T0定时器的定时时间更改为500个系统周期
 */

void pit_change(TIMERn_e timer , uint16 num)
{
	num = 0xffff - num;//计算好需要填入定时计数器寄存器的值
	if(timer == T0)//若使用T0定时器
		{
			TL0 = num;//设置定时器走时长度
			TH0 = num>>8;////设置定时器走时长度
		}
		else if(timer == T1)
				 {
					 TL1 = num;//设置定时器走时长度
					 TH1 = num>>8;//设置定时器走时长度
				 }
				 else if(timer == T2)
							{
								T2L = num;//设置定时器走时长度
								T2H = num>>8;//设置定时器走时长度
							}
							else if(timer == T3)
									 {
										 T3L = num;//设置定时器走时长度
										 T3H = num>>8;//设置定时器走时长度
									 }
									 else if(timer == T4)
												{
													T4L = num;//设置定时器走时长度
													T4H = num>>8;//设置定时器走时长度
												}
}

/*!
 *	@brief		读取定时器当前计时数值
 *	@param		timer   	定时器模块号
 *	@warning  定时器计时走数是从0开始，每过一个计时周期其值增加1
 *	@sampleusage:	pit_get(T0); //获取T0定时器当前计数值
 */
uint16 pit_get(TIMERn_e timer)
{
	if(timer == T0) return (TH0<<8)|TL0;//若使用T0定时器
		else if(timer == T1) return (TH1<<8)|TL1;
				 else if(timer == T2) return (T2H<<8)|T2L;
							else if(timer == T3) return (T3H<<8)|T3L;
									 else if(timer == T4) return (T4H<<8)|T4L;
												else return 0;
}