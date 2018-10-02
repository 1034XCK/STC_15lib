#ifndef __STC_CCP_H__
#define __STC_CCP_H__

typedef enum
{
	CCP0,//CCPģ��0
	CCP1,//CCPģ��1
	CCP2,//CCPģ��2
}CCPn_e;//CCPģ���ѡ��

typedef enum
{
	IDLE_PCA_RUN, //����ģʽ��PCA��������������
	IDLE_PCA_STOP,//����״̬��PCA������ֹͣ����
}IDLE_PCA_STATE_e;//����״̬PCAģ���Ƿ���ѡ��

typedef enum
{
	INTERNAL,			//PCA����������������ϵͳʱ�ӷ�Ƶ��ʱ��T0��Ƶ�õ�
	EXTERNAL_ECI, //PCA�����������������ⲿ���루����Ҫ���ⲿPWM������λʱ���õ���
}PCA_CLK_SOURCE_e;//PCA��������������Դѡ��

typedef enum
{
	PWM_8bit,//8λPWM������ƾ���
	PWM_7bit,//7λPWM������ƾ���
	PWM_6bit,//6λPWM������ƾ���
}PWM_ACCURACY_e;//PWM������ƾ���

typedef enum
{
	CCF_INTERRUPT_DIS,//��ֹ�����ж�
	CCF_INTERRUPT_RISE,//��������������ʱ�����ж�����
	CCF_INTERRUPT_FALL,//���������½���ʱ�����ж�����
	CCF_INTERRUPT_JUMP,//��������������ʱ�����ж�����
}CCF_INTERRUPT_e; //��β��񴥷��ж�����

typedef enum
{
	POSITIVE_PULSE_WIDTH,//������
	NEGATIVE_PULSE_WIDTH,//������
	CYCLE_LENGTH,//����
}SIGNAL_FEATURE_e;//�ź�ʱ������

void	PCA_IRQHandler (void);//�жϺ���

/***************************************PWMģʽ******************************************/
extern void CCP_pwm_init(CCPn_e  ,  IDLE_PCA_STATE_e  ,  PCA_CLK_SOURCE_e  ,  PWM_ACCURACY_e  ,  uint32 freq , uint8 duty , CCF_INTERRUPT_e);//PWMģʽ��ʼ��
extern void CCP_pwm_freq(PWM_ACCURACY_e  ,  uint32 freq);//�ı�PWMƵ��
extern void CCP_pwm_duty(CCPn_e  ,  uint8 duty);//�ı�PWMռ�ձ�

/*************************************����׽ģʽ***************************************/
extern void CCP_input_init(CCPn_e  ,  IDLE_PCA_STATE_e  ,  PCA_CLK_SOURCE_e  ,  uint32 freq  ,  CCF_INTERRUPT_e);//����ɼ�ģʽ��ʼ��

extern uint32 CCP_input_PULSE_WIDTH(CCPn_e  ,  SIGNAL_FEATURE_e);//��ȡ�ź�ʱ�䳤������

#endif /*__STC_CCP_H__*/