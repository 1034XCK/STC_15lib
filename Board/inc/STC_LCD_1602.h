#ifndef __STC_LCD_1602_H__
#define __STC_LCD_1602_H__

/**********   LCD�ܽŶ���   **********/
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

extern void init_LCD1602(void);								//LCD1602��ʼ������
extern void commoninit_init_LCD1602(void);		//��ͨ��ʼ������
extern void display_setup_LCD1602(uint8 com);	//LCD1602��ʾ���ú���

extern void LCD1602_display_achar(uint8 line,uint8 list,uint8 character);		//��ʾһ���ַ���line��list��
extern void LCD1602_display_array(uint8 line,uint8 list,uint8 *p);			 		//��ʾһ�ַ�����line��list��
extern void LCD1602_display_uint8_number(uint8 line,uint8 list,uint8 num);	//��ʾһuint8��������line��list��
extern void LCD1602_display_int8_number(uint8 line,uint8 list,int8 num);		//��ʾһint8��������line��list��
extern void LCD1602_display_uint16_number(uint8 line,uint8 list,uint16 num);//��ʾһuint16��������line��list��
extern void LCD1602_display_int16_number(uint8 line,uint8 list,int16 num);	//��ʾһint16��������line��list��
extern void LCD1602_display_uint32_number(uint8 line,uint8 list,uint32 num);//��ʾһuint32��������line��list��

void write_LCD1602_com(uint8 com);  					//LCD1602дָ���
void write_LCD1602_date(uint8 date);					//LCD1602д���ݺ���
void wait_LCD1602_busy_delay(void);						//�ȴ�LCD1602æ�겢�����ֵķ�Ӧʱ��

#endif //__STC_LCD_1602_H__