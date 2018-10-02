#ifndef __STC_SYSTICK_H__
#define __STC_SYSTICK_H__

extern void systick_delay_us  (uint8 time_us);//短时间微秒级延时函数(0~255)
extern void systick_delay_lus(uint16 time_us);//长时间微秒级延时函数(4~65535)
extern void systick_delay_ms (uint16 time_ms);//毫秒级延时函数(0~65535)

#endif