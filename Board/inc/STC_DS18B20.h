#ifndef __STC_DS18B20_H__
#define __STC_DS18B20_H__

extern bit init_DS18B20(pxn_e DS18B20_DQ);//��ʼ��DS18B20
extern int16 DS18B20_read_temperature(pxn_e DS18B20_DQ);          

void DS18B20_write_byte(pxn_e DS18B20_DQ , uint8 dat);//д�ֽ�
uint8 DS18B20_read_byte(pxn_e DS18B20_DQ);//���ֽ�

#endif //__STC_DS18B20_H__