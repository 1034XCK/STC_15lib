#ifndef __STC_CONF_H__
#define __STC_CONF_H__

/*
 * 定义平台[放在工程选项里定义]
 */

/*
 * 定义晶振时钟,单位为MHz
 */
#define EXTAL_IN_Hz		(35000000)	//内部IRC时钟、外部输入时钟、外部晶振时钟


/*
 * 定义LCD型号
 */

/*
 * 选择是否输出调试信息,不输出则注释下面的宏定义
 */


/*
 * 定义 PLL 超频 频率 
 */


/*
 * 定义 printf函数 的 串口输出端口 和 串口信息
 */
 
#define STC_PORT		UART0
 
/*
 * 配置延时函数
 */
 
 #if 1
 #include "STC_SysTick.h"
 #define DELAY_US(us)		systick_delay_lus(us)
 #define DELAY_MS(ms)		systick_delay_ms(ms)
 #endif

/*
 * 配置断言和其实现函数
 */

/*
 * 配置调试输出函数
 */

/*
 * 启动前检测,放止 复用下载口
 */

#endif /* __STC_CONF_H__  */