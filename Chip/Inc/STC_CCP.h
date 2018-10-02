#ifndef __STC_CCP_H__
#define __STC_CCP_H__

typedef enum
{
	CCP0,//CCP模块0
	CCP1,//CCP模块1
	CCP2,//CCP模块2
}CCPn_e;//CCP模块号选择

typedef enum
{
	IDLE_PCA_RUN, //空闲模式下PCA计数器继续工作
	IDLE_PCA_STOP,//空闲状态下PCA计数器停止工作
}IDLE_PCA_STATE_e;//空闲状态PCA模块是否工作选择

typedef enum
{
	INTERNAL,			//PCA计数器计数脉冲由系统时钟分频或定时器T0分频得到
	EXTERNAL_ECI, //PCA计数器计数脉冲由外部输入（当需要和外部PWM保持相位时可用到）
}PCA_CLK_SOURCE_e;//PCA计数器计数脉冲源选择

typedef enum
{
	PWM_8bit,//8位PWM脉宽调制精度
	PWM_7bit,//7位PWM脉宽调制精度
	PWM_6bit,//6位PWM脉宽调制精度
}PWM_ACCURACY_e;//PWM脉宽调制精度

typedef enum
{
	CCF_INTERRUPT_DIS,//禁止触发中断
	CCF_INTERRUPT_RISE,//允许当出现上升沿时发起中断请求
	CCF_INTERRUPT_FALL,//允许当出现下降沿时发起中断请求
	CCF_INTERRUPT_JUMP,//允许当出现跳变沿时发起中断请求
}CCF_INTERRUPT_e; //如何捕获触发中断请求

typedef enum
{
	POSITIVE_PULSE_WIDTH,//正脉宽
	NEGATIVE_PULSE_WIDTH,//负脉宽
	CYCLE_LENGTH,//周期
}SIGNAL_FEATURE_e;//信号时间特征

void	PCA_IRQHandler (void);//中断函数

/***************************************PWM模式******************************************/
extern void CCP_pwm_init(CCPn_e  ,  IDLE_PCA_STATE_e  ,  PCA_CLK_SOURCE_e  ,  PWM_ACCURACY_e  ,  uint32 freq , uint8 duty , CCF_INTERRUPT_e);//PWM模式初始化
extern void CCP_pwm_freq(PWM_ACCURACY_e  ,  uint32 freq);//改变PWM频率
extern void CCP_pwm_duty(CCPn_e  ,  uint8 duty);//改变PWM占空比

/*************************************脉宽捕捉模式***************************************/
extern void CCP_input_init(CCPn_e  ,  IDLE_PCA_STATE_e  ,  PCA_CLK_SOURCE_e  ,  uint32 freq  ,  CCF_INTERRUPT_e);//脉宽采集模式初始化

extern uint32 CCP_input_PULSE_WIDTH(CCPn_e  ,  SIGNAL_FEATURE_e);//获取信号时间长度特征

#endif /*__STC_CCP_H__*/