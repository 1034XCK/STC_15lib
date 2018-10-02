#ifndef __STC_WS2812_H__
#define __STC_WS2812_H__

#include "common.h"

#define WS2812_D P32 //WS2812数据引脚
#define WS2812_work_speed 0 //WS2812工作速度,0:普通模式(时序严格按照手册执行，晶振频率>16MHz均可运行，刷写一个灯珠所用时间约为34.5us)
                            //               1:高速模式(按照极限条件测试可行的最快速度，要求晶振频率>=35MHz，刷写一个灯珠所用时间约为30us)这可能导致运行不稳定

#if (WS2812_work_speed) //1为高速模式
  #if (EXTAL_IN_Hz >= 35000000)
	  #define SEND_H_DATA     \
				    {               \
					    WS2812_D = 1; \
					    d<<=1;        \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
					    WS2812_D = 0; \
				    }
    #define SEND_L_DATA     \
				    {               \
					    WS2812_D = 1; \
					    _nop_();      \
					    WS2812_D = 0; \
					    d<<=1;        \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
							_nop_();      \
				    }
	#else
	  #error "Crystal frequency is too low because 'WS2812_work_speed' has been set to high speed mode, so adjust 'EXTAL_IN_Hz' to a value greater than 35MHz."
	#endif
#else //0为普通速度，严格按照标准时许执行
  #if (EXTAL_IN_Hz >= 34000000)
    #define SEND_H_DATA     \
				    {               \
					    WS2812_D = 1; \
					    d<<=1;        \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
					    WS2812_D = 0; \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
				      _nop_();      \
					    _nop_();      \
				    }
    #define SEND_L_DATA     \
				    {               \
					    WS2812_D = 1; \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
					    WS2812_D = 0; \
					    d<<=1;        \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
				    }
  #elif (EXTAL_IN_Hz >= 32000000)
		#define SEND_H_DATA     \
				    {               \
					    WS2812_D = 1; \
					    d<<=1;        \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
					    WS2812_D = 0; \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
				      _nop_();      \
				    }
		#define SEND_L_DATA     \
				    {               \
					    WS2812_D = 1; \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
					    WS2812_D = 0; \
					    d<<=1;        \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
				    }
  #elif (EXTAL_IN_Hz >= 30000000)
		#define SEND_H_DATA     \
				    {               \
					    WS2812_D = 1; \
					    d<<=1;        \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
					    WS2812_D = 0; \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
				    }
		#define SEND_L_DATA     \
				    {               \
					    WS2812_D = 1; \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
					    WS2812_D = 0; \
					    d<<=1;        \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
				    }
  #elif (EXTAL_IN_Hz >= 27000000)
	  #define SEND_H_DATA     \
				    {               \
					    WS2812_D = 1; \
					    d<<=1;        \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
					    WS2812_D = 0; \
					    _nop_();      \
						  _nop_();      \
				    }
	  #define SEND_L_DATA     \
				    {               \
					    WS2812_D = 1; \
					    _nop_();      \
					    _nop_();      \
					    WS2812_D = 0; \
					    d<<=1;        \
					    _nop_();      \
				    }
  #elif (EXTAL_IN_Hz >= 24000000)
		#define SEND_H_DATA     \
				    {               \
					    WS2812_D = 1; \
					    d<<=1;        \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
						  _nop_();      \
					    WS2812_D = 0; \
				    }
	  #define SEND_L_DATA     \
				    {               \
					    WS2812_D = 1; \
					    _nop_();      \
					    WS2812_D = 0; \
					    d<<=1;        \
				    }
  #elif (EXTAL_IN_Hz >= 16000000)
		#define SEND_H_DATA     \
				    {               \
					    WS2812_D = 1; \
					    d<<=1;        \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
					    _nop_();      \
					    WS2812_D = 0; \
				    }
		#define SEND_L_DATA     \
				    {               \
					    WS2812_D = 1; \
						  _nop_();      \
					    WS2812_D = 0; \
					    d<<=1;        \
				    }
  #else
	  #error "The crystal frequency is too low to complete the WS2812 function. Please set a higher (EXTAL_IN_Hz) value."
  #endif
#endif

extern bool init_ws2812_or_end_frame(void);
extern void WS2812_display(uint8 num , uint8 *array_addr);

#endif //__STC_WS2812_H__