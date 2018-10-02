#ifndef __STC_IAP_H__
#define __STC_IAP_H__

//���ݾ���Ƶ������ƥ��ISP�ȴ�ʱ��
#define ISP_WAIT_1MHZ	7
#define ISP_WAIT_2MHZ	6
#define ISP_WAIT_3MHZ	5
#define ISP_WAIT_6MHZ	4
#define ISP_WAIT_12MHZ	3
#define ISP_WAIT_20MHZ	2
#define ISP_WAIT_24MHZ	1
#define ISP_WAIT_30MHZ	0

#if (EXTAL_IN_Hz >= 24000000L)
	#define		ISP_WAIT_FREQUENCY	ISP_WAIT_30MHZ
#elif (EXTAL_IN_Hz >= 20000000L)
	#define		ISP_WAIT_FREQUENCY	ISP_WAIT_24MHZ
#elif (EXTAL_IN_Hz >= 12000000L)
	#define		ISP_WAIT_FREQUENCY	ISP_WAIT_20MHZ
#elif (EXTAL_IN_Hz >= 6000000L)
	#define		ISP_WAIT_FREQUENCY	ISP_WAIT_12MHZ
#elif (EXTAL_IN_Hz >= 3000000L)
	#define		ISP_WAIT_FREQUENCY	ISP_WAIT_6MHZ
#elif (EXTAL_IN_Hz >= 2000000L)
	#define		ISP_WAIT_FREQUENCY	ISP_WAIT_3MHZ
#elif (EXTAL_IN_Hz >= 1000000L)
	#define		ISP_WAIT_FREQUENCY	ISP_WAIT_2MHZ
#else
	#define		ISP_WAIT_FREQUENCY	ISP_WAIT_1MHZ
#endif


extern uint8 IAP_read_byte(uint16 addr);//��EEPROM��ĳһ��ַ�ڵ�1�ֽ�����
extern void IAP_write_byte(uint16 addr , uint8 write_data);//дEEPROM��ĳһ��ַ�ڵ�����
extern void IAP_erase_sector(uint16 addr);//����������

#endif //"STC_IAP.h"