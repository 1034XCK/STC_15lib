#include "STC_WS2812.h"

/*!
 *	@brief		WS2812��ʼ�� �� ֡������
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
 *	@brief		ˢдWS2812������ʾ
 *	@param		num Ҫ�������ݵ��ֽ���(һ�����黨��3���ֽڣ��ֱ�Ϊ��ɫ����ɫ����ɫ�����ȵȼ�)����ȡ�����sizeof()���㳤��
              *p  Ҫ������������ŵ�������׵�ַ��������ȡ��ַ����&����
 *	@warning	�ú���ֻ�������ݴ��䣬������һ֡���������밴��ʵ���������һ����24us��֡����ʱ��
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