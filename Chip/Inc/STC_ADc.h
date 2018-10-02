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
	ADC_ALL,//所有P1口均用作AD采集
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

extern void adc_init(ADCn_e ADCn ,  ADC_RESULT_WAY_e ADC_RESULT_WAY);//ADC初始化
extern uint16 adc_wait_once(ADCn_e ADCn , SPEED_nSCLK_e SPEED_nSCLK);//等待获取ADC采样的值（精度10位）
extern void adc_transition_request(ADCn_e ADCn , SPEED_nSCLK_e SPEED_nSCLK);//提出ADc转换请求，结果通过中断方式获取
extern uint16 get_BandGap_adc(SPEED_nSCLK_e SPEED_nSCLK);//等待获取内部参考电压的ADC采样值（精度10位）
extern uint16 get_voltage_delay(ADCn_e ADCn , SPEED_nSCLK_e SPEED_nSCLK);//等待获取一个精确地电压值，单位mV
void ADC_IRQHandler(void);//ADC采集完成中断

#endif /* __STC_ADC_H__ */