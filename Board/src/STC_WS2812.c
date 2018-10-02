#include "STC_WS2812.h"

/*!
 *	@brief		WS2812初始化 或 帧结束符
 *	@param		
 *	@warning	
 *	@sampleusage:	init_ws2812_or_end_frame();
 */

bool init_ws2812_or_end_frame(void)
{
	WS2812_D = 0;
	DELAY_US(50);
	if(WS2812_D) return false;
	else return true;
}

/*!
 *	@brief		刷写WS2812让其显示
 *	@param		num 要传输数据的字节数(一个灯珠花掉3个字节，分别为绿色、红色、蓝色的亮度等级)，可取数组的sizeof()计算长度
              *p  要传输数据所存放的数组的首地址，必须以取地址符号&进入
 *	@warning	该函数只负责数据传输，传输完一帧数据流后请按照实际情况给出一大于24us的帧结束时间
 *	@sampleusage:	WS2812_display(sizeof(A) , &A[0][0]);
 */

void WS2812_display(uint8 data num , uint8 *p)
{
	uint8 data d=0;
	while(num--)
	{
		d = *p++;
		if(d&0x80) SEND_H_DATA
		else SEND_L_DATA
		if(d&0x80) SEND_H_DATA
		else SEND_L_DATA
		if(d&0x80) SEND_H_DATA
		else SEND_L_DATA
		if(d&0x80) SEND_H_DATA
		else SEND_L_DATA
		if(d&0x80) SEND_H_DATA
		else SEND_L_DATA
		if(d&0x80) SEND_H_DATA
		else SEND_L_DATA
		if(d&0x80) SEND_H_DATA
		else SEND_L_DATA
		if(d&0x80) SEND_H_DATA
		else SEND_L_DATA
	}
}