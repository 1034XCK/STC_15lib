#ifndef __STC_SYSTICK_H__
#define __STC_SYSTICK_H__

extern void systick_delay_us  (uint8 time_us);//��ʱ��΢�뼶��ʱ����(0~255)
extern void systick_delay_lus(uint16 time_us);//��ʱ��΢�뼶��ʱ����(4~65535)
extern void systick_delay_ms (uint16 time_ms);//���뼶��ʱ����(0~65535)

#endif