#include "common.h"
#include "STC_soft_PWM.h"
#include "STC_gpio.h"
#include "STC_port.h"
#include "STC_PIT.h"
#include "STC_interrupt.h"

/*!
 *	@brief		Èí¼þÊµÏÖPWM³õÊ¼»¯
 *	@param		use_Tn	Ê¹ÓÃÄÄ¸ö¶¨Ê±Æ÷×÷ÎªÈí¼þPWMµÄÊ±ÖÓ
							pxn			½«PWMÐÅºÅÊä³öÖÁÄÄ¸öÒý½Å
							freq		PWMÐÅºÅ³õÊ¼ÆµÂÊ
							duty		PWMÐÅºÅ³õÊ¼Õ¼¿Õ±È
 *	@warning	Èí¼þPWMÊä³öËùÔÚIO¿Ú¹¤×÷Ä£Ê½²»ÄÜÎª¸¡¿ÕÊäÈëÄ£Ê½£¬ÉÏµç³õÊ¼»¯Îª×¼Ë«Ïò¿Ú
              STC15F2K60S2Ã»ÓÐT3ºÍT4£¬ÏêÇéÇë¿´ÊÖ²á
 *	@sampleusage:	soft_pwm_init(PWM0_T0 , p11 , 50 , 50);//Ê¹ÓÃT0¶¨Ê±Æ÷×÷ÎªÈí¼þPWM0µÄÊ±ÖÓ£¬Êä³ö¶Ë¿ÚÎªp11£¬ÆµÂÊ50Hz£¬Õ¼¿Õ±ÈÎª50/PWM0_PRECISON
 */
 
pxn_e		PWM0_out , PWM1_out , PWM2_out , PWM3_out , PWM4_out;
uint16 data	soft_pwm0_duty = 0 , soft_pwm1_duty = 0 , soft_pwm2_duty = 0,
				    soft_pwm3_duty = 0 , soft_pwm4_duty = 0,
				    Regular0_times_g = 0 , Regular1_times_g = 0 , Regular2_times_g = 0,
				    Regular3_times_g = 0 , Regular4_times_g = 0;

void soft_pwm_init(Use_Tn_e use_Tn , pxn_e pxn , uint32 freq , uint16 duty)
{
	uint16 Regular_times = 0;//¶¨Ê±´ÎÊý
	
	if(freq > EXTAL_IN_Hz/(65536L*(1+ACQUIRE(CLK_DIV,2,0))))//¶¨Ê±Æ÷¼ÆÂúËùÐèÒªµÄÖÜÆÚ´óÓÚÉèÖÃÆµÂÊµÄÐÅºÅÖÜÆÚ£¬Âö¿íµ÷ÖÆ·½¿ÉÔÚÒ»´Î¶¨Ê±ÖÜÆÚÄÚÍê³É
	{
		if(use_Tn == PWM0_T0)//ÈôÊ¹ÓÃPWM0
		{
			if(duty > PWM0_PRECISON)	duty = PWM0_PRECISON;
			PWM0_out = pxn;//È·¶¨pwmÊä³öÒý½Å
			Regular0_times_g = EXTAL_IN_Hz/(freq*(1+ACQUIRE(CLK_DIV,2,0)));//¸ù¾ÝÉèÖÃÆµÂÊ¼ÆËã¶¨Ê±Æ÷×ßÊ±³¤¶È
			soft_pwm0_duty = (uint32)duty*Regular0_times_g/PWM0_PRECISON;//È·¶¨ÕýÕ¼¿Õ±È¶¨Ê±Æ÷×ßÊ±£¨È«¾Ö±äÁ¿£©
			pit_init(T0,Regular_times);//ÆôÓÃT0¶¨Ê±Æ÷
			set_vector_handler(TIMER0_VECTORn , PWM0_ONE_TIME_cycle);//½«¶¨Ê±Æ÷T0ÖÐ¶ÏµÄ·þÎñº¯ÊýÉè¶¨ÎªPWM0_ONE_TIME_cycle()
			Whether_IRQ(TIMER0_VECTORn , IRQ_enable);//Ê¹ÄÜ¶¨Ê±Æ÷T0ÖÐ¶Ï
		}
		else if(use_Tn == PWM1_T1)//ÈôÊ¹ÓÃPWM1
				 {
					 if(duty > PWM1_PRECISON)	duty = PWM1_PRECISON;
					 PWM1_out = pxn;//È·¶¨pwmÊä³öÒý½Å
					 Regular1_times_g = EXTAL_IN_Hz/(freq*(1+ACQUIRE(CLK_DIV,2,0)));//¸ù¾ÝÉèÖÃÆµÂÊ¼ÆËã¶¨Ê±Æ÷×ßÊ±³¤¶È
					 soft_pwm1_duty = (uint32)duty*Regular1_times_g/PWM1_PRECISON;//È·¶¨ÕýÕ¼¿Õ±È¶¨Ê±Æ÷×ßÊ±£¨È«¾Ö±äÁ¿£©
					 pit_init(T1,Regular_times);//ÆôÓÃT1¶¨Ê±Æ÷
					 set_vector_handler(TIMER1_VECTORn , PWM1_ONE_TIME_cycle);//½«¶¨Ê±Æ÷T1ÖÐ¶ÏµÄ·þÎñº¯ÊýÉè¶¨ÎªPWM1_ONE_TIME_cycle()
					 Whether_IRQ(TIMER1_VECTORn , IRQ_enable);//Ê¹ÄÜ¶¨Ê±Æ÷T1ÖÐ¶Ï
				 }
				 else if(use_Tn == PWM2_T2)//ÈôÊ¹ÓÃPWM2
							{
								if(duty > PWM2_PRECISON)	duty = PWM2_PRECISON;
								PWM2_out = pxn;//È·¶¨pwmÊä³öÒý½Å
								Regular2_times_g = EXTAL_IN_Hz/(freq*(1+ACQUIRE(CLK_DIV,2,0)));//¸ù¾ÝÉèÖÃÆµÂÊ¼ÆËã¶¨Ê±Æ÷×ßÊ±³¤¶È
								soft_pwm2_duty = (uint32)duty*Regular2_times_g/PWM2_PRECISON;//È·¶¨ÕýÕ¼¿Õ±È¶¨Ê±Æ÷×ßÊ±£¨È«¾Ö±äÁ¿£©©
								pit_init(T2,Regular_times);//ÆôÓÃT2¶¨Ê±Æ÷
								set_vector_handler(TIMER2_VECTORn , PWM2_ONE_TIME_cycle);//½«¶¨Ê±Æ÷T2ÖÐ¶ÏµÄ·þÎñº¯ÊýÉè¶¨ÎªPWM2_ONE_TIME_cycle()
								Whether_IRQ(TIMER2_VECTORn , IRQ_enable);//Ê¹ÄÜ¶¨Ê±Æ÷T2ÖÐ¶Ï
							}
							else if(use_Tn == PWM3_T3)//ÈôÊ¹ÓÃPWM3
									 {
										 if(duty > PWM3_PRECISON)	duty = PWM3_PRECISON;
										 PWM3_out = pxn;//È·¶¨pwmÊä³öÒý½Å
										 Regular3_times_g = EXTAL_IN_Hz/(freq*(1+ACQUIRE(CLK_DIV,2,0)));//¸ù¾ÝÉèÖÃÆµÂÊ¼ÆËã¶¨Ê±Æ÷×ßÊ±³¤¶È
										 soft_pwm3_duty = (uint32)duty*Regular3_times_g/PWM3_PRECISON;//È·¶¨ÕýÕ¼¿Õ±È¶¨Ê±Æ÷×ßÊ±£¨È«¾Ö±äÁ¿£©
										 pit_init(T3,Regular_times);//ÆôÓÃT3¶¨Ê±Æ÷
										 set_vector_handler(TIMER3_VECTORn , PWM3_ONE_TIME_cycle);//½«¶¨Ê±Æ÷T3ÖÐ¶ÏµÄ·þÎñº¯ÊýÉè¶¨ÎªPWM3_ONE_TIME_cycle()
										 Whether_IRQ(TIMER3_VECTORn , IRQ_enable);//Ê¹ÄÜ¶¨Ê±Æ÷T3ÖÐ¶Ï
									 }
									 else if(use_Tn == PWM4_T4)//ÈôÊ¹ÓÃPWM4
												{
													if(duty > PWM4_PRECISON)	duty = PWM4_PRECISON;
													PWM4_out = pxn;//È·¶¨pwmÊä³öÒý½Å
													Regular4_times_g = EXTAL_IN_Hz/(freq*(1+ACQUIRE(CLK_DIV,2,0)));//¸ù¾ÝÉèÖÃÆµÂÊ¼ÆËã¶¨Ê±Æ÷×ßÊ±³¤¶È
													soft_pwm4_duty = (uint32)duty*Regular4_times_g/PWM4_PRECISON;//È·¶¨ÕýÕ¼¿Õ±È¶¨Ê±Æ÷×ßÊ±£¨È«¾Ö±äÁ¿£©
													pit_init(T4,Regular_times);//ÆôÓÃT4¶¨Ê±Æ÷
													set_vector_handler(TIMER4_VECTORn , PWM4_ONE_TIME_cycle);//½«¶¨Ê±Æ÷T4ÖÐ¶ÏµÄ·þÎñº¯ÊýÉè¶¨ÎªPWM4_ONE_TIME_cycle()
													Whether_IRQ(TIMER4_VECTORn , IRQ_enable);//Ê¹ÄÜ¶¨Ê±Æ÷T4ÖÐ¶Ï
												}
	}
	else //¶¨Ê±Æ÷¼ÆÂúËùÐèÒªµÄÖÜÆÚÐ¡ÓÚÉèÖÃÆµÂÊµÄÐÅºÅÖÜÆÚ£¬Âö¿íµ÷ÖÆ½«ÀûÓÃµ¥²½Ê±¼äÀÛ¼Ó·½Ê½Íê³É
	{
		if(use_Tn == PWM0_T0)//ÈôÊ¹ÓÃPWM0
		{
			PWM0_out = pxn;//È·¶¨pwmÊä³öÒý½Å
			soft_pwm0_duty = duty;//È·¶¨Õ¼¿Õ±È£¨È«¾Ö±äÁ¿£©
			Regular_times = EXTAL_IN_Hz/((1+ACQUIRE(CLK_DIV,2,0))*freq*PWM0_PRECISON);//¸ù¾ÝÉèÖÃÆµÂÊ¼°¾«¶È¼ÆËã¶¨Ê±Æ÷×ßÊ±³¤¶È
			pit_init(T0,Regular_times);//ÆôÓÃT0¶¨Ê±Æ÷
			set_vector_handler(TIMER0_VECTORn , PWM0_UNIT_TIME_ACC);//½«¶¨Ê±Æ÷T0ÖÐ¶ÏµÄ·þÎñº¯ÊýÉè¶¨ÎªPWM0_UNIT_TIME_ACC()
			Whether_IRQ(TIMER0_VECTORn , IRQ_enable);//Ê¹ÄÜ¶¨Ê±Æ÷T0ÖÐ¶Ï
		}
		else if(use_Tn == PWM1_T1)//ÈôÊ¹ÓÃPWM1
				 {
					 PWM1_out = pxn;//È·¶¨pwmÊä³öÒý½Å
					 soft_pwm1_duty = duty;//È·¶¨Õ¼¿Õ±È£¨È«¾Ö±äÁ¿£©
					 Regular_times = EXTAL_IN_Hz/((1+ACQUIRE(CLK_DIV,2,0))*freq*PWM1_PRECISON);//¸ù¾ÝÉèÖÃÆµÂÊ¼°¾«¶È¼ÆËã¶¨Ê±Æ÷×ßÊ±³¤¶È
					 pit_init(T1,Regular_times);//ÆôÓÃT1¶¨Ê±Æ÷
					 set_vector_handler(TIMER1_VECTORn , PWM1_UNIT_TIME_ACC);//½«¶¨Ê±Æ÷T1ÖÐ¶ÏµÄ·þÎñº¯ÊýÉè¶¨ÎªPWM1_UNIT_TIME_ACC()
					 Whether_IRQ(TIMER1_VECTORn , IRQ_enable);//Ê¹ÄÜ¶¨Ê±Æ÷T1ÖÐ¶Ï
				 }
				 else if(use_Tn == PWM2_T2)//ÈôÊ¹ÓÃPWM2
							{
								PWM2_out = pxn;//È·¶¨pwmÊä³öÒý½Å
								soft_pwm2_duty = duty;//È·¶¨Õ¼¿Õ±È£¨È«¾Ö±äÁ¿£©
								Regular_times = EXTAL_IN_Hz/((1+ACQUIRE(CLK_DIV,2,0))*freq*PWM2_PRECISON);//¸ù¾ÝÉèÖÃÆµÂÊ¼°¾«¶È¼ÆËã¶¨Ê±Æ÷×ßÊ±³¤¶È
								pit_init(T2,Regular_times);//ÆôÓÃT2¶¨Ê±Æ÷
								set_vector_handler(TIMER2_VECTORn , PWM2_UNIT_TIME_ACC);//½«¶¨Ê±Æ÷T2ÖÐ¶ÏµÄ·þÎñº¯ÊýÉè¶¨ÎªPWM2_UNIT_TIME_ACC()
								Whether_IRQ(TIMER2_VECTORn , IRQ_enable);//Ê¹ÄÜ¶¨Ê±Æ÷T2ÖÐ¶Ï
							}
							else if(use_Tn == PWM3_T3)//ÈôÊ¹ÓÃPWM3
									 {
										 PWM3_out = pxn;//È·¶¨pwmÊä³öÒý½Å
										 soft_pwm3_duty = duty;//È·¶¨Õ¼¿Õ±È£¨È«¾Ö±äÁ¿£©
										 Regular_times = EXTAL_IN_Hz/((1+ACQUIRE(CLK_DIV,2,0))*freq*PWM3_PRECISON);//¸ù¾ÝÉèÖÃÆµÂÊ¼°¾«¶È¼ÆËã¶¨Ê±Æ÷×ßÊ±³¤¶È
										 pit_init(T3,Regular_times);//ÆôÓÃT3¶¨Ê±Æ÷
										 set_vector_handler(TIMER3_VECTORn , PWM3_UNIT_TIME_ACC);//½«¶¨Ê±Æ÷T3ÖÐ¶ÏµÄ·þÎñº¯ÊýÉè¶¨ÎªPWM3_UNIT_TIME_ACC()
										 Whether_IRQ(TIMER3_VECTORn , IRQ_enable);//Ê¹ÄÜ¶¨Ê±Æ÷T3ÖÐ¶Ï
									 }
									 else if(use_Tn == PWM4_T4)//ÈôÊ¹ÓÃPWM4
												{
													PWM4_out = pxn;//È·¶¨pwmÊä³öÒý½Å
													soft_pwm4_duty = duty;//È·¶¨Õ¼¿Õ±È£¨È«¾Ö±äÁ¿£©
													Regular_times = EXTAL_IN_Hz/((1+ACQUIRE(CLK_DIV,2,0))*freq*PWM4_PRECISON);//¸ù¾ÝÉèÖÃÆµÂÊ¼°¾«¶È¼ÆËã¶¨Ê±Æ÷×ßÊ±³¤¶È
													pit_init(T4,Regular_times);//ÆôÓÃT4¶¨Ê±Æ÷
													set_vector_handler(TIMER4_VECTORn , PWM4_UNIT_TIME_ACC);//½«¶¨Ê±Æ÷T4ÖÐ¶ÏµÄ·þÎñº¯ÊýÉè¶¨ÎªPWM4_UNIT_TIME_ACC()
													Whether_IRQ(TIMER4_VECTORn , IRQ_enable);//Ê¹ÄÜ¶¨Ê±Æ÷T4ÖÐ¶Ï
												}
	}
}

/*!
 *	@brief		¶¨Ê±Æ÷ÖÐ¶Ï·þÎñº¯ÊýÈº
							¶¨Ê±Æ÷¼ÆÂúËùÐèÒªµÄÖÜÆÚ´óÓÚÉèÖÃÆµÂÊµÄÐÅºÅÖÜÆÚ£¬Âö¿íµ÷ÖÆ·½¿ÉÔÚÒ»´Î¶¨Ê±ÖÜÆÚÄÚÍê³É
 *	@param		
 *	@warning	²»¿Éµ÷ÓÃ
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
 *	@brief		¶¨Ê±Æ÷ÖÐ¶Ï·þÎñº¯ÊýÈº
							¶¨Ê±Æ÷¼ÆÂúËùÐèÒªµÄÖÜÆÚÐ¡ÓÚÉèÖÃÆµÂÊµÄÐÅºÅÖÜÆÚ£¬Âö¿íµ÷ÖÆ½«ÀûÓÃµ¥²½Ê±¼äÀÛ¼Ó·½Ê½Íê³É
 *	@param		
 *	@warning	²»¿Éµ÷ÓÃ
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