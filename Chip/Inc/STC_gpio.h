#ifndef __STC_GPIO_H__
#define __STC_GPIO_H__

#include "STC_port.h"

/************************************************初始化GPIO*********************************************************/
extern void gpio_init(pxn_e,  port_mode,  uint8 level_state);			//初始化GPIO引脚(哪个引脚，什么模式，初始电平)
extern void gpio_group_init(px_e,  port_mode,  uint8 level_state);//初始化一组GPIO端口(哪个端口，什么模式，初始数据)
extern void gpio_mode(pxn_e,  port_mode);													//设置GPIO引脚工作模式(哪个引脚，什么模式)
extern void gpio_group_mode(px_e,  port_mode);										//设置一组GPIO端口工作模式(哪个端口，什么模式)


/*********************************************GPIO数据设置与读取****************************************************/
extern void gpio_set(pxn_e,  bool level_state);									  //设置引脚状态
extern void gpio_turn(pxn_e);																			//反转引脚状态
extern bool gpio_get(pxn_e);																			//读取引脚状态

#endif      //__STC_GPIO_H__