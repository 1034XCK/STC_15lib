#ifndef __STC_CONF_H__
#define __STC_CONF_H__

/*
 * ����ƽ̨[���ڹ���ѡ���ﶨ��]
 */

/*
 * ���徧��ʱ��,��λΪMHz
 */
#define EXTAL_IN_Hz		(35000000)	//�ڲ�IRCʱ�ӡ��ⲿ����ʱ�ӡ��ⲿ����ʱ��


/*
 * ����LCD�ͺ�
 */

/*
 * ѡ���Ƿ����������Ϣ,�������ע������ĺ궨��
 */


/*
 * ���� PLL ��Ƶ Ƶ�� 
 */


/*
 * ���� printf���� �� ��������˿� �� ������Ϣ
 */
 
#define STC_PORT		UART0
 
/*
 * ������ʱ����
 */
 
 #if 1
 #include "STC_SysTick.h"
 #define DELAY_US(us)		systick_delay_lus(us)
 #define DELAY_MS(ms)		systick_delay_ms(ms)
 #endif

/*
 * ���ö��Ժ���ʵ�ֺ���
 */

/*
 * ���õ����������
 */

/*
 * ����ǰ���,��ֹ �������ؿ�
 */

#endif /* __STC_CONF_H__  */