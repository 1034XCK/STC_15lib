#ifndef __STC_GPIO_H__
#define __STC_GPIO_H__

#include "STC_port.h"

/************************************************��ʼ��GPIO*********************************************************/
extern void gpio_init(pxn_e,  port_mode,  uint8 level_state);			//��ʼ��GPIO����(�ĸ����ţ�ʲôģʽ����ʼ��ƽ)
extern void gpio_group_init(px_e,  port_mode,  uint8 level_state);//��ʼ��һ��GPIO�˿�(�ĸ��˿ڣ�ʲôģʽ����ʼ����)
extern void gpio_mode(pxn_e,  port_mode);													//����GPIO���Ź���ģʽ(�ĸ����ţ�ʲôģʽ)
extern void gpio_group_mode(px_e,  port_mode);										//����һ��GPIO�˿ڹ���ģʽ(�ĸ��˿ڣ�ʲôģʽ)


/*********************************************GPIO�����������ȡ****************************************************/
extern void gpio_set(pxn_e,  bool level_state);									  //��������״̬
extern void gpio_turn(pxn_e);																			//��ת����״̬
extern bool gpio_get(pxn_e);																			//��ȡ����״̬

#endif      //__STC_GPIO_H__