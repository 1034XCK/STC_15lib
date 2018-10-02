#include "include.h"

/*!
 *	@brief		
 *	@param		
 *	@warning	
 *	@sampleusage:	
 */

#define pump P04 //ˮ��
#define left P54 //���
#define down P17 //�¼�
#define up   P15 //�ϼ�
#define right P14 //�Ҽ�

int16 set_temp = 5000 , body_temp = 0 , water_temp = 0;
uint8 LCD_display_num=0 ;

void LCD_display(void);
void setting(void);

void main(void)
{
	gpio_init(p04 , STRONGPULLUP , 0);//ˮ��
	gpio_init(p05 , STRONGPULLUP , 0);//��
	gpio_init(p06 , STRONGPULLUP , 0);//��
	pump = 1;//��ˮ��
	CCP_pwm_init(CCP0,IDLE_PCA_RUN,INTERNAL,PWM_8bit,7813,0,CCF_INTERRUPT_DIS);//����
	CCP_pwm_init(CCP1,IDLE_PCA_RUN,INTERNAL,PWM_8bit,7813,38,CCF_INTERRUPT_DIS);//����
	CCP_pwm_init(CCP2,IDLE_PCA_RUN,INTERNAL,PWM_8bit,7813,255,CCF_INTERRUPT_DIS);//������Ƭ
	soft_pwm_init(PWM0_T0 , p05 , 7813 , 15);//���
	soft_pwm_init(PWM1_T1 , p06 , 7813 , 50);//�̵�(15~85)
	commoninit_init_LCD1602();
	init_DS18B20(p00);//�����´�
	init_DS18B20(p01);//��ȴˮ��ˮ���´�
	pit_init(T2,65535);
	set_vector_handler(TIMER2_VECTORn , LCD_display);
	Whether_IRQ(TIMER2_VECTORn , IRQ_enable);
	IT0 = 1;//�½����ж�
	set_vector_handler(INT0_VECTORn , setting);
	EX0 = 1;
	EA  = 1;
	P54 = 1;
	P17 = 1;
	P15 = 1;
	P14 = 1;
	
	while(1)
	{
		if(body_temp > set_temp)	CCP_pwm_duty(CCP2 , 0);//����������Ƭ
		else CCP_pwm_duty(CCP2 , 255);//�ر�������Ƭ
		CCP_pwm_duty(CCP0 , 255-(5000-water_temp)/12);
		if(water_temp > 2500 || body_temp > set_temp) pump = 0;//��ˮ��
		else pump = 1;//��ˮ��
	}
}

void LCD_display(void)
{
	LCD_display_num++;
	if(LCD_display_num > 254)
	{
		LCD_display_num = 0;
		LCD1602_display_array(1,1,"BT:");
		body_temp = DS18B20_read_temperature(p00);
		LCD1602_display_int16_number(1,5,body_temp);
		LCD1602_display_array(2,1,"WT:");
		water_temp = DS18B20_read_temperature(p01);
		LCD1602_display_int16_number(2,5,water_temp);
		LCD1602_display_array(1,11,"ST:");
		LCD1602_display_int16_number(2,11,set_temp);
		CCP_pwm_duty(CCP1 , 255-(body_temp+5000)/39);//����
		soft_pwm_init(PWM0_T0 , p05 , 7813 , 85+(body_temp-5000)/143);//���
	}
}

void setting(void)
{
	EX0 = 0;
	DELAY_MS(10);
	if(P32 == 0);//ȷ����ȷ������
	{
		CCP_pwm_duty(CCP2 , 255);//�ر�������Ƭ
		CCP_pwm_duty(CCP0 , 0);//�رշ���
		Whether_IRQ(TIMER0_VECTORn , IRQ_disable);
		Whether_IRQ(TIMER1_VECTORn , IRQ_disable);
		while(P32 == 0);//�ȴ�ȷ�����ͷ�
		Whether_IRQ(TIMER2_VECTORn , IRQ_disable);//�ر�������ʾ�ж�
		display_setup_LCD1602(0x01); //����
		LCD1602_display_array(1,1,"body temp:");
		DS18B20_read_temperature(p00);
		DELAY_MS(700);
		LCD1602_display_uint16_number(1,11,DS18B20_read_temperature(p00));
		LCD1602_display_array(2,1,"Set temp:");
		while(left == 1)//û�а���ȷ����
		{
			LCD1602_display_int16_number(2,11,set_temp);
			if(up == 0)	set_temp++;//�ϼ�����
			if(down == 0)	set_temp--;//�¼�����
		}
		while(left == 0);//�ȴ�ȷ�����ͷ�
		EX0 = 1;
		display_setup_LCD1602(0x01); //����
		Whether_IRQ(TIMER2_VECTORn , IRQ_enable);//����������ʾ�ж�
	}
	return;
}