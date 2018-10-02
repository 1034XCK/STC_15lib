#include "common.h"
#include "STC_ADc.h"
#include "STC_interrupt.h"

uint16 data ADC_interrupt_result[8]={0};

/**
 *  @brief		ADC��ʼ������ĳ��IO������Ϊģ�⹦��ʹ�ã�
 *	@param		ADCn ͨ����
 *	@param		interrupt_able ADC�ɼ���ʽ
 *	@warning	
 *	@sampleusage:	adc_init(ADC0,WAIT_ONCE);	//��P1.0��Ϊģ�⹦��ADC0ʹ��,���õȴ��ķ�ʽ�ɼ�
 */
void adc_init(ADCn_e ADCn ,  ADC_RESULT_WAY_e ADC_RESULT_WAY)
{
	BIT_CLR(ADC_CONTR,3);//ֹͣADת��
	if(ADCn == ADC_ALL)	P1ASF = 0xff;//����P1�ڵ�ģ�⹦��
	else BIT_SET(P1ASF,ADCn);//����P1�ڵ�ģ�⹦��
	ADC_RES=0;ADC_RESL=0;//��AD�ɼ�����Ĵ�������
	BIT_CLR(ADC_CONTR,4);//��AD�ɼ�������־λ����
	BIT_SET(CLK_DIV,5);//ADC_RES[1:0]��Ÿ���λ��ADC_RESL[7:0]��ŵ�8λ
	if(ADC_RESULT_WAY == ADC_INTERRUPT)
	{
		set_vector_handler(ADC_VECTORn , ADC_IRQHandler);
		Whether_IRQ(ADC_VECTORn , IRQ_enable);
	}
	else
	{
		Whether_IRQ(ADC_VECTORn , IRQ_disable);
	}
	BIT_SET(ADC_CONTR,7);//����ADת���ܿ���
}

/*!
 *	@brief		�ȴ���ȡADC������ֵ������10λ��
 *	@param		ADCn					��Ҫ�õ���һ·��ADֵ
 *	@param		SPEED_nSCLK		�Զ��Ĳɼ��ٶȽ��вɼ����ٶ�Խ�쾫��Խ�ͣ�
 *	@warning	һ��ֻ�ܲɼ�һ·��STC��Ƭ�����ֻ��һ��A/Dת����
 *	@sampleusage:	adc_wait_once(ADC0 , SPEED_90SCLK); //��90��ϵͳʱ�ӵ��ٶȲɼ�ADC0��������ֵ
 */
uint16 adc_wait_once(ADCn_e ADCn , SPEED_nSCLK_e SPEED_nSCLK)
{
	if(ADCn<ADC_ALL)REPLACE(ADC_CONTR,2,0,ADCn);//�����ɼ���ͨ����P1[7:0]
	REPLACE(ADC_CONTR,6,5,SPEED_nSCLK);//����ת���ٶ�
	BIT_SET(ADC_CONTR,3);//��ʼADת��
	while( ! BIT_GET(ADC_CONTR,4));//�ȴ�ת������
	BIT_CLR(ADC_CONTR,4);//���ת����ɱ�־λ
	return (ADC_RES<<8) | ADC_RESL;//����10λ����
}

/*!
 *	@brief		���ADcת�����󣬽��ͨ���жϷ�ʽ��ȡ
 *	@param		ADCn					��Ҫ�õ���һ·��ADֵ
 *	@param		SPEED_nSCLK		�Զ��Ĳɼ��ٶȽ��вɼ����ٶ�Խ�쾫��Խ�ͣ�
 *	@warning	
 *	@sampleusage:	adc_transition_request(ADC0 , SPEED_540SCLK);//����һ��ADת����������540��ϵͳʱ�Ӻ����ж��ڲ鿴
 */

void adc_transition_request(ADCn_e ADCn , SPEED_nSCLK_e SPEED_nSCLK)
{
	if(ADCn<ADC_ALL)REPLACE(ADC_CONTR,2,0,ADCn);//�����ɼ���ͨ����P1[7:0]
	REPLACE(ADC_CONTR,6,5,SPEED_nSCLK);//����ת���ٶ�
	BIT_SET(ADC_CONTR,3);//��ʼADת��
}

/*!
 *	@brief		�ȴ���ȡ�ڲ���׼��ѹ��ADc��ֵ
 *	@param		SPEED_nSCLK	ADcת���ٶ�
 *	@warning	ת���ٶȽ���Ϊ540��ϵͳʱ�ӣ�������Ϊ��ȷ
							�˻�ȡ��ʽΪ��ѯ�ȴ���ʽ
							ʹ�ô˺�������Ӱ�������ⲿADcת��
 *	@sampleusage:	get_BandGap_adc(SPEED_540SCLK);
 */

uint16 get_BandGap_adc(SPEED_nSCLK_e SPEED_nSCLK)
{
	uint8 after_P1ASF = P1ASF;
	
	BIT_CLR(ADC_CONTR,3);//ֹͣADת��
	P1ASF = 0x00;
	ADC_RES=0;ADC_RESL=0;//��AD�ɼ�����Ĵ�������
	BIT_CLR(ADC_CONTR,4);//��AD�ɼ�������־λ����
	BIT_SET(CLK_DIV,5);//ADC_RES[1:0]��Ÿ���λ��ADC_RESL[7:0]��ŵ�8λ
	BIT_SET(ADC_CONTR,7);//����ADת���ܿ���
	REPLACE(ADC_CONTR,6,5,SPEED_nSCLK);//����ת���ٶ�
	BIT_SET(ADC_CONTR,3);//��ʼADת��
	while( ! BIT_GET(ADC_CONTR,4));//�ȴ�ת������
	BIT_CLR(ADC_CONTR,4);//���ת����ɱ�־λ
	P1ASF = after_P1ASF;
	return (ADC_RES<<8) | ADC_RESL;//����10λ����
}

/*!
 *	@brief		�ȴ���ȡһ����ȷ�ص�ѹֵ����λmV
 *	@param		ADCn					��Ҫ�õ���һ·��ADֵ
 *	@param		SPEED_nSCLK		�Զ��Ĳɼ��ٶȽ��вɼ����ٶ�Խ�쾫��Խ�ͣ�
 *	@warning	������õ��ǵȴ��ɼ���ʽ
 *	@sampleusage:	get_voltage_delay(ADC0 , SPEED_90SCLK);//��90��ϵͳʱ�ӵ��ٶȲɼ�ADC0������540��ϵͳʱ�ӵ��ٶȲɼ��ڲ���׼ֵ�����������������mVΪ��λ�ĵ�ѹֵ
 */

uint16 get_voltage_delay(ADCn_e ADCn , SPEED_nSCLK_e SPEED_nSCLK)
{
	return 1246L * adc_wait_once(ADCn , SPEED_nSCLK) / get_BandGap_adc(SPEED_540SCLK);//��540��ϵͳʱ�ӵ��ٶȲɼ��ڲ���׼ֵ�����������㣬���ؾ�ȷ�ĵ�ѹֵ����λmV
}

/*!
 *	@brief		ADC�ɼ�����ж�
 *	@param		
 *	@warning	
 *	@sampleusage:	
 */

void ADC_IRQHandler(void)
{
	BIT_CLR(ADC_CONTR,4);//���ת����ɱ�־λ
	ADC_interrupt_result[ACQUIRE(ADC_CONTR,2,0)] = (ADC_RES<<8) | ADC_RESL;//����10λ����
}