#include "common.h"
#include "STC_ADc.h"
#include "STC_interrupt.h"

uint16 data ADC_interrupt_result[8]={0};

/**
 *  @brief		ADC初始化（将某个IO口设置为模拟功能使用）
 *	@param		ADCn 通道号
 *	@param		interrupt_able ADC采集方式
 *	@warning	
 *	@sampleusage:	adc_init(ADC0,WAIT_ONCE);	//将P1.0作为模拟功能ADC0使用,并用等待的方式采集
 */
void adc_init(ADCn_e ADCn ,  ADC_RESULT_WAY_e ADC_RESULT_WAY)
{
	BIT_CLR(ADC_CONTR,3);//停止AD转换
	if(ADCn == ADC_ALL)	P1ASF = 0xff;//设置P1口的模拟功能
	else BIT_SET(P1ASF,ADCn);//设置P1口的模拟功能
	ADC_RES=0;ADC_RESL=0;//将AD采集结果寄存器清零
	BIT_CLR(ADC_CONTR,4);//将AD采集结束标志位清零
	BIT_SET(CLK_DIV,5);//ADC_RES[1:0]存放高两位，ADC_RESL[7:0]存放底8位
	if(ADC_RESULT_WAY == ADC_INTERRUPT)
	{
		set_vector_handler(ADC_VECTORn , ADC_IRQHandler);
		Whether_IRQ(ADC_VECTORn , IRQ_enable);
	}
	else
	{
		Whether_IRQ(ADC_VECTORn , IRQ_disable);
	}
	BIT_SET(ADC_CONTR,7);//开启AD转换总开关
}

/*!
 *	@brief		等待获取ADC采样的值（精度10位）
 *	@param		ADCn					需要得到哪一路的AD值
 *	@param		SPEED_nSCLK		以多快的采集速度进行采集（速度越快精度越低）
 *	@warning	一次只能采集一路，STC单片机最多只有一个A/D转换器
 *	@sampleusage:	adc_wait_once(ADC0 , SPEED_90SCLK); //以90个系统时钟的速度采集ADC0，并返回值
 */
uint16 adc_wait_once(ADCn_e ADCn , SPEED_nSCLK_e SPEED_nSCLK)
{
	if(ADCn<ADC_ALL)REPLACE(ADC_CONTR,2,0,ADCn);//即将采集的通道号P1[7:0]
	REPLACE(ADC_CONTR,6,5,SPEED_nSCLK);//设置转换速度
	BIT_SET(ADC_CONTR,3);//开始AD转换
	while( ! BIT_GET(ADC_CONTR,4));//等待转换结束
	BIT_CLR(ADC_CONTR,4);//清除转换完成标志位
	return (ADC_RES<<8) | ADC_RESL;//返回10位数据
}

/*!
 *	@brief		提出ADc转换请求，结果通过中断方式获取
 *	@param		ADCn					需要得到哪一路的AD值
 *	@param		SPEED_nSCLK		以多快的采集速度进行采集（速度越快精度越低）
 *	@warning	
 *	@sampleusage:	adc_transition_request(ADC0 , SPEED_540SCLK);//请求一次AD转换，结果请过540个系统时钟后在中断内查看
 */

void adc_transition_request(ADCn_e ADCn , SPEED_nSCLK_e SPEED_nSCLK)
{
	if(ADCn<ADC_ALL)REPLACE(ADC_CONTR,2,0,ADCn);//即将采集的通道号P1[7:0]
	REPLACE(ADC_CONTR,6,5,SPEED_nSCLK);//设置转换速度
	BIT_SET(ADC_CONTR,3);//开始AD转换
}

/*!
 *	@brief		等待获取内部基准电压的ADc的值
 *	@param		SPEED_nSCLK	ADc转化速度
 *	@warning	转化速度建议为540个系统时钟，这样较为精确
							此获取方式为查询等待方式
							使用此函数不会影响其他外部ADc转换
 *	@sampleusage:	get_BandGap_adc(SPEED_540SCLK);
 */

uint16 get_BandGap_adc(SPEED_nSCLK_e SPEED_nSCLK)
{
	uint8 after_P1ASF = P1ASF;
	
	BIT_CLR(ADC_CONTR,3);//停止AD转换
	P1ASF = 0x00;
	ADC_RES=0;ADC_RESL=0;//将AD采集结果寄存器清零
	BIT_CLR(ADC_CONTR,4);//将AD采集结束标志位清零
	BIT_SET(CLK_DIV,5);//ADC_RES[1:0]存放高两位，ADC_RESL[7:0]存放底8位
	BIT_SET(ADC_CONTR,7);//开启AD转换总开关
	REPLACE(ADC_CONTR,6,5,SPEED_nSCLK);//设置转换速度
	BIT_SET(ADC_CONTR,3);//开始AD转换
	while( ! BIT_GET(ADC_CONTR,4));//等待转换结束
	BIT_CLR(ADC_CONTR,4);//清除转换完成标志位
	P1ASF = after_P1ASF;
	return (ADC_RES<<8) | ADC_RESL;//返回10位数据
}

/*!
 *	@brief		等待获取一个精确地电压值，单位mV
 *	@param		ADCn					需要得到哪一路的AD值
 *	@param		SPEED_nSCLK		以多快的采集速度进行采集（速度越快精度越低）
 *	@warning	这里采用的是等待采集方式
 *	@sampleusage:	get_voltage_delay(ADC0 , SPEED_90SCLK);//以90个系统时钟的速度采集ADC0，再以540个系统时钟的速度采集内部基准值，最后进行运算输出以mV为单位的电压值
 */

uint16 get_voltage_delay(ADCn_e ADCn , SPEED_nSCLK_e SPEED_nSCLK)
{
	return 1246L * adc_wait_once(ADCn , SPEED_nSCLK) / get_BandGap_adc(SPEED_540SCLK);//以540个系统时钟的速度采集内部基准值，最后进行运算，返回精确的电压值，单位mV
}

/*!
 *	@brief		ADC采集完成中断
 *	@param		
 *	@warning	
 *	@sampleusage:	
 */

void ADC_IRQHandler(void)
{
	BIT_CLR(ADC_CONTR,4);//清除转换完成标志位
	ADC_interrupt_result[ACQUIRE(ADC_CONTR,2,0)] = (ADC_RES<<8) | ADC_RESL;//返回10位数据
}