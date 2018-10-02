#include "common.h"
#include "STC_clock.h"

/*!
 *	@brief		��ʱ�ӣ���ʱ�ӣ���Ƶ��ϵͳʱ�ӣ���������ʱ�ӣ�
 *	@param		CLOCK_DIV_e				��Ƶ���ò���
 *	@warning	��ʼֵΪ��ϵͳʱ�� = ��ʱ�ӣ�����Ƶ��
 *	@sampleusage:	clockdiv_count(DIV_2);	//ϵͳ����ʱ��Ϊ��ʱ�Ӷ���Ƶ����
 */
void clockdiv_count(CLOCK_DIV_e div)
{
	if(div < DIV_MAX) REPLACE(CLK_DIV,2,0,div);//����ϵͳʱ�ӷ�Ƶϵ��
}

/*!
 *	@brief		��ʱ�Ӷ����Ƶ�������
 *	@param		mcko	�Ƿ��������ͷ�Ƶϵ��
 *	@warning	ʱ�����������PORT_cfg.h������
            	STC15ϵ��5V��Ƭ�������������13.5MHz��Ƶ�ʣ�3.3V�Ĳ��ܳ���8MHz
             	STC15ϵ��8pin��Ƭ����MCLKO/P3.4�ڶ������ʱ��
             	STC15ϵ��16pin�����ϵ�Ƭ������MCLKO/P5.4�����ʱ��
            	STC15W4kϵ�п���MCLKO/P5.4��MCLKO_2/XTAL2/P1.6�����ʱ��
              ʱ���������IO�ڹ���ģʽ����Ϊ�������룬�ϵ��ʼ��Ϊ׼˫���
 *	@sampleusage:	mclock_div_output(MCKO_2)	//��ʱ�Ӷ������2��Ƶʱ��
 */
void mclock_div_output(MCKO_e mcko)
{
	if(mcko < MCKO_MAX) REPLACE(CLK_DIV,7,6,mcko);//�������ʱ�ӷ�Ƶϵ��
	if(MCLK_OUTPUT_PIN == p54 || MCLK_OUTPUT_PIN == p34) BIT_CLR(CLK_DIV,3);//����ʱ�Ӷ�������˿�λ��
	else if(MCLK_OUTPUT_PIN == p16)BIT_SET(CLK_DIV,3);//����ʱ�Ӷ�������˿�λ��
}