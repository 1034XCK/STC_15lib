#ifndef __STC_DS18B20_H__
#define __STC_DS18B20_H__

extern bit init_DS18B20(pxn_e DS18B20_DQ);//初始化DS18B20
extern int16 DS18B20_read_temperature(pxn_e DS18B20_DQ);          

void DS18B20_write_byte(pxn_e DS18B20_DQ , uint8 dat);//写字节
uint8 DS18B20_read_byte(pxn_e DS18B20_DQ);//读字节

#endif //__STC_DS18B20_H__