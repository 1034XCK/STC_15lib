#ifndef __STC_WS2812_H__
#define __STC_WS2812_H__

#include "common.h"

#define WS2812_D P32 //WS2812��������
#define WS2812_work_speed 0 //WS2812�����ٶ�,0:��ͨģʽ(ʱ���ϸ����ֲ�ִ�У�����Ƶ��>16MHz�������У�ˢдһ����������ʱ��ԼΪ34.5us)
                            //               1:����ģʽ(���ռ����������Կ��е�����ٶȣ�Ҫ����Ƶ��>=35MHz��ˢдһ����������ʱ��ԼΪ30us)����ܵ������в��ȶ�

#if (WS2812_work_speed) //1Ϊ����ģʽ
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
#else //0Ϊ��ͨ�ٶȣ��ϸ��ձ�׼ʱ��ִ��
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