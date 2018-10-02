#ifndef __STC_DS1302_H__
#define __STC_DS1302_H__

#define DS1302_CLK P34
#define DS1302_DAT P33
#define DS1302_CE P32

extern void init_DS1302(void);

extern void write_DS1302(uint8 adr , uint8 dat);
extern uint8 read_DS1302(uint8 adr);

void write_Byte_DS1302(uint8 dat);
uint8 read_Byte_DS1302(void);

#endif