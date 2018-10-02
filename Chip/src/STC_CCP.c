/*
 * ����ͷ�ļ�
 */
#include "common.h"
#include "STC_CCP.h"
#include "STC_gpio.h"
#include "STC_interrupt.h"

/*!
 *	@brief		PWMģʽ��ʼ��
 *	@param		CCPn						CCPģ���ѡ��
							IDLE_PCA_STATE	����ģʽ����δ���CCP״̬(��Ҫ��CCP�е�PCA������)
							PCA_CLK_SOURCE	PCA��������������Դѡ��
							PWM_ACCURACY		PWM���ƾ���
							freq						PWM��ʼƵ��
							duty						PWM��ʼռ�ձ�
							CCF_INTERRUPT		��β��񴥷��ж�����
 *	@warning	CCP_PWMģʽ�������IO�ڹ���ģʽ����Ϊ�������룬�ϵ��ʼ��Ϊ׼˫���
              Ҫ�������ж�Ӧ��Ҫ��λMAT,���ֲ���ûд
							��PCA�����������������ⲿ����ʱ���ܵ�����Ƶ�ʣ������ʼ��������Ƶ��Ҳû���ã�PWM���Ƶ�ʵ����ⲿ����Ƶ��/256
							freq���Ըı�PWMƵ�ʣ�����Ӱ������ģ���Ƶ�ʣ���Ϊ����ģ�鹲��һ��ʱ��Դ
							freq���������ޣ����ô�����߿�����Ƶ��max_freq = EXTAL_IN_Hz/(64*(1+ACQUIRE(CLK_DIV,2,0)))
 *	@sampleusage:	CCP_pwm_init(CCP0,IDLE_PCA_RUN,INTERNAL,PWM_8bit,50,26,CCF_INTERRUPT_DIS); //��CCP0ģ�顢������״̬����Ȼ���С�ʹ���ڲ�ʱ�ӡ�8λ����PWM����ʼƵ��50Hz����ʼռ�ձ�26/255���������ж�
 */
 
void CCP_pwm_init(CCPn_e CCPn  ,  IDLE_PCA_STATE_e IDLE_PCA_STATE  ,  PCA_CLK_SOURCE_e PCA_CLK_SOURCE  ,
								  PWM_ACCURACY_e PWM_ACCURACY  ,  uint32 freq , uint8 duty , CCF_INTERRUPT_e CCF_INTERRUPT)
{
	uint32 max_freq = 0;//���Ƶ��
	uint32 divide_factor=0;//��Ƶϵ��
	
	if(ECI==p12 && CCP_0==p11 && CCP_1==p10 && CCP_2==p37)REPLACE(P_SW1,5,4,0);//����CCP�˿�
	if(ECI==p34 && CCP_0==p35 && CCP_1==p36 && CCP_2==p37)REPLACE(P_SW1,5,4,1);//����CCP�˿�
	if(ECI==p24 && CCP_0==p25 && CCP_1==p26 && CCP_2==p27)REPLACE(P_SW1,5,4,2);//����CCP�˿�
	
	BIT_CLR(CCON,7);//��������������־
	BIT_CLR(CCON,6);//ֹͣ����
	CH=0;CL=0;//���PCA������
	
	if(IDLE_PCA_STATE == IDLE_PCA_RUN)	BIT_CLR(CMOD,7);//����ģʽ��PCA��������������
	else if(IDLE_PCA_STATE == IDLE_PCA_STOP)	BIT_SET(CMOD,7);//����״̬��PCA������ֹͣ����
			 else return;//����ģʽ��CCP����״̬���ô���
	
	if(CCPn == CCP0)
	{
		BIT_CLR(CCON,0);//�������/ƥ���жϱ�־
		if(CCF_INTERRUPT == CCF_INTERRUPT_DIS)	CCAPM0=0x42;//��ֹ�����ж�
		else
		{
			if(CCF_INTERRUPT == CCF_INTERRUPT_RISE)	 CCAPM0=0x63;//��������������ʱ�����ж�����
			else if(CCF_INTERRUPT == CCF_INTERRUPT_FALL)	CCAPM0=0x53;//���������½���ʱ�����ж�����
			else if(CCF_INTERRUPT == CCF_INTERRUPT_JUMP)	CCAPM0=0x73;//��������������ʱ�����ж�����
		}
		
		if(PWM_ACCURACY == PWM_8bit)
	  {
			REPLACE(PCA_PWM0,7,6,0);//8λPWM
			max_freq = EXTAL_IN_Hz/(256*(1+ACQUIRE(CLK_DIV,2,0)));//��������PWMƵ��
			if(duty==0) {CCAP0L=0xff;CCAP0H=0xff;BIT_SET(PCA_PWM0,1);BIT_SET(PCA_PWM0,0);}//����0ռ�ձ�
			else {CCAP0L = (0xff-duty);CCAP0H = (0xff-duty);BIT_CLR(PCA_PWM0,0);BIT_CLR(PCA_PWM0,1);}//����ռ�ձ�
		}
		else if(PWM_ACCURACY == PWM_7bit)
				 {
					 REPLACE(PCA_PWM0,7,6,1);//7λPWM
					 max_freq = EXTAL_IN_Hz/(128*(1+ACQUIRE(CLK_DIV,2,0)));//��������PWMƵ��
					 if(duty==0) {CCAP0L=0xff;CCAP0H=0xff;BIT_SET(PCA_PWM0,1);BIT_SET(PCA_PWM0,0);}//����0ռ�ձ�
				   else {CCAP0L = (0x7f-(duty>>1));CCAP0H = (0x7f-(duty>>1));BIT_CLR(PCA_PWM0,0);BIT_CLR(PCA_PWM0,1);}//����ռ�ձ�
				 }
				 else if(PWM_ACCURACY == PWM_6bit)
				 {
					 REPLACE(PCA_PWM0,7,6,2);//6λPWM
					 max_freq = EXTAL_IN_Hz/(64*(1+ACQUIRE(CLK_DIV,2,0)));//��������PWMƵ��
					 if(duty==0){CCAP0L=0xff;CCAP0H=0xff;BIT_SET(PCA_PWM0,1);BIT_SET(PCA_PWM0,0);}//����0ռ�ձ�
					 else {CCAP0L = (0x3f-(duty>>2));CCAP0H = (0x3f-(duty>>2));BIT_CLR(PCA_PWM0,0);BIT_CLR(PCA_PWM0,1);}//����ռ�ձ�
				 }
				 else return;//PWM�������ô���
	}
	else if(CCPn == CCP1)
			 {
				 BIT_CLR(CCON,1);//�������/ƥ���жϱ�־
				 if(CCF_INTERRUPT == CCF_INTERRUPT_DIS)	CCAPM1=0x42;//��ֹ�����ж�
				 else
				 {
					 if(CCF_INTERRUPT == CCF_INTERRUPT_RISE)	 CCAPM1=0x63;//��������������ʱ�����ж�����
					 else if(CCF_INTERRUPT == CCF_INTERRUPT_FALL)	CCAPM1=0x53;//���������½���ʱ�����ж�����
								else if(CCF_INTERRUPT == CCF_INTERRUPT_JUMP)	CCAPM1=0x73;//��������������ʱ�����ж�����
				 }
				 
				 if(PWM_ACCURACY == PWM_8bit)
				 {
					 REPLACE(PCA_PWM1,7,6,0);//8λPWM
					 max_freq = EXTAL_IN_Hz/(256*(1+ACQUIRE(CLK_DIV,2,0)));//��������PWMƵ��
					 if(duty==0) {CCAP1L=0xff;CCAP1H=0xff;BIT_SET(PCA_PWM1,1);BIT_SET(PCA_PWM1,0);}//����0ռ�ձ�
					 else {CCAP1L = (0xff-duty);CCAP1H = (0xff-duty);BIT_CLR(PCA_PWM1,0);BIT_CLR(PCA_PWM1,1);}//����ռ�ձ�
				 }
				 else if(PWM_ACCURACY == PWM_7bit)
				 {
					 REPLACE(PCA_PWM1,7,6,1);//7λPWM
					 max_freq = EXTAL_IN_Hz/(128*(1+ACQUIRE(CLK_DIV,2,0)));//��������PWMƵ��
					 if(duty==0) {CCAP1L=0xff;CCAP1H=0xff;BIT_SET(PCA_PWM1,1);BIT_SET(PCA_PWM1,0);}//����0ռ�ձ�
					 else {CCAP1L = (0x7f-(duty>>1));CCAP1H = (0x7f-(duty>>1));BIT_CLR(PCA_PWM1,0);BIT_CLR(PCA_PWM1,1);}//����ռ�ձ�
				 }
						 else if(PWM_ACCURACY == PWM_6bit)
									{
										REPLACE(PCA_PWM1,7,6,2);//6λPWM
										max_freq = EXTAL_IN_Hz/(64*(1+ACQUIRE(CLK_DIV,2,0)));//��������PWMƵ��
										if(duty==0){CCAP1L=0xff;CCAP1H=0xff;BIT_SET(PCA_PWM1,1);BIT_SET(PCA_PWM1,0);}//����0ռ�ձ�
										else {CCAP1L = (0x3f-(duty>>2));CCAP1H = (0x3f-(duty>>2));BIT_CLR(PCA_PWM1,0);BIT_CLR(PCA_PWM1,1);}//����ռ�ձ�
									}
									else return;//PWM�������ô���
			 }
			 else if(CCPn == CCP2)
			 {
				 BIT_CLR(CCON,2);//�������/ƥ���жϱ�־
				 if(CCF_INTERRUPT == CCF_INTERRUPT_DIS)	CCAPM2=0x42;//��ֹ�����ж�
				 else
				 {
					 if(CCF_INTERRUPT == CCF_INTERRUPT_RISE)	 CCAPM2=0x63;//��������������ʱ�����ж�����
					 else if(CCF_INTERRUPT == CCF_INTERRUPT_FALL)	CCAPM2=0x53;//���������½���ʱ�����ж�����
					 else if(CCF_INTERRUPT == CCF_INTERRUPT_JUMP)	CCAPM2=0x73;//��������������ʱ�����ж�����
				 }
				 
				 if(PWM_ACCURACY == PWM_8bit)
				 {
					 REPLACE(PCA_PWM2,7,6,0);//8λPWM
					 max_freq = EXTAL_IN_Hz/(256*(1+ACQUIRE(CLK_DIV,2,0)));//��������PWMƵ��
					 if(duty==0) {CCAP2L=0xff;CCAP2H=0xff;BIT_SET(PCA_PWM2,1);BIT_SET(PCA_PWM2,0);}//����0ռ�ձ�
					 else {CCAP2L = (0xff-duty);CCAP2H = (0xff-duty);BIT_CLR(PCA_PWM2,0);BIT_CLR(PCA_PWM2,1);}//����ռ�ձ�
				 }
				 else if(PWM_ACCURACY == PWM_7bit)
				 {
					 REPLACE(PCA_PWM2,7,6,1);//7λPWM
					 max_freq = EXTAL_IN_Hz/(128*(1+ACQUIRE(CLK_DIV,2,0)));//��������PWMƵ��
					 if(duty==0) {CCAP2L=0xff;CCAP2H=0xff;BIT_SET(PCA_PWM2,1);BIT_SET(PCA_PWM2,0);}//����0ռ�ձ�
					 else {CCAP2L = (0x7f-(duty>>1));CCAP2H = (0x7f-(duty>>1));BIT_CLR(PCA_PWM2,0);BIT_CLR(PCA_PWM2,1);}//����ռ�ձ�
				 }
							else if(PWM_ACCURACY == PWM_6bit)
							{
								REPLACE(PCA_PWM2,7,6,2);//6λPWM
								max_freq = EXTAL_IN_Hz/(64*(1+ACQUIRE(CLK_DIV,2,0)));//��������PWMƵ��
								if(duty==0){CCAP2L=0xff;CCAP2H=0xff;BIT_SET(PCA_PWM2,1);BIT_SET(PCA_PWM2,0);}//����0ռ�ձ�
								else {CCAP2L = (0x3f-(duty>>2));CCAP2H = (0x3f-(duty>>2));BIT_CLR(PCA_PWM2,0);BIT_CLR(PCA_PWM2,1);}//����ռ�ձ�
							}
							else return;//PWM�������ô���
			 }
			 else return;//CCPģ������ô���
	
	if(PCA_CLK_SOURCE == EXTERNAL_ECI)	REPLACE(CMOD,3,1,3);//PCA�����������������ⲿ���루����Ҫ���ⲿPWM������λʱ���õ���
	else if(PCA_CLK_SOURCE == INTERNAL)
			 {
				 if(freq!=0)
				 {
					 if(freq > max_freq)	return;//����Ƶ�ʹ���
					 else if(freq == max_freq)	REPLACE(CMOD,3,1,4);//ʹ��ϵͳʱ�Ӳ���Ƶ��ΪPCA��������������ʱ��
								else if(freq >= (max_freq/2))	 REPLACE(CMOD,3,1,1);//ʹ��ϵͳʱ��2��Ƶ��ΪPCA��������������ʱ��
										 else if(freq >= ((max_freq/4)-4) && freq <= (5+(max_freq/4)))	 REPLACE(CMOD,3,1,5);//ʹ��ϵͳʱ��4��Ƶ��ΪPCA��������������ʱ��
													else if(freq >= ((max_freq/6)-4) && freq <= (5+(max_freq/6)))	 REPLACE(CMOD,3,1,6);//ʹ��ϵͳʱ��6��Ƶ��ΪPCA��������������ʱ��
															 else if(freq >= ((max_freq/8)-4) && freq <= (5+(max_freq/8)))	 REPLACE(CMOD,3,1,7);//ʹ��ϵͳʱ��8��Ƶ��ΪPCA��������������ʱ��
																		else if(freq >= ((max_freq/12)-4) && freq <= (5+(max_freq/12))) REPLACE(CMOD,3,1,0);//ʹ��ϵͳʱ��12��Ƶ��ΪPCA��������������ʱ��
																				 else
																				 {
																					 divide_factor=max_freq/freq;//�����Ƶϵ��
																					 if(divide_factor > 0xffff) divide_factor = 0xffff;//���÷�Ƶϵ���޶�
																					 divide_factor = 0xffff-divide_factor;//׼������T0��ʱ����ֵ
																					 
																					 REPLACE(CMOD,3,1,2);//ʹ�ö�ʱ��0�������ΪPCA��������������ʱ��
																					 BIT_SET(AUXR,7);//T0ʱ�ӹ�����1Tģʽ��
																					 REPLACE(TMOD,3,0,0);//T0����16λ�Զ���װ��ʱ��
																					 TL0 = divide_factor;//��Ƶϵ��
																					 TH0 = divide_factor >> 8;//��Ƶϵ��
																					 TF0 = 0;//���T0�����־
																					 TR0 = 1;//����T0��ʱʱ��
																				 }
				}//��Ƶ������Ϊ��0����Ƶ��Ϊ��һ�γ�ʼ����Ƶ�ʻ��ϵ縴λĬ��Ƶ��EXTAL_IN_Hz/12
			}
			else return;//PCA������������������Դ���ô���
	
	CR=1;//PCA��������ʼ����
}

/*!
 *	@brief		�ı�PWMƵ��
 *	@param		PWM_ACCURACY	PWMʹ�õľ���			
							freq					Ҫ�ı��Ƶ��
 *	@warning	����CCPģ�鹲��һ��ʱ��Դ������Ƶ��������һ���ģ���CCP0ΪPWMģʽ��CCP1�ǲ�׽ģʽ����ı�PWMƵ�ʺ�׽����ֵҲ����֮�ı�
              freq���������ޣ����ô�����߿�����Ƶ��max_freq = EXTAL_IN_Hz/(64*(1+ACQUIRE(CLK_DIV,2,0)))
 *	@sampleusage:	CCP_pwm_freq(PWM_8bit,1400); //ʹ��8λ���ȣ�����Ϊ1400Hz
 */

void CCP_pwm_freq(PWM_ACCURACY_e PWM_ACCURACY , uint32 freq)//�ı�PWMƵ��
{
	uint32 max_freq = 0;
	uint32 divide_factor=0;
	
	max_freq = EXTAL_IN_Hz/(0xff >> PWM_ACCURACY*(1+ACQUIRE(CLK_DIV,2,0)));//��������PWMƵ��
	if(freq!=0)
	{
		if(freq > max_freq)	return;//����Ƶ�ʹ���
		else if(freq == max_freq)	REPLACE(CMOD,3,1,4);//ʹ��ϵͳʱ�Ӳ���Ƶ��ΪPCA��������������ʱ��
				 else if(freq >= (max_freq/2))	 REPLACE(CMOD,3,1,1);//ʹ��ϵͳʱ��2��Ƶ��ΪPCA��������������ʱ��
							else if(freq >= ((max_freq/4)-4) && freq <= (5+(max_freq/4)))	 REPLACE(CMOD,3,1,5);//ʹ��ϵͳʱ��4��Ƶ��ΪPCA��������������ʱ��
									 else if(freq >= ((max_freq/6)-4) && freq <= (5+(max_freq/6)))	 REPLACE(CMOD,3,1,6);//ʹ��ϵͳʱ��6��Ƶ��ΪPCA��������������ʱ��
												else if(freq >= ((max_freq/8)-4) && freq <= (5+(max_freq/8)))	 REPLACE(CMOD,3,1,7);//ʹ��ϵͳʱ��8��Ƶ��ΪPCA��������������ʱ��
														 else if(freq >= ((max_freq/12)-4) && freq <= (5+(max_freq/12))) REPLACE(CMOD,3,1,0);//ʹ��ϵͳʱ��12��Ƶ��ΪPCA��������������ʱ��
																	else
																	{
																		divide_factor=max_freq/freq;//�����Ƶϵ��
																		if(divide_factor > 0xffff) divide_factor = 0xffff;//���÷�Ƶϵ���޶�
																		divide_factor = 0xffff-divide_factor;//׼������T0��ʱ����ֵ
																		
																		REPLACE(CMOD,3,1,2);//ʹ�ö�ʱ��0�������ΪPCA��������������ʱ��
																		BIT_SET(AUXR,7);//T0ʱ�ӹ�����1Tģʽ��
																		REPLACE(TMOD,3,0,0);//T0����16λ�Զ���װ��ʱ��
																		TL0 = divide_factor;//��Ƶϵ��
																		TH0 = divide_factor >> 8;//��Ƶϵ��
																		TF0 = 0;//���T0�����־
																		TR0 = 1;//����T0��ʱʱ��
																	}
	}//��Ƶ������Ϊ��0����Ƶ��Ϊ��һ�γ�ʼ����Ƶ��
}

/*!
 *	@brief		����PWMռ�ձ�
 *	@param		CCPn				ģ���
							duty				ռ�ձ�
 *	@warning	ռ�ձȵķ�Χ��0~255
 *	@sampleusage:	CCP_pwm_duty(CCP0 , 12); //��CCP0��PWM��ռ�ձ�����Ϊ12/255
 */

void CCP_pwm_duty(CCPn_e CCPn , uint8 duty)
{
	if(CCPn == CCP0)
	{
		if(0 == ACQUIRE(PCA_PWM0,7,6))//��ȡPWM���þ���ֵ
		{
			if(duty==0) {CCAP0L=0xff;CCAP0H=0xff;BIT_SET(PCA_PWM0,1);BIT_SET(PCA_PWM0,0);}//����0ռ�ձ�
			else {CCAP0L = (0xff-duty);CCAP0H = (0xff-duty);BIT_CLR(PCA_PWM0,0);BIT_CLR(PCA_PWM0,1);}//����ռ�ձ�
		}
		else if(1 == ACQUIRE(PCA_PWM0,7,6))//��ȡPWM���þ���ֵ
				 {
					 if(duty==0) {CCAP0L=0xff;CCAP0H=0xff;BIT_SET(PCA_PWM0,1);BIT_SET(PCA_PWM0,0);}//����0ռ�ձ�
				   else {CCAP0L = (0x7f-(duty>>1));CCAP0H = (0x7f-(duty>>1));BIT_CLR(PCA_PWM0,0);BIT_CLR(PCA_PWM0,1);}//����ռ�ձ�
				 }
				 else if(2 == ACQUIRE(PCA_PWM0,7,6))//��ȡPWM���þ���ֵ
							{
								if(duty==0){CCAP0L=0xff;CCAP0H=0xff;BIT_SET(PCA_PWM0,1);BIT_SET(PCA_PWM0,0);}//����0ռ�ձ�
								else {CCAP0L = (0x3f-(duty>>2));CCAP0H = (0x3f-(duty>>2));BIT_CLR(PCA_PWM0,0);BIT_CLR(PCA_PWM0,1);}//����ռ�ձ�
							}
	}
	else if(CCPn == CCP1)
			 {
				 if(0 == ACQUIRE(PCA_PWM1,7,6))//��ȡPWM���þ���ֵ
				 {
					 if(duty==0) {CCAP1L=0xff;CCAP1H=0xff;BIT_SET(PCA_PWM1,1);BIT_SET(PCA_PWM1,0);}//����0ռ�ձ�
					 else {CCAP1L = (0xff-duty);CCAP1H = (0xff-duty);BIT_CLR(PCA_PWM1,0);BIT_CLR(PCA_PWM1,1);}//����ռ�ձ�
				 }
				 else if(1 == ACQUIRE(PCA_PWM1,7,6))//��ȡPWM���þ���ֵ
							{
								if(duty==0) {CCAP1L=0xff;CCAP1H=0xff;BIT_SET(PCA_PWM1,1);BIT_SET(PCA_PWM1,0);}//����0ռ�ձ�
								else {CCAP1L = (0x7f-(duty>>1));CCAP1H = (0x7f-(duty>>1));BIT_CLR(PCA_PWM1,0);BIT_CLR(PCA_PWM1,1);}//����ռ�ձ�
							}
							else if(2 == ACQUIRE(PCA_PWM1,7,6))//��ȡPWM���þ���ֵ
									 {
										 if(duty==0){CCAP1L=0xff;CCAP1H=0xff;BIT_SET(PCA_PWM1,1);BIT_SET(PCA_PWM1,0);}//����0ռ�ձ�
										 else {CCAP1L = (0x3f-(duty>>2));CCAP1H = (0x3f-(duty>>2));BIT_CLR(PCA_PWM1,0);BIT_CLR(PCA_PWM1,1);}//����ռ�ձ�
									 }
			 }
			 else if(CCPn == CCP2)
						{
							if(0 == ACQUIRE(PCA_PWM2,7,6))//��ȡPWM���þ���ֵ
							{
								if(duty==0) {CCAP2L=0xff;CCAP2H=0xff;BIT_SET(PCA_PWM2,1);BIT_SET(PCA_PWM2,0);}//����0ռ�ձ�
								else {CCAP2L = (0xff-duty);CCAP2H = (0xff-duty);BIT_CLR(PCA_PWM2,0);BIT_CLR(PCA_PWM2,1);}//����ռ�ձ�
							}
							else if(1 == ACQUIRE(PCA_PWM2,7,6))//��ȡPWM���þ���ֵ
									 {
										 if(duty==0) {CCAP2L=0xff;CCAP2H=0xff;BIT_SET(PCA_PWM2,1);BIT_SET(PCA_PWM2,0);}//����0ռ�ձ�
										 else {CCAP2L = (0x7f-(duty>>1));CCAP2H = (0x7f-(duty>>1));BIT_CLR(PCA_PWM2,0);BIT_CLR(PCA_PWM2,1);}//����ռ�ձ�
									 }
									 else if(2 == ACQUIRE(PCA_PWM2,7,6))//��ȡPWM���þ���ֵ
												{
													if(duty==0){CCAP2L=0xff;CCAP2H=0xff;BIT_SET(PCA_PWM2,1);BIT_SET(PCA_PWM2,0);}//����0ռ�ձ�
													else {CCAP2L = (0x3f-(duty>>2));CCAP2H = (0x3f-(duty>>2));BIT_CLR(PCA_PWM2,0);BIT_CLR(PCA_PWM2,1);}//����ռ�ձ�
												}
						}
}

/*!
 *	@brief		����ģʽ��ʼ��
 *	@param		CCPn						CCPģ���ѡ��
							IDLE_PCA_STATE	����ģʽ����δ���CCP״̬(��Ҫ��CCP�е�PCA������)
							PCA_CLK_SOURCE	PCA��������������Դѡ��
							freq						ʱ��ԴƵ�� = ��ֵ/ʱ�䣨��Ϊ��λ��
															�磺��Ҫ����0.02ms��������ʾ��ֵ��ҪΪ��256������freq = 256/0.02
							CCF_INTERRUPT		��β��񴥷��ж�����
 *	@warning	��λ����ʱ��=1/freq����Ӱ��������ɼ��ľ��ȣ�ʱ��Ƶ��Խ�ߡ���λ����ʱ��Խ�̡��ɼ�����ʱ�侫��Խ�ߣ�����Ӱ������ģ���Ƶ�ʣ���Ϊ����ģ�鹲��һ��ʱ��Դ
              freq���������ޣ���󲻵ô��ھ���Ƶ��EXTAL_IN_Hz��
              CCF_INTERRUPT����Ҫ���������ź�����ʱ�������CCF_INTERRUPT_RISE��CCF_INTERRUPT_FALL��CCF_INTERRUPT_JUMP���ִ�����ʽ������ʹ��ǰ���֣���Ϊ�������Բ�������Ƶ�ʵ��źţ�����ѡ�������ź����Ͷ�����
                           ����Ҫ���������źŵ���������ʱ����ֻ��ʹ��CCF_INTERRUPT_JUMP������ʽ�������ܹ�����
              CCP����ģʽ����IO�ڵĹ���ģʽ����Ϊǿ�������ģʽ���ϵ��ʼ��Ϊ׼˫���
              �������Եó����ڸ�Ƶ�ź�����CCP����ʱ�����ʴﵽ����Ƶ��ʱ��Ҫ�����δ���ʱ��������256���ľ������ڷ��ɻ���ȶ����ݣ��������ź��ٶȱ���������Ҫ��
 *	@sampleusage:	CCP_input_init(CCP0  ,  IDLE_PCA_RUN  ,  INTERNAL  ,  EXTAL_IN_Hz  ,  CCF_INTERRUPT_JUMP);//CCP0�����źŲ���ģʽ������ģʽ��CCPģ�����ɹ�����ʹ���ڲ�ʱ����Ϊ����Դ������ʱ��Ƶ������Ϊ����Ƶ�ʡ�������ʽΪ�����ش���
 */

void CCP_input_init(CCPn_e CCPn  ,  IDLE_PCA_STATE_e IDLE_PCA_STATE  ,  PCA_CLK_SOURCE_e PCA_CLK_SOURCE  ,  uint32 freq  ,  CCF_INTERRUPT_e CCF_INTERRUPT)
{
	uint32 divide_factor=0;//��Ƶϵ��
	if(ECI==p12 && CCP_0==p11 && CCP_1==p10 && CCP_2==p37)REPLACE(P_SW1,5,4,0);//����CCP0�˿�
	if(ECI==p34 && CCP_0==p35 && CCP_1==p36 && CCP_2==p37)REPLACE(P_SW1,5,4,1);//����CCP0�˿�
	if(ECI==p24 && CCP_0==p25 && CCP_1==p26 && CCP_2==p27)REPLACE(P_SW1,5,4,2);//����CCP0�˿�
	
	BIT_CLR(CCON,7);//��������������־
	BIT_CLR(CCON,6);//ֹͣ����
	CH=0;CL=0;//���PCA������
	
	if(IDLE_PCA_STATE == IDLE_PCA_RUN)	BIT_CLR(CMOD,7);//����ģʽ��PCA��������������
	else if(IDLE_PCA_STATE == IDLE_PCA_STOP)	BIT_SET(CMOD,7);//����״̬��PCA������ֹͣ����
			 else return;//����ģʽ��CCP����״̬���ô���
	
	if(CCPn == CCP0)
	{
		BIT_CLR(CCON,0);//����жϱ�־
		CCAP0L=0;//�����׽����ֵ
		CCAP0H=0;//�����׽����ֵ
		PCA_PWM0=0x00;//���PWMģʽ�Ĵ���
		if(CCF_INTERRUPT == CCF_INTERRUPT_RISE)	 CCAPM0=0x21;//�����ز���
		else if(CCF_INTERRUPT == CCF_INTERRUPT_FALL)	CCAPM0=0x11;//�½��ز���
		else if(CCF_INTERRUPT == CCF_INTERRUPT_JUMP)	CCAPM0=0x31;//�����ز���
	}
	else if(CCPn == CCP1)
			 {
				 BIT_CLR(CCON,1);//�������/ƥ���жϱ�־
				 CCAP1L=0;//�����׽����ֵ
				 CCAP1H=0;//�����׽����ֵ
				 PCA_PWM1=0x00;//���PWMģʽ�Ĵ���
				 if(CCF_INTERRUPT == CCF_INTERRUPT_RISE)	 CCAPM1=0x21;//�����ز���
				 else if(CCF_INTERRUPT == CCF_INTERRUPT_FALL)	CCAPM1=0x11;//�½��ز���
				 else if(CCF_INTERRUPT == CCF_INTERRUPT_JUMP)	CCAPM1=0x31;//�����ز���
			 }
			 else if(CCPn == CCP2)
						{
							BIT_CLR(CCON,2);//�������/ƥ���жϱ�־
							CCAP2L=0;//�����׽����ֵ
							CCAP2H=0;//�����׽����ֵ
							PCA_PWM2=0x00;//���PWMģʽ�Ĵ���
							if(CCF_INTERRUPT == CCF_INTERRUPT_RISE)	 CCAPM2=0x21;//�����ز���
							else if(CCF_INTERRUPT == CCF_INTERRUPT_FALL)	CCAPM2=0x11;//�½��ز���
							else if(CCF_INTERRUPT == CCF_INTERRUPT_JUMP)	CCAPM2=0x31;//�����ز���
						}
						else return;//CCPģ������ô���
	if(PCA_CLK_SOURCE == EXTERNAL_ECI)	REPLACE(CMOD,3,1,3);//PCA�����������������ⲿ���루����Ҫ���ⲿPWM������λʱ���õ���
	else if(PCA_CLK_SOURCE == INTERNAL)
			 {
				 if(freq!=0)
				 {
					 if(freq > EXTAL_IN_Hz)	return;//����Ƶ�ʹ���
					 else if(freq == EXTAL_IN_Hz)	REPLACE(CMOD,3,1,4);//ʹ��ϵͳʱ�Ӳ���Ƶ��ΪPCA��������������ʱ��
								else if(freq >= (EXTAL_IN_Hz/2))	 REPLACE(CMOD,3,1,1);//ʹ��ϵͳʱ��2��Ƶ��ΪPCA��������������ʱ��
										 else if(freq >= ((EXTAL_IN_Hz/4)-4) && freq <= (5+(EXTAL_IN_Hz/4)))	 REPLACE(CMOD,3,1,5);//ʹ��ϵͳʱ��4��Ƶ��ΪPCA��������������ʱ��
													else if(freq >= ((EXTAL_IN_Hz/6)-4) && freq <= (5+(EXTAL_IN_Hz/6)))	 REPLACE(CMOD,3,1,6);//ʹ��ϵͳʱ��6��Ƶ��ΪPCA��������������ʱ��
															 else if(freq >= ((EXTAL_IN_Hz/8)-4) && freq <= (5+(EXTAL_IN_Hz/8)))	 REPLACE(CMOD,3,1,7);//ʹ��ϵͳʱ��8��Ƶ��ΪPCA��������������ʱ��
																		else if(freq >= ((EXTAL_IN_Hz/12)-4) && freq <= (5+(EXTAL_IN_Hz/12))) REPLACE(CMOD,3,1,0);//ʹ��ϵͳʱ��12��Ƶ��ΪPCA��������������ʱ��
																				 else
																				 {
																					 divide_factor=EXTAL_IN_Hz/freq;//�����Ƶϵ��
																					 if(divide_factor > 0xffff) divide_factor = 0xffff;//���÷�Ƶϵ���޶�
																					 divide_factor = 0xffff-divide_factor;//׼������T0��ʱ����ֵ
																					 
																					 REPLACE(CMOD,3,1,2);//ʹ�ö�ʱ��0�������ΪPCA��������������ʱ��
																					 BIT_SET(AUXR,7);//T0ʱ�ӹ�����1Tģʽ��
																					 REPLACE(TMOD,3,0,0);//T0����16λ�Զ���װ��ʱ��
																					 TL0 = divide_factor;//��Ƶϵ��
																					 TH0 = divide_factor >> 8;//��Ƶϵ��
																					 TF0 = 0;//���T0�����־
																					 TR0 = 1;//����T0��ʱʱ��
																				 }
				}
			}//��Ƶ������Ϊ��0����Ƶ��Ϊ��һ�γ�ʼ����Ƶ�ʻ��ϵ縴λĬ��Ƶ��EXTAL_IN_Hz/12
	set_vector_handler(CCP_VECTORn , PCA_IRQHandler);//��PCA�жϵķ������趨ΪPCA_IRQHandler()
	BIT_SET(CMOD,0);//����PCA��������ж�
	CR = 1;
	EA = 1;
}

/*!
 *	@brief		��ȡ�ź�ʱ�䳤������
 *	@param		CCPn						CCPģ���ѡ��
							SIGNAL_FEATURE	�ź�ʱ������
 *	@warning	
 *	@sampleusage:	CCP_input_PULSE_WIDTH(CCP0,POSITIVE_PULSE_WIDTH);//��ȡCCP0�����źŵ�������
 */

uint32 data CCP0_PULSE0_WIDTH = 0 , CCP0_PULSE1_WIDTH = 0,
			      CCP1_PULSE0_WIDTH = 0 , CCP1_PULSE1_WIDTH = 0,
			      CCP2_PULSE0_WIDTH = 0 , CCP2_PULSE1_WIDTH = 0;

uint32 CCP_input_PULSE_WIDTH(CCPn_e CCPn ,  SIGNAL_FEATURE_e SIGNAL_FEATURE)//��ȡ�ź�ʱ�䳤������
{
	if(CCPn == CCP0)
	{
		if(ACQUIRE(CCAPM0,5,4)==3)//�����ش���
		{
			if(SIGNAL_FEATURE == POSITIVE_PULSE_WIDTH) return CCP0_PULSE1_WIDTH;//������
			else if(SIGNAL_FEATURE == NEGATIVE_PULSE_WIDTH)	return CCP0_PULSE0_WIDTH;//������
					 else if(SIGNAL_FEATURE == CYCLE_LENGTH)	return CCP0_PULSE1_WIDTH + CCP0_PULSE0_WIDTH;//����
		}
		else//�������ػ��½��ش���
		{
			if(SIGNAL_FEATURE == CYCLE_LENGTH)	return CCP0_PULSE0_WIDTH;//����
			else return 0;//�ô�����ʽ���ܲ�����ʱ������
		}
	}
	else if(CCPn == CCP1)
			 {
				 if(ACQUIRE(CCAPM1,5,4)==3)//�����ش���
				 {
					 if(SIGNAL_FEATURE == POSITIVE_PULSE_WIDTH) return CCP1_PULSE1_WIDTH;//������
					 else if(SIGNAL_FEATURE == NEGATIVE_PULSE_WIDTH)	return CCP1_PULSE0_WIDTH;//������
								else if(SIGNAL_FEATURE == CYCLE_LENGTH)	return CCP1_PULSE1_WIDTH + CCP1_PULSE0_WIDTH;//����
				 }
				 else//�������ػ��½��ش���
				 {
					 if(SIGNAL_FEATURE == CYCLE_LENGTH)	return CCP1_PULSE0_WIDTH;//����
					 else return 0;//�ô�����ʽ���ܲ�����ʱ������
				 }
			 }
			 else if(CCPn == CCP2)
						{
							if(ACQUIRE(CCAPM2,5,4)==3)//�����ش���
							{
								if(SIGNAL_FEATURE == POSITIVE_PULSE_WIDTH) return CCP2_PULSE1_WIDTH;//������
								else if(SIGNAL_FEATURE == NEGATIVE_PULSE_WIDTH)	return CCP2_PULSE0_WIDTH;//������
										 else if(SIGNAL_FEATURE == CYCLE_LENGTH)	return CCP2_PULSE1_WIDTH + CCP2_PULSE0_WIDTH;//����
							}
							else//�������ػ��½��ش���
							{
								if(SIGNAL_FEATURE == CYCLE_LENGTH)	return CCP2_PULSE0_WIDTH;//����
								else return 0;//�ô�����ʽ���ܲ�����ʱ������
							}
						}
	return 0;////CCPģ������ô���
}

/*!
 *	@brief		CCP�жϺ���
 *	@param		
 *	@warning	CCP�����ж϶�����룬���ÿ�ν����ж϶���Ҫ�ж������жϵ�ԭ��
 *	@sampleusage:	
 */

uint16 data CCP0_LAST_STIGGER_MODE_TIME = 0 , CCAP0_LAST_DATA = 0 , CCAP0_NOW_DATA = 0,
			      CCP1_LAST_STIGGER_MODE_TIME = 0 , CCAP1_LAST_DATA = 0 , CCAP1_NOW_DATA = 0,
			      CCP2_LAST_STIGGER_MODE_TIME = 0 , CCAP2_LAST_DATA = 0 , CCAP2_NOW_DATA = 0;

void	PCA_IRQHandler (void)
{
	if(CF)//��ʱ������ж�
	{
		CF = 0;
		CCP0_LAST_STIGGER_MODE_TIME++;
		CCP1_LAST_STIGGER_MODE_TIME++;
		CCP2_LAST_STIGGER_MODE_TIME++;
	}
	
	if(CCF0 && (BIT_GET(CCAPM0,1)==0) && (BIT_GET(CCAPM0,3)==0))//CCP0����ģʽ��׽�ж�
	{
		if(ACQUIRE(CCAPM0,5,4)==3)//�����ش���
		{
			if(gpio_get(CCP_0))//��¼������Ϊ������
			{
				CCF0 = 0;
				CCAP0_LAST_DATA = CCAP0_NOW_DATA;
				((uint8 *) & CCAP0_NOW_DATA)[0] = CCAP0H;
				((uint8 *) & CCAP0_NOW_DATA)[1] = CCAP0L;
				if(CCP0_LAST_STIGGER_MODE_TIME==0)
				{
					CCP0_PULSE0_WIDTH = CCAP0_NOW_DATA - CCAP0_LAST_DATA;
					CCP0_LAST_STIGGER_MODE_TIME = 0;
				}
				else
				{
					CCP0_PULSE0_WIDTH = (--CCP0_LAST_STIGGER_MODE_TIME)*0x10000+(CCAP0_NOW_DATA+0x10000-CCAP0_LAST_DATA);
					CCP0_LAST_STIGGER_MODE_TIME = 0;
				}
			}
			else//��¼������Ϊ������
			{
				CCF0 = 0;
				CCAP0_LAST_DATA = CCAP0_NOW_DATA;
				((uint8 *) & CCAP0_NOW_DATA)[0] = CCAP0H;
				((uint8 *) & CCAP0_NOW_DATA)[1] = CCAP0L;
				if(CCP0_LAST_STIGGER_MODE_TIME==0)
				{
					CCP0_PULSE1_WIDTH = CCAP0_NOW_DATA - CCAP0_LAST_DATA;
					CCP0_LAST_STIGGER_MODE_TIME = 0;
				}
				else
				{
					CCP0_PULSE1_WIDTH = (--CCP0_LAST_STIGGER_MODE_TIME)*0x10000+(CCAP0_NOW_DATA+0x10000-CCAP0_LAST_DATA);
					CCP0_LAST_STIGGER_MODE_TIME = 0;
				}
			}
		}
		else//�������ػ��½��ش���
		{
			CCF0 = 0;
			CCAP0_LAST_DATA = CCAP0_NOW_DATA;
			((uint8 *) & CCAP0_NOW_DATA)[0] = CCAP0H;
			((uint8 *) & CCAP0_NOW_DATA)[1] = CCAP0L;
			if(CCP0_LAST_STIGGER_MODE_TIME==0)
			{
				CCP0_PULSE0_WIDTH = CCAP0_NOW_DATA - CCAP0_LAST_DATA;
				CCP0_LAST_STIGGER_MODE_TIME = 0;
			}
			else
			{
				CCP0_PULSE0_WIDTH = (--CCP0_LAST_STIGGER_MODE_TIME)*0x10000+(CCAP0_NOW_DATA+0x10000-CCAP0_LAST_DATA);
				CCP0_LAST_STIGGER_MODE_TIME = 0;
			}
		}
	}
	
	if(CCF1 && (BIT_GET(CCAPM1,1)==0) && (BIT_GET(CCAPM1,3)==0))//CCP1����ģʽ��׽�ж�
	{
		if(ACQUIRE(CCAPM1,5,4)==3)//�����ش���
		{
			if(gpio_get(CCP_1))//��¼������Ϊ������
			{
				CCF1 = 0;
				CCAP1_LAST_DATA = CCAP1_NOW_DATA;
				((uint8 *) & CCAP1_NOW_DATA)[0] = CCAP1H;
				((uint8 *) & CCAP1_NOW_DATA)[1] = CCAP1L;
				if(CCP1_LAST_STIGGER_MODE_TIME==0)
				{
					CCP1_PULSE0_WIDTH = CCAP1_NOW_DATA - CCAP1_LAST_DATA;
					CCP1_LAST_STIGGER_MODE_TIME = 0;
				}
				else
				{
					CCP1_PULSE0_WIDTH = (--CCP1_LAST_STIGGER_MODE_TIME)*0x10000+(CCAP1_NOW_DATA+0x10000-CCAP1_LAST_DATA);
					CCP1_LAST_STIGGER_MODE_TIME = 0;
				}
			}
			else//��¼������Ϊ������
			{
				CCF1 = 0;
				CCAP1_LAST_DATA = CCAP1_NOW_DATA;
				((uint8 *) & CCAP1_NOW_DATA)[0] = CCAP1H;
				((uint8 *) & CCAP1_NOW_DATA)[1] = CCAP1L;
				if(CCP1_LAST_STIGGER_MODE_TIME==0)
				{
					CCP1_PULSE1_WIDTH = CCAP1_NOW_DATA - CCAP1_LAST_DATA;
					CCP1_LAST_STIGGER_MODE_TIME = 0;
				}
				else
				{
					CCP1_PULSE1_WIDTH = (--CCP1_LAST_STIGGER_MODE_TIME)*0x10000+(CCAP1_NOW_DATA+0x10000-CCAP1_LAST_DATA);
					CCP1_LAST_STIGGER_MODE_TIME = 0;
				}
			}
		}
		else//�������ػ��½��ش���
		{
			CCF1 = 0;
			CCAP1_LAST_DATA = CCAP1_NOW_DATA;
			((uint8 *) & CCAP1_NOW_DATA)[0] = CCAP1H;
			((uint8 *) & CCAP1_NOW_DATA)[1] = CCAP1L;
			if(CCP1_LAST_STIGGER_MODE_TIME==0)
			{
				CCP1_PULSE0_WIDTH = CCAP1_NOW_DATA - CCAP1_LAST_DATA;
				CCP1_LAST_STIGGER_MODE_TIME = 0;
			}
			else
			{
				CCP1_PULSE0_WIDTH = (--CCP1_LAST_STIGGER_MODE_TIME)*0x10000+(CCAP1_NOW_DATA+0x10000-CCAP1_LAST_DATA);
				CCP1_LAST_STIGGER_MODE_TIME = 0;
			}
		}
	}
	
	if(CCF2 && (BIT_GET(CCAPM2,1)==0) && (BIT_GET(CCAPM2,3)==0))//CCP2����ģʽ��׽�ж�
	{
		if(ACQUIRE(CCAPM2,5,4)==3)//�����ش���
		{
			if(gpio_get(CCP_2))//��¼������Ϊ������
			{
				CCF2 = 0;
				CCAP2_LAST_DATA = CCAP2_NOW_DATA;
				((uint8 *) & CCAP2_NOW_DATA)[0] = CCAP2H;
				((uint8 *) & CCAP2_NOW_DATA)[1] = CCAP2L;
				if(CCP2_LAST_STIGGER_MODE_TIME==0)
				{
					CCP2_PULSE0_WIDTH = CCAP2_NOW_DATA - CCAP2_LAST_DATA;
					CCP2_LAST_STIGGER_MODE_TIME = 0;
				}
				else
				{
					CCP2_PULSE0_WIDTH = (--CCP2_LAST_STIGGER_MODE_TIME)*0x10000+(CCAP2_NOW_DATA+0x10000-CCAP2_LAST_DATA);
					CCP2_LAST_STIGGER_MODE_TIME = 0;
				}
			}
			else//��¼������Ϊ������
			{
				CCF2 = 0;
				CCAP2_LAST_DATA = CCAP2_NOW_DATA;
				((uint8 *) & CCAP2_NOW_DATA)[0] = CCAP2H;
				((uint8 *) & CCAP2_NOW_DATA)[1] = CCAP2L;
				if(CCP2_LAST_STIGGER_MODE_TIME==0)
				{
					CCP2_PULSE1_WIDTH = CCAP2_NOW_DATA - CCAP2_LAST_DATA;
					CCP2_LAST_STIGGER_MODE_TIME = 0;
				}
				else
				{
					CCP2_PULSE1_WIDTH = (--CCP2_LAST_STIGGER_MODE_TIME)*0x10000+(CCAP2_NOW_DATA+0x10000-CCAP2_LAST_DATA);
					CCP2_LAST_STIGGER_MODE_TIME = 0;
				}
			}
		}
		else//�������ػ��½��ش���
		{
			CCF2 = 0;
			CCAP2_LAST_DATA = CCAP2_NOW_DATA;
			((uint8 *) & CCAP2_NOW_DATA)[0] = CCAP2H;
			((uint8 *) & CCAP2_NOW_DATA)[1] = CCAP2L;
			if(CCP2_LAST_STIGGER_MODE_TIME==0)
			{
				CCP2_PULSE0_WIDTH = CCAP2_NOW_DATA - CCAP2_LAST_DATA;
				CCP2_LAST_STIGGER_MODE_TIME = 0;
			}
			else
			{
				CCP2_PULSE0_WIDTH = (--CCP2_LAST_STIGGER_MODE_TIME)*0x10000+(CCAP2_NOW_DATA+0x10000-CCAP2_LAST_DATA);
				CCP2_LAST_STIGGER_MODE_TIME = 0;
			}
		}
	}
}