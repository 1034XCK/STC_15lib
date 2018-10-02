#ifndef __STC_ADC_H__
#define __SYC_ADC_H__

typedef enum
{
	ADC0,//P1.0
	ADC1,//P1.1
	ADC2,//P1.2
	ADC3,//P1.3
	ADC4,//P1.4
	ADC5,//P1.5
	ADC6,//P1.6
	ADC7,//P1.7
	ADC_ALL,//����P1�ھ�����AD�ɼ�
}ADCn_e;

typedef enum
{
	SPEED_540SCLK,
	SPEED_360SCLK,
	SPEED_180SCLK,
	SPEED_90SCLK,
}SPEED_nSCLK_e;

typedef enum
{
	WAIT_ONCE,
	ADC_INTERRUPT,
}ADC_RESULT_WAY_e;

extern uint16 data ADC_interrupt_result[8];

extern void adc_init(ADCn_e ADCn ,  ADC_RESULT_WAY_e ADC_RESULT_WAY);//ADC��ʼ��
extern uint16 adc_wait_once(ADCn_e ADCn , SPEED_nSCLK_e SPEED_nSCLK);//�ȴ���ȡADC������ֵ������10λ��
extern void adc_transition_request(ADCn_e ADCn , SPEED_nSCLK_e SPEED_nSCLK);//���ADcת�����󣬽��ͨ���жϷ�ʽ��ȡ
extern uint16 get_BandGap_adc(SPEED_nSCLK_e SPEED_nSCLK);//�ȴ���ȡ�ڲ��ο���ѹ��ADC����ֵ������10λ��
extern uint16 get_voltage_delay(ADCn_e ADCn , SPEED_nSCLK_e SPEED_nSCLK);//�ȴ���ȡһ����ȷ�ص�ѹֵ����λmV
void ADC_IRQHandler(void);//ADC�ɼ�����ж�

#endif /* __STC_ADC_H__ */