#include "include.h"

/*!
 *	@brief		
 *	@param		
 *	@warning	
 *	@sampleusage:	
 */

#define pump P04 //水泵
#define left P54 //左键
#define down P17 //下键
#define up   P15 //上键
#define right P14 //右键

int16 set_temp = 5000 , body_temp = 0 , water_temp = 0;
uint8 LCD_display_num=0 ;

void LCD_display(void);
void setting(void);

void main(void)
{
	gpio_init(p04 , STRONGPULLUP , 0);//水泵
	gpio_init(p05 , STRONGPULLUP , 0);//灯
	gpio_init(p06 , STRONGPULLUP , 0);//灯
	pump = 1;//关水泵
	CCP_pwm_init(CCP0,IDLE_PCA_RUN,INTERNAL,PWM_8bit,7813,0,CCF_INTERRUPT_DIS);//风扇
	CCP_pwm_init(CCP1,IDLE_PCA_RUN,INTERNAL,PWM_8bit,7813,38,CCF_INTERRUPT_DIS);//蓝灯
	CCP_pwm_init(CCP2,IDLE_PCA_RUN,INTERNAL,PWM_8bit,7813,255,CCF_INTERRUPT_DIS);//主制冷片
	soft_pwm_init(PWM0_T0 , p05 , 7813 , 15);//红灯
	soft_pwm_init(PWM1_T1 , p06 , 7813 , 50);//绿灯(15~85)
	commoninit_init_LCD1602();
	init_DS18B20(p00);//箱体温传
	init_DS18B20(p01);//冷却水出水口温传
	pit_init(T2,65535);
	set_vector_handler(TIMER2_VECTORn , LCD_display);
	Whether_IRQ(TIMER2_VECTORn , IRQ_enable);
	IT0 = 1;//下降沿中断
	set_vector_handler(INT0_VECTORn , setting);
	EX0 = 1;
	EA  = 1;
	P54 = 1;
	P17 = 1;
	P15 = 1;
	P14 = 1;
	
	while(1)
	{
		if(body_temp > set_temp)	CCP_pwm_duty(CCP2 , 0);//开启主制冷片
		else CCP_pwm_duty(CCP2 , 255);//关闭主制冷片
		CCP_pwm_duty(CCP0 , 255-(5000-water_temp)/12);
		if(water_temp > 2500 || body_temp > set_temp) pump = 0;//开水泵
		else pump = 1;//关水泵
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
		CCP_pwm_duty(CCP1 , 255-(body_temp+5000)/39);//蓝灯
		soft_pwm_init(PWM0_T0 , p05 , 7813 , 85+(body_temp-5000)/143);//红灯
	}
}

void setting(void)
{
	EX0 = 0;
	DELAY_MS(10);
	if(P32 == 0);//确定键确定按下
	{
		CCP_pwm_duty(CCP2 , 255);//关闭主制冷片
		CCP_pwm_duty(CCP0 , 0);//关闭风扇
		Whether_IRQ(TIMER0_VECTORn , IRQ_disable);
		Whether_IRQ(TIMER1_VECTORn , IRQ_disable);
		while(P32 == 0);//等待确定键释放
		Whether_IRQ(TIMER2_VECTORn , IRQ_disable);//关闭数据显示中断
		display_setup_LCD1602(0x01); //清屏
		LCD1602_display_array(1,1,"body temp:");
		DS18B20_read_temperature(p00);
		DELAY_MS(700);
		LCD1602_display_uint16_number(1,11,DS18B20_read_temperature(p00));
		LCD1602_display_array(2,1,"Set temp:");
		while(left == 1)//没有按下确定键
		{
			LCD1602_display_int16_number(2,11,set_temp);
			if(up == 0)	set_temp++;//上键按下
			if(down == 0)	set_temp--;//下键按下
		}
		while(left == 0);//等待确定键释放
		EX0 = 1;
		display_setup_LCD1602(0x01); //清屏
		Whether_IRQ(TIMER2_VECTORn , IRQ_enable);//开启数据显示中断
	}
	return;
}