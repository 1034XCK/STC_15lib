#include "common.h"
#include "STC_clock.h"

/*!
 *	@brief		主时钟（振荡时钟）分频至系统时钟（程序运行时钟）
 *	@param		CLOCK_DIV_e				分频设置参数
 *	@warning	初始值为：系统时钟 = 主时钟（不分频）
 *	@sampleusage:	clockdiv_count(DIV_2);	//系统运行时钟为主时钟二分频而来
 */
void clockdiv_count(CLOCK_DIV_e div)
{
	if(div < DIV_MAX) REPLACE(CLK_DIV,2,0,div);//设置系统时钟分频系数
}

/*!
 *	@brief		主时钟对外分频输出控制
 *	@param		mcko	是否对外输出和分频系数
 *	@warning	时钟输出引脚在PORT_cfg.h中设置
            	STC15系列5V单片机不能输出超过13.5MHz的频率，3.3V的不能超过8MHz
             	STC15系列8pin单片机在MCLKO/P3.4口对外输出时钟
             	STC15系列16pin及以上单片机均在MCLKO/P5.4口输出时钟
            	STC15W4k系列可在MCLKO/P5.4或MCLKO_2/XTAL2/P1.6口输出时钟
              时钟输出所在IO口工作模式不能为浮空输入，上电初始化为准双向口
 *	@sampleusage:	mclock_div_output(MCKO_2)	//主时钟对外输出2分频时钟
 */
void mclock_div_output(MCKO_e mcko)
{
	if(mcko < MCKO_MAX) REPLACE(CLK_DIV,7,6,mcko);//设置输出时钟分频系数
	if(MCLK_OUTPUT_PIN == p54 || MCLK_OUTPUT_PIN == p34) BIT_CLR(CLK_DIV,3);//设置时钟对外输出端口位置
	else if(MCLK_OUTPUT_PIN == p16)BIT_SET(CLK_DIV,3);//设置时钟对外输出端口位置
}