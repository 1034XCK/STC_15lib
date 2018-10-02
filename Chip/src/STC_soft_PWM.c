#include "common.h"
#include "STC_soft_PWM.h"
#include "STC_gpio.h"
#include "STC_port.h"
#include "STC_PIT.h"
#include "STC_interrupt.h"

/*!
 *	@brief		���ʵ��PWM��ʼ��
 *	@param		use_Tn	ʹ���ĸ���ʱ����Ϊ���PWM��ʱ��
							pxn			��PWM�ź�������ĸ�����
							freq		PWM�źų�ʼƵ��
							duty		PWM�źų�ʼռ�ձ�
 *	@warning	���PWM�������IO�ڹ���ģʽ����Ϊ��������ģʽ���ϵ��ʼ��Ϊ׼˫���
              STC15F2K60S2û��T3��T4�������뿴�ֲ�
 *	@sampleusage:	soft_pwm_init(PWM0_T0 , p11 , 50 , 50);//ʹ��T0��ʱ����Ϊ���PWM0��ʱ�ӣ�����˿�Ϊp11��Ƶ��50Hz��ռ�ձ�Ϊ50/PWM0_PRECISON
 */
 
pxn_e		PWM0_out , PWM1_out , PWM2_out , PWM3_out , PWM4_out;
uint16 data	soft_pwm0_duty = 0 , soft_pwm1_duty = 0 , soft_pwm2_duty = 0,
				    soft_pwm3_duty = 0 , soft_pwm4_duty = 0,
				    Regular0_times_g = 0 , Regular1_times_g = 0 , Regular2_times_g = 0,
				    Regular3_times_g = 0 , Regular4_times_g = 0;

void soft_pwm_init(Use_Tn_e use_Tn , pxn_e pxn , uint32 freq , uint16 duty)
{
	uint16 Regular_times = 0;//��ʱ����
	
	if(freq > EXTAL_IN_Hz/(65536L*(1+ACQUIRE(CLK_DIV,2,0))))//��ʱ����������Ҫ�����ڴ�������Ƶ�ʵ��ź����ڣ�������Ʒ�����һ�ζ�ʱ���������
	{
		if(use_Tn == PWM0_T0)//��ʹ��PWM0
		{
			if(duty > PWM0_PRECISON)	duty = PWM0_PRECISON;
			PWM0_out = pxn;//ȷ��pwm�������
			Regular0_times_g = EXTAL_IN_Hz/(freq*(1+ACQUIRE(CLK_DIV,2,0)));//��������Ƶ�ʼ��㶨ʱ����ʱ����
			soft_pwm0_duty = (uint32)duty*Regular0_times_g/PWM0_PRECISON;//ȷ����ռ�ձȶ�ʱ����ʱ��ȫ�ֱ�����
			pit_init(T0,Regular_times);//����T0��ʱ��
			set_vector_handler(TIMER0_VECTORn , PWM0_ONE_TIME_cycle);//����ʱ��T0�жϵķ������趨ΪPWM0_ONE_TIME_cycle()
			Whether_IRQ(TIMER0_VECTORn , IRQ_enable);//ʹ�ܶ�ʱ��T0�ж�
		}
		else if(use_Tn == PWM1_T1)//��ʹ��PWM1
				 {
					 if(duty > PWM1_PRECISON)	duty = PWM1_PRECISON;
					 PWM1_out = pxn;//ȷ��pwm�������
					 Regular1_times_g = EXTAL_IN_Hz/(freq*(1+ACQUIRE(CLK_DIV,2,0)));//��������Ƶ�ʼ��㶨ʱ����ʱ����
					 soft_pwm1_duty = (uint32)duty*Regular1_times_g/PWM1_PRECISON;//ȷ����ռ�ձȶ�ʱ����ʱ��ȫ�ֱ�����
					 pit_init(T1,Regular_times);//����T1��ʱ��
					 set_vector_handler(TIMER1_VECTORn , PWM1_ONE_TIME_cycle);//����ʱ��T1�жϵķ������趨ΪPWM1_ONE_TIME_cycle()
					 Whether_IRQ(TIMER1_VECTORn , IRQ_enable);//ʹ�ܶ�ʱ��T1�ж�
				 }
				 else if(use_Tn == PWM2_T2)//��ʹ��PWM2
							{
								if(duty > PWM2_PRECISON)	duty = PWM2_PRECISON;
								PWM2_out = pxn;//ȷ��pwm�������
								Regular2_times_g = EXTAL_IN_Hz/(freq*(1+ACQUIRE(CLK_DIV,2,0)));//��������Ƶ�ʼ��㶨ʱ����ʱ����
								soft_pwm2_duty = (uint32)duty*Regular2_times_g/PWM2_PRECISON;//ȷ����ռ�ձȶ�ʱ����ʱ��ȫ�ֱ������
								pit_init(T2,Regular_times);//����T2��ʱ��
								set_vector_handler(TIMER2_VECTORn , PWM2_ONE_TIME_cycle);//����ʱ��T2�жϵķ������趨ΪPWM2_ONE_TIME_cycle()
								Whether_IRQ(TIMER2_VECTORn , IRQ_enable);//ʹ�ܶ�ʱ��T2�ж�
							}
							else if(use_Tn == PWM3_T3)//��ʹ��PWM3
									 {
										 if(duty > PWM3_PRECISON)	duty = PWM3_PRECISON;
										 PWM3_out = pxn;//ȷ��pwm�������
										 Regular3_times_g = EXTAL_IN_Hz/(freq*(1+ACQUIRE(CLK_DIV,2,0)));//��������Ƶ�ʼ��㶨ʱ����ʱ����
										 soft_pwm3_duty = (uint32)duty*Regular3_times_g/PWM3_PRECISON;//ȷ����ռ�ձȶ�ʱ����ʱ��ȫ�ֱ�����
										 pit_init(T3,Regular_times);//����T3��ʱ��
										 set_vector_handler(TIMER3_VECTORn , PWM3_ONE_TIME_cycle);//����ʱ��T3�жϵķ������趨ΪPWM3_ONE_TIME_cycle()
										 Whether_IRQ(TIMER3_VECTORn , IRQ_enable);//ʹ�ܶ�ʱ��T3�ж�
									 }
									 else if(use_Tn == PWM4_T4)//��ʹ��PWM4
												{
													if(duty > PWM4_PRECISON)	duty = PWM4_PRECISON;
													PWM4_out = pxn;//ȷ��pwm�������
													Regular4_times_g = EXTAL_IN_Hz/(freq*(1+ACQUIRE(CLK_DIV,2,0)));//��������Ƶ�ʼ��㶨ʱ����ʱ����
													soft_pwm4_duty = (uint32)duty*Regular4_times_g/PWM4_PRECISON;//ȷ����ռ�ձȶ�ʱ����ʱ��ȫ�ֱ�����
													pit_init(T4,Regular_times);//����T4��ʱ��
													set_vector_handler(TIMER4_VECTORn , PWM4_ONE_TIME_cycle);//����ʱ��T4�жϵķ������趨ΪPWM4_ONE_TIME_cycle()
													Whether_IRQ(TIMER4_VECTORn , IRQ_enable);//ʹ�ܶ�ʱ��T4�ж�
												}
	}
	else //��ʱ����������Ҫ������С������Ƶ�ʵ��ź����ڣ�������ƽ����õ���ʱ���ۼӷ�ʽ���
	{
		if(use_Tn == PWM0_T0)//��ʹ��PWM0
		{
			PWM0_out = pxn;//ȷ��pwm�������
			soft_pwm0_duty = duty;//ȷ��ռ�ձȣ�ȫ�ֱ�����
			Regular_times = EXTAL_IN_Hz/((1+ACQUIRE(CLK_DIV,2,0))*freq*PWM0_PRECISON);//��������Ƶ�ʼ����ȼ��㶨ʱ����ʱ����
			pit_init(T0,Regular_times);//����T0��ʱ��
			set_vector_handler(TIMER0_VECTORn , PWM0_UNIT_TIME_ACC);//����ʱ��T0�жϵķ������趨ΪPWM0_UNIT_TIME_ACC()
			Whether_IRQ(TIMER0_VECTORn , IRQ_enable);//ʹ�ܶ�ʱ��T0�ж�
		}
		else if(use_Tn == PWM1_T1)//��ʹ��PWM1
				 {
					 PWM1_out = pxn;//ȷ��pwm�������
					 soft_pwm1_duty = duty;//ȷ��ռ�ձȣ�ȫ�ֱ�����
					 Regular_times = EXTAL_IN_Hz/((1+ACQUIRE(CLK_DIV,2,0))*freq*PWM1_PRECISON);//��������Ƶ�ʼ����ȼ��㶨ʱ����ʱ����
					 pit_init(T1,Regular_times);//����T1��ʱ��
					 set_vector_handler(TIMER1_VECTORn , PWM1_UNIT_TIME_ACC);//����ʱ��T1�жϵķ������趨ΪPWM1_UNIT_TIME_ACC()
					 Whether_IRQ(TIMER1_VECTORn , IRQ_enable);//ʹ�ܶ�ʱ��T1�ж�
				 }
				 else if(use_Tn == PWM2_T2)//��ʹ��PWM2
							{
								PWM2_out = pxn;//ȷ��pwm�������
								soft_pwm2_duty = duty;//ȷ��ռ�ձȣ�ȫ�ֱ�����
								Regular_times = EXTAL_IN_Hz/((1+ACQUIRE(CLK_DIV,2,0))*freq*PWM2_PRECISON);//��������Ƶ�ʼ����ȼ��㶨ʱ����ʱ����
								pit_init(T2,Regular_times);//����T2��ʱ��
								set_vector_handler(TIMER2_VECTORn , PWM2_UNIT_TIME_ACC);//����ʱ��T2�жϵķ������趨ΪPWM2_UNIT_TIME_ACC()
								Whether_IRQ(TIMER2_VECTORn , IRQ_enable);//ʹ�ܶ�ʱ��T2�ж�
							}
							else if(use_Tn == PWM3_T3)//��ʹ��PWM3
									 {
										 PWM3_out = pxn;//ȷ��pwm�������
										 soft_pwm3_duty = duty;//ȷ��ռ�ձȣ�ȫ�ֱ�����
										 Regular_times = EXTAL_IN_Hz/((1+ACQUIRE(CLK_DIV,2,0))*freq*PWM3_PRECISON);//��������Ƶ�ʼ����ȼ��㶨ʱ����ʱ����
										 pit_init(T3,Regular_times);//����T3��ʱ��
										 set_vector_handler(TIMER3_VECTORn , PWM3_UNIT_TIME_ACC);//����ʱ��T3�жϵķ������趨ΪPWM3_UNIT_TIME_ACC()
										 Whether_IRQ(TIMER3_VECTORn , IRQ_enable);//ʹ�ܶ�ʱ��T3�ж�
									 }
									 else if(use_Tn == PWM4_T4)//��ʹ��PWM4
												{
													PWM4_out = pxn;//ȷ��pwm�������
													soft_pwm4_duty = duty;//ȷ��ռ�ձȣ�ȫ�ֱ�����
													Regular_times = EXTAL_IN_Hz/((1+ACQUIRE(CLK_DIV,2,0))*freq*PWM4_PRECISON);//��������Ƶ�ʼ����ȼ��㶨ʱ����ʱ����
													pit_init(T4,Regular_times);//����T4��ʱ��
													set_vector_handler(TIMER4_VECTORn , PWM4_UNIT_TIME_ACC);//����ʱ��T4�жϵķ������趨ΪPWM4_UNIT_TIME_ACC()
													Whether_IRQ(TIMER4_VECTORn , IRQ_enable);//ʹ�ܶ�ʱ��T4�ж�
												}
	}
}

/*!
 *	@brief		��ʱ���жϷ�����Ⱥ
							��ʱ����������Ҫ�����ڴ�������Ƶ�ʵ��ź����ڣ�������Ʒ�����һ�ζ�ʱ���������
 *	@param		
 *	@warning	���ɵ���
 *	@sampleusage:	
 */

bit PWM0_STATE = 0,
		PWM1_STATE = 0,
		PWM2_STATE = 0,
		PWM3_STATE = 0,
		PWM4_STATE = 0;

void PWM0_ONE_TIME_cycle(void)
{
	PWM0_STATE = ~PWM0_STATE;
	if(soft_pwm0_duty < 410) gpio_set(PWM0_out , 0);
	else if(410 > Regular0_times_g - soft_pwm0_duty)	gpio_set(PWM0_out , 1);
			 else if(PWM0_STATE)
						{
							gpio_set(PWM0_out , 0);
							pit_change(T0,soft_pwm0_duty);
						}
						else
						{
							gpio_set(PWM0_out , 1);
							pit_change(T0,Regular0_times_g - soft_pwm0_duty);
						}
}

void PWM1_ONE_TIME_cycle(void)
{
	PWM1_STATE = ~PWM1_STATE;
	if(soft_pwm1_duty < 410) gpio_set(PWM1_out , 0);
	else if(410 > Regular1_times_g - soft_pwm1_duty)	gpio_set(PWM1_out , 1);
			 else if(PWM1_STATE)
						{
							gpio_set(PWM1_out , 0);
							pit_change(T1,soft_pwm1_duty);
						}
						else
						{
							gpio_set(PWM1_out , 1);
							pit_change(T1,Regular1_times_g - soft_pwm1_duty);
						}
}

void PWM2_ONE_TIME_cycle(void)
{
	PWM2_STATE = ~PWM2_STATE;
	if(soft_pwm2_duty < 410) gpio_set(PWM2_out , 0);
	else if(410 > Regular2_times_g - soft_pwm2_duty)	gpio_set(PWM2_out , 1);
			 else if(PWM2_STATE)
						{
							gpio_set(PWM2_out , 0);
							pit_change(T2,soft_pwm2_duty);
						}
						else
						{
							gpio_set(PWM2_out , 1);
							pit_change(T2,Regular2_times_g - soft_pwm2_duty);
						}
}

void PWM3_ONE_TIME_cycle(void)
{
	PWM3_STATE = ~PWM3_STATE;
	if(soft_pwm3_duty < 410) gpio_set(PWM3_out , 0);
	else if(410 > Regular3_times_g - soft_pwm3_duty)	gpio_set(PWM3_out , 1);
			 else if(PWM3_STATE)
						{
							gpio_set(PWM3_out , 0);
							pit_change(T3,soft_pwm3_duty);
						}
						else
						{
							gpio_set(PWM3_out , 1);
							pit_change(T3,Regular3_times_g - soft_pwm3_duty);
						}
}

void PWM4_ONE_TIME_cycle(void)
{
	PWM4_STATE = ~PWM4_STATE;
	if(soft_pwm4_duty < 410) gpio_set(PWM4_out , 0);
	else if(410 > Regular4_times_g - soft_pwm4_duty)	gpio_set(PWM4_out , 1);
			 else if(PWM4_STATE)
						{
							gpio_set(PWM4_out , 0);
							pit_change(T4,soft_pwm4_duty);
						}
						else
						{
							gpio_set(PWM4_out , 1);
							pit_change(T4,Regular4_times_g - soft_pwm4_duty);
						}
}

/*!
 *	@brief		��ʱ���жϷ�����Ⱥ
							��ʱ����������Ҫ������С������Ƶ�ʵ��ź����ڣ�������ƽ����õ���ʱ���ۼӷ�ʽ���
 *	@param		
 *	@warning	���ɵ���
 *	@sampleusage:	
 */

uint16 data PWM0_UNIT_TIME_NUM=0 , PWM1_UNIT_TIME_NUM=0 , PWM2_UNIT_TIME_NUM=0,
			      PWM3_UNIT_TIME_NUM=0 , PWM4_UNIT_TIME_NUM=0;

void PWM0_UNIT_TIME_ACC(void)
{
	PWM0_UNIT_TIME_NUM++;
	if(PWM0_UNIT_TIME_NUM >  PWM0_PRECISON)	PWM0_UNIT_TIME_NUM = 0;
	if(PWM0_UNIT_TIME_NUM >= soft_pwm0_duty)	gpio_set(PWM0_out , 0);
	else gpio_set(PWM0_out , 1);
}

void PWM1_UNIT_TIME_ACC(void)
{
	PWM1_UNIT_TIME_NUM++;
	if(PWM1_UNIT_TIME_NUM >  PWM1_PRECISON)	PWM1_UNIT_TIME_NUM = 0;
	if(PWM1_UNIT_TIME_NUM >= soft_pwm1_duty)	gpio_set(PWM1_out , 0);
	else gpio_set(PWM1_out , 1);
}

void PWM2_UNIT_TIME_ACC(void)
{
	PWM2_UNIT_TIME_NUM++;
	if(PWM2_UNIT_TIME_NUM >  PWM2_PRECISON)	PWM2_UNIT_TIME_NUM = 0;
	if(PWM2_UNIT_TIME_NUM >= soft_pwm2_duty)	gpio_set(PWM2_out , 0);
	else gpio_set(PWM2_out , 1);
}

void PWM3_UNIT_TIME_ACC(void)
{
	PWM3_UNIT_TIME_NUM++;
	if(PWM3_UNIT_TIME_NUM >  PWM3_PRECISON)	PWM3_UNIT_TIME_NUM = 0;
	if(PWM3_UNIT_TIME_NUM >= soft_pwm3_duty)	gpio_set(PWM3_out , 0);
	else gpio_set(PWM3_out , 1);
}

void PWM4_UNIT_TIME_ACC(void)
{
	PWM4_UNIT_TIME_NUM++;
	if(PWM4_UNIT_TIME_NUM >  PWM4_PRECISON)	PWM4_UNIT_TIME_NUM = 0;
	if(PWM4_UNIT_TIME_NUM >= soft_pwm4_duty)	gpio_set(PWM4_out , 0);
	else gpio_set(PWM4_out , 1);
}