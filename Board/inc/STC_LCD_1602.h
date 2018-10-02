#ifndef __STC_LCD_1602_H__
#define __STC_LCD_1602_H__

/**********   LCD管脚定义   **********/
#define LCD1602_RS  P44
#define LCD1602_RW  P42
#define LCD1602_EN  P41
#define LCD1602_LED P10

#define LCD1602_D0  P00
#define LCD1602_D1  P01
#define LCD1602_D2  P02
#define LCD1602_D3  P03
#define LCD1602_D4  P04
#define LCD1602_D5  P05
#define LCD1602_D6  P06
#define LCD1602_D7  P07

#define LCD_delay()	DELAY_US(100)

extern void init_LCD1602(void);								//LCD1602简单始化函数
extern void commoninit_init_LCD1602(void);		//普通初始化函数
extern void display_setup_LCD1602(uint8 com);	//LCD1602显示设置函数

extern void LCD1602_display_achar(uint8 line,uint8 list,uint8 character);		//显示一个字符于line行list列
extern void LCD1602_display_array(uint8 line,uint8 list,uint8 *p);			 		//显示一字符串于line行list列
extern void LCD1602_display_uint8_number(uint8 line,uint8 list,uint8 num);	//显示一uint8型数字于line行list列
extern void LCD1602_display_int8_number(uint8 line,uint8 list,int8 num);		//显示一int8型数字于line行list列
extern void LCD1602_display_uint16_number(uint8 line,uint8 list,uint16 num);//显示一uint16型数字于line行list列
extern void LCD1602_display_int16_number(uint8 line,uint8 list,int16 num);	//显示一int16型数字于line行list列
extern void LCD1602_display_uint32_number(uint8 line,uint8 list,uint32 num);//显示一uint32型数字于line行list列

void write_LCD1602_com(uint8 com);  					//LCD1602写指令函数
void write_LCD1602_date(uint8 date);					//LCD1602写数据函数
void wait_LCD1602_busy_delay(void);						//等待LCD1602忙完并给予充分的反应时间

#endif //__STC_LCD_1602_H__